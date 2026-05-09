#include <adwaita.h>
#include "chapters.h"
#include "theme_list.h"

static void on_activate (GtkApplication *app) {
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_resource(css_provider, "/com/Linux_c_programming_helper/main.css");

    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(),
        GTK_STYLE_PROVIDER(css_provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION
    );

    g_object_unref(css_provider);

    GtkWidget *window = adw_application_window_new(app);
    GtkWidget *nav_view = adw_navigation_view_new();

    GtkWidget *chapters_page_content = create_chapters_page(nav_view);
    g_assert(chapters_page_content != NULL);

    AdwNavigationPage *initial_page = adw_navigation_page_new(chapters_page_content, "Разделы");
    g_assert(initial_page != NULL);

    adw_navigation_view_push(ADW_NAVIGATION_VIEW(nav_view), initial_page);

    adw_application_window_set_content(ADW_APPLICATION_WINDOW(window), nav_view);
    gtk_window_present(GTK_WINDOW(window));
}

int main (int argc, char *argv[]) {
    AdwApplication *app = adw_application_new("com.Linux_c_programming_helper", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(on_activate), NULL);
    return g_application_run(G_APPLICATION(app), argc, argv);
}