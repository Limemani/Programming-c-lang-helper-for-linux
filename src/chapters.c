#include "chapters.h"
#include "c_base.h"
#include <adwaita.h>
#include <gtk/gtk.h>

#define ELEMENT_SIZE 180
#define EDGE_SPACING 20

static void c_base_clicked(GtkButton *btn, gpointer userdata) {
    GtkWidget *c_base_page_content = create_c_base_page();
    g_assert(c_base_page_content != NULL);

    AdwNavigationPage *page = adw_navigation_page_new(c_base_page_content, "Основы C");
    g_assert(page != NULL);

    adw_navigation_view_push(ADW_NAVIGATION_VIEW(userdata), page);
}

// Функции-обработчики hover теперь получают GtkEventControllerMotion
static void hovered(GtkEventControllerMotion *controller, gpointer userdata) {
    gtk_widget_add_css_class(GTK_WIDGET(userdata), "hovered");
}

static void unhovered(GtkEventControllerMotion *controller, gpointer userdata) {
    gtk_widget_remove_css_class(GTK_WIDGET(userdata), "hovered");
}

GtkWidget* create_chapters_page(GtkWidget *nav_view) {
    GtkWidget *clamp = adw_clamp_new();
    GtkWidget *chapters_h = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 40); // Увеличим расстояние между блоками
    GtkWidget *chapters_v1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *chapters_v2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    // --- Блок 1: Основы C ---
    GtkWidget *c_lang_base = gtk_button_new();
    GtkWidget *c_lang_base_img = gtk_image_new_from_resource(
        "/com/Linux_c_programming_helper/c_lang_base_image.png");
    GtkWidget *c_lang_base_text = gtk_label_new("Базовое\nпрограммирование на C");
    gtk_label_set_justify(GTK_LABEL(c_lang_base_text), GTK_JUSTIFY_CENTER);
    gtk_widget_set_valign(c_lang_base_text, GTK_ALIGN_START);

    // --- Блок 2: GTK4 ---
    GtkWidget *c_lang_gtk4 = gtk_button_new();
    GtkWidget *c_lang_gtk4_img = gtk_image_new_from_resource(
        "/com/Linux_c_programming_helper/c_lang_gtk4_image.png");
    GtkWidget *c_lang_gtk4_text = gtk_label_new("Программирование\nс GTK4");
    gtk_label_set_justify(GTK_LABEL(c_lang_gtk4_text), GTK_JUSTIFY_CENTER);
    gtk_widget_set_valign(c_lang_gtk4_text, GTK_ALIGN_START);

    // Устанавливаем картинки как дочерние элементы кнопок
    gtk_button_set_child(GTK_BUTTON(c_lang_base), c_lang_base_img);
    gtk_button_set_child(GTK_BUTTON(c_lang_gtk4), c_lang_gtk4_img);
    
    gtk_widget_set_size_request(c_lang_base, ELEMENT_SIZE, ELEMENT_SIZE);
    gtk_widget_set_size_request(c_lang_gtk4, ELEMENT_SIZE, ELEMENT_SIZE);

    // Применяем новые CSS-классы
    gtk_widget_add_css_class(c_lang_base, "img_button");
    gtk_widget_add_css_class(c_lang_base_text, "base_under_text");

    gtk_widget_add_css_class(c_lang_gtk4, "img_button");
    gtk_widget_add_css_class(c_lang_gtk4_text, "gtk_under_text");

    // Создаем контроллеры для отслеживания наведения мыши
    GtkEventController *controller_motion_c_base = gtk_event_controller_motion_new();
    gtk_widget_add_controller(c_lang_base, controller_motion_c_base);

    GtkEventController *controller_motion_c_gtk4 = gtk_event_controller_motion_new();
    gtk_widget_add_controller(c_lang_gtk4, controller_motion_c_gtk4);

    // Подключаем сигналы enter/leave. Они передают текст (userdata) для изменения его класса
    g_signal_connect(controller_motion_c_base, "enter", G_CALLBACK(hovered), c_lang_base_text);
    g_signal_connect(controller_motion_c_base, "leave", G_CALLBACK(unhovered), c_lang_base_text);

    g_signal_connect(controller_motion_c_gtk4, "enter", G_CALLBACK(hovered), c_lang_gtk4_text);
    g_signal_connect(controller_motion_c_gtk4, "leave", G_CALLBACK(unhovered), c_lang_gtk4_text);

    // Подключаем сигнал нажатия на кнопку
    g_signal_connect(c_lang_base, "clicked", G_CALLBACK(c_base_clicked), nav_view);
    // g_signal_connect(c_lang_gtk4, "clicked", G_CALLBACK(c_gtk4_clicked), nav_view); // (если будет)

    // ПРАВИЛЬНЫЙ ПОРЯДОК: сначала картинка, потом текст под ней
    gtk_box_append(GTK_BOX(chapters_v1), c_lang_base);
    gtk_box_append(GTK_BOX(chapters_v1), c_lang_base_text);
    
    gtk_box_append(GTK_BOX(chapters_v2), c_lang_gtk4);
    gtk_box_append(GTK_BOX(chapters_v2), c_lang_gtk4_text);

    // Добавляем вертикальные блоки в горизонтальный
    gtk_box_append(GTK_BOX(chapters_h), chapters_v1);
    gtk_box_append(GTK_BOX(chapters_h), chapters_v2);

    gtk_widget_set_margin_start(chapters_h, EDGE_SPACING); gtk_widget_set_margin_end(chapters_h, EDGE_SPACING);
    gtk_widget_set_margin_top(chapters_h, EDGE_SPACING); gtk_widget_set_margin_bottom(chapters_h, EDGE_SPACING);

    // Центрирование
    gtk_widget_set_halign(chapters_h, GTK_ALIGN_CENTER); gtk_widget_set_valign(chapters_h, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(chapters_v1, GTK_ALIGN_CENTER); gtk_widget_set_valign(chapters_v1, GTK_ALIGN_CENTER);
    gtk_widget_set_halign(chapters_v2, GTK_ALIGN_CENTER); gtk_widget_set_valign(chapters_v2, GTK_ALIGN_CENTER);
    
    adw_clamp_set_child(ADW_CLAMP(clamp), chapters_h);

    return clamp;
}