#include <gtk/gtk.h>
#include "chapters.h"
#include "c_base.h"

static void back_home_clicked(GtkButton *btn, gpointer userdata) {
    gtk_stack_set_visible_child_name(GTK_STACK(userdata), "chapters");
}

static void on_page_change(GObject *stack, GParamSpec *pspec, gpointer userdata) {
    const char *name = gtk_stack_get_visible_child_name(GTK_STACK(stack));

    if (g_strcmp0(name, "c_base") == 0 || g_strcmp0(name, "c_gtk4") == 0) 
        gtk_widget_set_visible(userdata, TRUE);
    else 
        gtk_widget_set_visible(userdata, FALSE);
}

static void on_activate (GtkApplication *app) {
    GResource *resources = g_resource_load("resources.xml", NULL);

    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_resource(css_provider, "/com/Linux_c_programming_helper/man.css");

    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(css_provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );

    g_object_unref(css_provider);

    GtkWidget *window = gtk_application_window_new (app);
    GtkWidget *header = gtk_header_bar_new();
    GtkWidget *window_handle = gtk_window_handle_new();
    GtkWidget *back_home = gtk_button_new_from_icon_name("go-previous-symbolic");
    GtkWidget *scrolled_window = gtk_scrolled_window_new();
    GtkWidget *main_stack = gtk_stack_new();
    GtkWidget *chapters_page = create_chapters_page(main_stack, scrolled_window);
    GtkWidget *c_base_page = create_c_base_page(main_stack, back_home);

    gtk_stack_add_named(GTK_STACK(main_stack), chapters_page, "chapters");
    gtk_stack_add_named(GTK_STACK(main_stack), c_base_page, "c_base");
    gtk_stack_set_visible_child(GTK_STACK(main_stack), chapters_page);

    gtk_widget_set_visible(back_home, TRUE);
    g_signal_connect(back_home, "clicked", G_CALLBACK(back_home_clicked), main_stack);

    g_signal_connect(main_stack, "notify::visible-child", G_CALLBACK(on_page_change), back_home);

    
    gtk_header_bar_set_title_widget(GTK_HEADER_BAR(header), window_handle);

    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled_window), main_stack);
    
    gtk_window_set_child(GTK_WINDOW (window), scrolled_window);
    gtk_window_set_titlebar(GTK_WINDOW(window), header);

    gtk_window_set_default_size (GTK_WINDOW (window), 1, 1);
    gtk_window_set_title (GTK_WINDOW (window), "Справочник по программированию на языке C под Linux");
    gtk_window_present (GTK_WINDOW (window));
}

int main (int argc, char *argv[]) {
    GtkApplication *app = gtk_application_new ("com.Linux_c_programming_helper",
                                                G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (on_activate), NULL);
    return g_application_run (G_APPLICATION (app), argc, argv);
}
