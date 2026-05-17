#include "theme_list.h"
#include "global_funcs.h"
#include "content.h"
#include "code_source_view.h"
#include <adwaita.h>

#define EDGE_SPACING 40
#define TEXT_BUTTON_SIZE_W 120
#define TEXT_BUTTON_SIZE_H 20

static void theme_button_clicked(GtkButton *btn, gpointer userdata) {
    const char *theme = gtk_button_get_label(btn);
    GtkWindow *parent_w = GTK_WINDOW(gtk_widget_get_ancestor(GTK_WIDGET(btn), GTK_TYPE_WINDOW));
    GtkWidget *nav_view = gtk_widget_get_ancestor(GTK_WIDGET(btn), ADW_TYPE_NAVIGATION_VIEW);

    if (get_theme_list(theme) != NULL) {
        GtkWidget *theme_list_page_content = create_theme_list_page(parent_w, theme);
        g_assert(theme_list_page_content != NULL);

        AdwNavigationPage *page = adw_navigation_page_new(theme_list_page_content, theme);
        g_assert(page != NULL);

        adw_navigation_view_push(ADW_NAVIGATION_VIEW(nav_view), page);
    }
    else {
        bool is_ui = false;
        const char **ui_themes = get_theme_list("GTK 4");
        for (int i = 0; ui_themes[i] != NULL; i++) {
            if (strcmp(theme, ui_themes[i]) == 0) {
                is_ui = true;
                break;
            }
        }
        const char *source_code = get_source_code(theme);
        if (source_code != nullptr) {
            GtkWidget *code_page_content = create_code_source_page(
                parent_w, 
                source_code, 
                is_ui
            );
            AdwNavigationPage *page = adw_navigation_page_new(code_page_content, "Редактор");
            adw_navigation_view_push(ADW_NAVIGATION_VIEW(nav_view), page);
        }
        else {
            AdwDialog *msg_window = adw_alert_dialog_new("Тема не имеет source code", "Возникла ошибка подгрузки исходного кода темы, вероятно тема повреждена или не завершена. Обратитесь к автору приложения.");
            adw_alert_dialog_add_responses(ADW_ALERT_DIALOG(msg_window),
                                "ok", "ОК",
                                NULL);
            adw_alert_dialog_set_close_response(ADW_ALERT_DIALOG(msg_window), "ok");
            adw_dialog_present(msg_window, GTK_WIDGET(parent_w));
        }
    }
}

GtkWidget* create_theme_list_page(GtkWindow *parent, const char *theme_name) {
    GtkWidget *c_base_h = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);
    GtkWidget *c_base_v1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10); 
    GtkWidget *c_base_v2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10); 
    GtkWidget *c_base_v3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    const char **theme_list = get_theme_list(theme_name);

    if (theme_list != NULL) {
        int i = 0;
        while (theme_list[i] != NULL) {
            GtkWidget *button = gtk_button_new_with_label(theme_list[i]);
            gtk_widget_set_size_request(button, TEXT_BUTTON_SIZE_W, TEXT_BUTTON_SIZE_H);

            g_signal_connect(button, "clicked", G_CALLBACK(theme_button_clicked), NULL);
            
            if (i % 3 == 0) {
                gtk_box_append(GTK_BOX(c_base_v1), button);
            }
            else if (i % 3 == 1) {
                gtk_box_append(GTK_BOX(c_base_v2), button);
            }
            else {
                gtk_box_append(GTK_BOX(c_base_v3), button);
            }
            i++;
        }
    }

    gtk_box_append(GTK_BOX(c_base_h), c_base_v1);
    gtk_box_append(GTK_BOX(c_base_h), c_base_v2);
    gtk_box_append(GTK_BOX(c_base_h), c_base_v3);
    
    gtk_widget_set_margin_start(c_base_h, EDGE_SPACING); gtk_widget_set_margin_end(c_base_h, EDGE_SPACING);
    gtk_widget_set_margin_top(c_base_h, EDGE_SPACING); gtk_widget_set_margin_bottom(c_base_h, EDGE_SPACING);

    center2_align(c_base_h);
    start_center_aling(c_base_v1);
    start_center_aling(c_base_v2);
    start_center_aling(c_base_v3);

    return page_init(c_base_h, theme_name);
}