#include "chapters.h"
#include "theme_list.h"
#include "global_funcs.h"
#include "content.h"
#include <adwaita.h>

#define ELEMENT_SIZE 180
#define EDGE_SPACING 20

static void c_base_clicked(GtkButton *btn, gpointer userdata) {
    GtkWindow *parent_w = GTK_WINDOW(gtk_widget_get_ancestor(GTK_WIDGET(btn), GTK_TYPE_WINDOW));

    if (get_theme_list("Базовый C") != NULL) {
        GtkWidget *theme_list_page_content = create_theme_list_page(parent_w, "Базовый C");
        g_assert(theme_list_page_content != NULL);

        AdwNavigationPage *page = adw_navigation_page_new(theme_list_page_content, "Основы C");
        g_assert(page != NULL);

        adw_navigation_view_push(ADW_NAVIGATION_VIEW(userdata), page);
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

static void c_gtk4_clicked(GtkButton *btn, gpointer userdata) {
    GtkWindow *parent_w = GTK_WINDOW(gtk_widget_get_ancestor(GTK_WIDGET(btn), GTK_TYPE_WINDOW));

    if (get_theme_list("GTK 4") != NULL) {
        GtkWidget *theme_list_page_content = create_theme_list_page(parent_w, "GTK 4");
        g_assert(theme_list_page_content != NULL);

        AdwNavigationPage *page = adw_navigation_page_new(theme_list_page_content, "Основы GTK 4");
        g_assert(page != NULL);

        adw_navigation_view_push(ADW_NAVIGATION_VIEW(userdata), page);
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

static void hovered(GtkEventControllerMotion *controller, gpointer userdata) {
    gtk_widget_add_css_class(GTK_WIDGET(userdata), "hovered");
}

static void unhovered(GtkEventControllerMotion *controller, gpointer userdata) {
    gtk_widget_remove_css_class(GTK_WIDGET(userdata), "hovered");
}

void text_on_hover_modifier(GtkWidget *parent, GtkWidget *child) {
    gtk_widget_add_css_class(parent, "img_button");
    gtk_widget_add_css_class(child, "under_text");

    GtkEventController *controller_motion = gtk_event_controller_motion_new();
    gtk_widget_add_controller(parent, controller_motion);

    g_signal_connect(controller_motion, "enter", G_CALLBACK(hovered), child);
    g_signal_connect(controller_motion, "leave", G_CALLBACK(unhovered), child);
}

GtkWidget* create_chapters_page(GtkWidget *nav_view) {
    GtkWidget *chapters_h = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 40);
    GtkWidget *chapters_v1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *chapters_v2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);


    GtkWidget *c_lang_base = gtk_button_new();
    GtkWidget *c_lang_base_img = gtk_image_new_from_resource(
        "/com/Linux_c_programming_helper/c_lang_base_image.png");
    GtkWidget *c_lang_base_text = gtk_label_new("Базовый C");
    gtk_label_set_justify(GTK_LABEL(c_lang_base_text), GTK_JUSTIFY_CENTER);
    gtk_widget_set_valign(c_lang_base_text, GTK_ALIGN_START);

    GtkWidget *c_lang_gtk4 = gtk_button_new();
    GtkWidget *c_lang_gtk4_img = gtk_image_new_from_resource(
        "/com/Linux_c_programming_helper/c_lang_gtk4_image.png");
    GtkWidget *c_lang_gtk4_text = gtk_label_new("GTK 4");
    gtk_label_set_justify(GTK_LABEL(c_lang_gtk4_text), GTK_JUSTIFY_CENTER);
    gtk_widget_set_valign(c_lang_gtk4_text, GTK_ALIGN_START);



    gtk_button_set_child(GTK_BUTTON(c_lang_base), c_lang_base_img);
    gtk_button_set_child(GTK_BUTTON(c_lang_gtk4), c_lang_gtk4_img);
    
    gtk_widget_set_size_request(c_lang_base, ELEMENT_SIZE, ELEMENT_SIZE);
    gtk_widget_set_size_request(c_lang_gtk4, ELEMENT_SIZE, ELEMENT_SIZE);

    text_on_hover_modifier(c_lang_base, c_lang_base_text);
    text_on_hover_modifier(c_lang_gtk4, c_lang_gtk4_text);



    g_signal_connect(c_lang_base, "clicked", G_CALLBACK(c_base_clicked), nav_view);
    g_signal_connect(c_lang_gtk4, "clicked", G_CALLBACK(c_gtk4_clicked), nav_view);


    gtk_box_append(GTK_BOX(chapters_v1), c_lang_base);
    gtk_box_append(GTK_BOX(chapters_v1), c_lang_base_text);
    
    gtk_box_append(GTK_BOX(chapters_v2), c_lang_gtk4);
    gtk_box_append(GTK_BOX(chapters_v2), c_lang_gtk4_text);

    gtk_box_append(GTK_BOX(chapters_h), chapters_v1);
    gtk_box_append(GTK_BOX(chapters_h), chapters_v2);

    

    gtk_widget_set_margin_start(chapters_h, EDGE_SPACING); gtk_widget_set_margin_end(chapters_h, EDGE_SPACING);
    gtk_widget_set_margin_top(chapters_h, EDGE_SPACING); gtk_widget_set_margin_bottom(chapters_h, EDGE_SPACING);

    center2_align(chapters_h);
    center2_align(chapters_v1);
    center2_align(chapters_v2);

    return page_init(chapters_h, "Справочник по C");
}