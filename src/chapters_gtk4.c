#include "chapters.h"
#include <gtk/gtk.h>
#include <time.h>

#define ELEMENT_SIZE 180
#define EDGE_SPACING 20

static void c_base_clicked(GtkButton *btn, gpointer userdata) {
    gtk_stack_set_visible_child_name(GTK_STACK(userdata), "c_base");
}

static void hovered(GtkButton *btn, gpointer userdata) {

    gtk_widget_add_css_class(userdata, "hovered");
}

static void unhovered(GtkButton *btn, gpointer userdata) {
    gtk_widget_remove_css_class(userdata, "hovered");
}

GtkWidget* create_chapters_page(GtkWidget *main_stack, GtkWidget *scrolled_window) {
    GtkWidget *chapters_h = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    GtkWidget *chapters_v1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20); GtkWidget *chapters_v2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);

    GtkWidget *c_lang_base = gtk_button_new();
    GtkWidget *c_lang_base_img = gtk_image_new_from_resource(
        "/com/Linux_c_programming_helper/c_lang_base_image.png");
    GtkWidget *c_lang_base_text = gtk_label_new("Базовое\nпрограммирование на C");
    gtk_label_set_justify(GTK_LABEL(c_lang_base_text), GTK_JUSTIFY_CENTER);

    GtkWidget *c_lang_gtk4 = gtk_button_new();
    GtkWidget *c_lang_gtk4_img = gtk_image_new_from_resource(
        "/com/Linux_c_programming_helper/c_lang_gtk4_image.png");
    GtkWidget *c_lang_gtk4_text = gtk_label_new("Программирование с GTK4");
    gtk_label_set_justify(GTK_LABEL(c_lang_gtk4_text), GTK_JUSTIFY_CENTER);

    gtk_button_set_child(GTK_BUTTON(c_lang_base), c_lang_base_img);
    gtk_button_set_child(GTK_BUTTON(c_lang_gtk4), c_lang_gtk4_img);
    
    gtk_widget_set_size_request(c_lang_base, ELEMENT_SIZE, ELEMENT_SIZE);
    gtk_widget_set_size_request(c_lang_gtk4, ELEMENT_SIZE, ELEMENT_SIZE);


    gtk_widget_add_css_class(c_lang_base, "img_button");
    gtk_widget_add_css_class(c_lang_base_text, "base_under_text");
    GtkEventController *controller_motion_c_base = gtk_event_controller_motion_new();
    gtk_widget_add_controller(c_lang_base, controller_motion_c_base);

    gtk_widget_add_css_class(c_lang_gtk4, "img_button");
    gtk_widget_add_css_class(c_lang_gtk4_text, "gtk_under_text");
    GtkEventController *controller_motion_c_gtk4 = gtk_event_controller_motion_new();
    gtk_widget_add_controller(c_lang_gtk4, controller_motion_c_gtk4);


    g_signal_connect(controller_motion_c_base, "enter", G_CALLBACK(hovered), c_lang_base_text);
    g_signal_connect(controller_motion_c_base, "leave", G_CALLBACK(unhovered), c_lang_base_text);

    g_signal_connect(controller_motion_c_gtk4, "enter", G_CALLBACK(hovered), c_lang_gtk4_text);
    g_signal_connect(controller_motion_c_gtk4, "leave", G_CALLBACK(unhovered), c_lang_gtk4_text);

    g_signal_connect(c_lang_base, "clicked", G_CALLBACK(c_base_clicked), main_stack);


    gtk_box_append(GTK_BOX(chapters_v1), c_lang_base_text);
    gtk_box_append(GTK_BOX(chapters_v1), c_lang_base);
    gtk_box_append(GTK_BOX(chapters_v2), c_lang_gtk4_text);
    gtk_box_append(GTK_BOX(chapters_v2), c_lang_gtk4);

    gtk_box_append(GTK_BOX(chapters_h), chapters_v1); gtk_box_append(GTK_BOX(chapters_h), chapters_v2);

    gtk_widget_set_margin_start(chapters_h, EDGE_SPACING); gtk_widget_set_margin_end(chapters_h, EDGE_SPACING);
    gtk_widget_set_margin_top(chapters_h, EDGE_SPACING); gtk_widget_set_margin_bottom(chapters_h, EDGE_SPACING);

    gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(scrolled_window), (ELEMENT_SIZE * 3 - EDGE_SPACING));
    gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW(scrolled_window), (ELEMENT_SIZE * 2 - EDGE_SPACING));

    gtk_widget_set_halign(chapters_h, GTK_ALIGN_CENTER); gtk_widget_set_valign(chapters_h, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(chapters_v1, GTK_ALIGN_CENTER); gtk_widget_set_valign(chapters_v1, GTK_ALIGN_START);
    gtk_widget_set_halign(chapters_v2, GTK_ALIGN_CENTER); gtk_widget_set_valign(chapters_v2, GTK_ALIGN_START);

    return chapters_h;
}