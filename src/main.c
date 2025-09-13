#include <adwaita.h>
#include <gtk/gtk.h>
#include "chapters.h"
#include "c_base.h"

static void on_activate (GtkApplication *app) {
    // --- Загрузка ресурсов с проверкой ---
    GResource *resources = g_resource_load("resources.xml", NULL);

    // Убедитесь, что файл "resources.gresource" находится там,
    // где приложение ожидает его найти (обычно рядом с исполняемым файлом).
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_resource(css_provider, "/com/Linux_c_programming_helper/man.css");

    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(css_provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );

    g_object_unref(css_provider);

    // --- Создание UI ---
    GtkWidget *window = adw_application_window_new(app);
    GtkWidget *header = adw_header_bar_new();
    GtkWidget *content_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *nav_view = adw_navigation_view_new();

    // Создаем контент для страницы "Разделы"
    GtkWidget *chapters_page_content = create_chapters_page(nav_view);
    g_assert(chapters_page_content != NULL); // Проверяем, что страница создалась

    // Создаем страницу Adwaita с контентом и заголовком
    AdwNavigationPage *initial_page = adw_navigation_page_new(chapters_page_content, "Разделы");
    g_assert(initial_page != NULL);

    // Добавляем страницу в навигацию
    adw_navigation_view_push(ADW_NAVIGATION_VIEW(nav_view), initial_page);

    adw_header_bar_set_title_widget(ADW_HEADER_BAR(header), adw_window_title_new("Справочник по C", NULL));
    
    gtk_box_append(GTK_BOX(content_box), header);
    gtk_box_append(GTK_BOX(content_box), nav_view);

    adw_application_window_set_content(ADW_APPLICATION_WINDOW(window), content_box);
    gtk_window_present(GTK_WINDOW(window));
}

int main (int argc, char *argv[]) {
    AdwApplication *app = adw_application_new("com.Linux_c_programming_helper", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    return g_application_run(G_APPLICATION(app), argc, argv);
}