#include "code_source_view.h"
#include "global_funcs.h"
#include <gtksourceview/gtksource.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    GtkSourceBuffer *source_buffer;
    GtkTextBuffer *output_buffer;
    GtkTextBuffer *input_buffer; 
    GtkWidget *gtk4_check;       
    GtkWidget *run_button;
} CodeViewWidgets;

typedef struct {
    char *command;
    CodeViewWidgets *widgets;
} ThreadData;

typedef struct {
    char *text;
    CodeViewWidgets *widgets;
} OutputMessage;

static gboolean append_output_to_ui(gpointer data) {
    OutputMessage *msg = (OutputMessage *)data;
    
    GtkTextIter iter;
    gtk_text_buffer_get_end_iter(msg->widgets->output_buffer, &iter);
    gtk_text_buffer_insert(msg->widgets->output_buffer, &iter, msg->text, -1);
    
    g_free(msg->text);
    g_free(msg);
    return G_SOURCE_REMOVE;
}

static gboolean execution_finished(gpointer data) {
    CodeViewWidgets *widgets = (CodeViewWidgets *)data;
    gtk_widget_set_sensitive(widgets->run_button, TRUE);
    
    GtkTextIter iter;
    gtk_text_buffer_get_end_iter(widgets->output_buffer, &iter);
    gtk_text_buffer_insert(widgets->output_buffer, &iter, "\n--- Выполнение завершено ---\n", -1);
    return G_SOURCE_REMOVE;
}

static gpointer run_process_thread(gpointer data) {
    ThreadData *t_data = (ThreadData *)data;
    
    FILE *pipe = popen(t_data->command, "r");
    if (pipe) {
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
            OutputMessage *msg = g_new(OutputMessage, 1);
            msg->text = g_strdup(buffer);
            msg->widgets = t_data->widgets;
            
            g_idle_add(append_output_to_ui, msg);
        }
        pclose(pipe);
    }
    
    g_idle_add(execution_finished, t_data->widgets);
    
    g_free(t_data->command);
    g_free(t_data);
    return NULL;
}

static void on_run_clicked(GtkButton *btn, gpointer userdata) {
    CodeViewWidgets *widgets = (CodeViewWidgets *)userdata;
    GtkTextIter start, end;
    
    gtk_widget_set_sensitive(GTK_WIDGET(btn), FALSE);
    gtk_text_buffer_set_text(widgets->output_buffer, "Компиляция и запуск...\n", -1);

    gtk_text_buffer_get_bounds(GTK_TEXT_BUFFER(widgets->source_buffer), &start, &end);
    char *code = gtk_text_buffer_get_text(GTK_TEXT_BUFFER(widgets->source_buffer), &start, &end, FALSE);

    gtk_text_buffer_get_bounds(widgets->input_buffer, &start, &end);
    char *input_text = gtk_text_buffer_get_text(widgets->input_buffer, &start, &end, FALSE);

    const gchar *tmp_dir = g_get_tmp_dir();
    char source_path[1024], binary_path[1024], input_path[1024];
    
    snprintf(source_path, sizeof(source_path), "%s/temp_code_%d.c", tmp_dir, getpid());
    snprintf(binary_path, sizeof(binary_path), "%s/temp_out_%d", tmp_dir, getpid());
    snprintf(input_path, sizeof(input_path), "%s/temp_in_%d.txt", tmp_dir, getpid());

    FILE *fp = fopen(source_path, "w");
    if (fp) { fprintf(fp, "%s", code); fclose(fp); }
    g_free(code);

    fp = fopen(input_path, "w");
    if (fp) { fprintf(fp, "%s", input_text); fclose(fp); }
    g_free(input_text);

    gboolean is_gtk4 = gtk_check_button_get_active(GTK_CHECK_BUTTON(widgets->gtk4_check));
    const char *gtk_flags = is_gtk4 ? "`pkg-config --cflags --libs gtk4 libadwaita-1`" : "";

    char command[2048];
    snprintf(command, sizeof(command), 
             "cd \"%s\" && gcc \"%s\" -o \"%s\" %s 2>&1 && \"%s\" < \"%s\" 2>&1", 
             tmp_dir, source_path, binary_path, gtk_flags, binary_path, input_path);

    ThreadData *t_data = g_new(ThreadData, 1);
    t_data->command = g_strdup(command);
    t_data->widgets = widgets;

    g_thread_new("compiler_thread", run_process_thread, t_data);
}

GtkWidget* create_code_source_page(GtkWindow *parent, const char *initial_code, bool is_ui) {
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_size_request(main_box, 854, 480);
    
    GtkWidget *toolbar = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_margin_start(toolbar, 10); gtk_widget_set_margin_end(toolbar, 10);
    gtk_widget_set_margin_top(toolbar, 10); gtk_widget_set_margin_bottom(toolbar, 10);

    GtkWidget *run_button = gtk_button_new_with_label("▶ Запустить код");
    gtk_widget_add_css_class(run_button, "suggested-action");

    GtkWidget *gtk4_check = gtk_check_button_new_with_label("Компилировать с GTK4 / Libadwaita");
    
    gtk_box_append(GTK_BOX(toolbar), run_button);
    gtk_box_append(GTK_BOX(toolbar), gtk4_check);
    gtk_box_append(GTK_BOX(main_box), toolbar);

    if(is_ui) {
        gtk_check_button_set_active(GTK_CHECK_BUTTON(gtk4_check), true);
    }

    GtkWidget *main_paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_widget_set_hexpand(main_paned, TRUE);
    gtk_widget_set_vexpand(main_paned, TRUE);
    gtk_paned_set_position(GTK_PANED(main_paned), 500);

    GtkSourceLanguageManager *lang_manager = gtk_source_language_manager_get_default();
    GtkSourceLanguage *lang = gtk_source_language_manager_get_language(lang_manager, "c");
    
    GtkSourceBuffer *source_buffer = gtk_source_buffer_new(NULL);
    gtk_source_buffer_set_language(source_buffer, lang);
    gtk_text_buffer_set_text(GTK_TEXT_BUFFER(source_buffer), initial_code ? initial_code : "", -1);

    GtkWidget *source_view = gtk_source_view_new_with_buffer(source_buffer);
    gtk_source_view_set_tab_width(GTK_SOURCE_VIEW(source_view), 4);
    gtk_source_view_set_indent_width(GTK_SOURCE_VIEW(source_view), 4);
    gtk_source_view_set_show_line_numbers(GTK_SOURCE_VIEW(source_view), TRUE);
    gtk_source_view_set_highlight_current_line(GTK_SOURCE_VIEW(source_view), TRUE);
    gtk_source_view_set_auto_indent(GTK_SOURCE_VIEW(source_view), TRUE);
    gtk_widget_set_vexpand(source_view, TRUE);

    GtkWidget *source_scroll = gtk_scrolled_window_new();
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(source_scroll), source_view);

    GtkWidget *right_paned = gtk_paned_new(GTK_ORIENTATION_VERTICAL);
    gtk_paned_set_position(GTK_PANED(right_paned), 150);

    GtkWidget *input_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *input_label = gtk_label_new("Ввод данных (для scanf/gets):");
    gtk_widget_set_halign(input_label, GTK_ALIGN_START);
    gtk_widget_set_margin_start(input_label, 5);
    
    GtkTextBuffer *input_buffer = gtk_text_buffer_new(NULL);
    GtkWidget *input_view = gtk_text_view_new_with_buffer(input_buffer);
    gtk_text_view_set_monospace(GTK_TEXT_VIEW(input_view), TRUE);
    GtkWidget *input_scroll = gtk_scrolled_window_new();
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(input_scroll), input_view);
    
    gtk_box_append(GTK_BOX(input_box), input_label);
    gtk_box_append(GTK_BOX(input_box), input_scroll);
    gtk_widget_set_vexpand(input_scroll, TRUE);

    GtkWidget *output_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *output_label = gtk_label_new("Вывод программы (Консоль):");
    gtk_widget_set_halign(output_label, GTK_ALIGN_START);
    gtk_widget_set_margin_start(output_label, 5);

    GtkTextBuffer *output_buffer = gtk_text_buffer_new(NULL);
    GtkWidget *output_view = gtk_text_view_new_with_buffer(output_buffer);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(output_view), FALSE);
    
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider, "textview { background-color: #1e1e1e; color: #00ff00; font-family: 'Monospace'; }", -1);
    gtk_style_context_add_provider(gtk_widget_get_style_context(output_view), 
        GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);

    GtkWidget *output_scroll = gtk_scrolled_window_new();
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(output_scroll), output_view);

    gtk_box_append(GTK_BOX(output_box), output_label);
    gtk_box_append(GTK_BOX(output_box), output_scroll);
    gtk_widget_set_vexpand(output_scroll, TRUE);

    gtk_paned_set_start_child(GTK_PANED(right_paned), input_box);
    gtk_paned_set_end_child(GTK_PANED(right_paned), output_box);

    gtk_paned_set_start_child(GTK_PANED(main_paned), source_scroll);
    gtk_paned_set_end_child(GTK_PANED(main_paned), right_paned);
    
    gtk_box_append(GTK_BOX(main_box), main_paned);

    CodeViewWidgets *widgets = g_new(CodeViewWidgets, 1);
    widgets->source_buffer = source_buffer;
    widgets->output_buffer = output_buffer;
    widgets->input_buffer  = input_buffer;
    widgets->gtk4_check    = gtk4_check;
    widgets->run_button    = run_button;

    g_signal_connect(run_button, "clicked", G_CALLBACK(on_run_clicked), widgets);

    return page_init(main_box, "Редактор кода");
}