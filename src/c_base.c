#include "c_base.h"
#include <adwaita.h>

#define EDGE_SPACING 40
#define TEXT_BUTTON_SIZE_W 120
#define TEXT_BUTTON_SIZE_H 20

GtkWidget* create_c_base_page(void) {    
    GtkWidget *clamp = adw_clamp_new();
    GtkWidget *c_base_h = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);
    GtkWidget *c_base_v1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10); 
    GtkWidget *c_base_v2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10); 
    GtkWidget *c_base_v3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    GtkWidget *basics = gtk_button_new_with_label("Basics");
    GtkWidget *vector = gtk_button_new_with_label("Vector");
    GtkWidget *map = gtk_button_new_with_label("Map");
    GtkWidget *cstring = gtk_button_new_with_label("String");
    GtkWidget *function = gtk_button_new_with_label("Function");

    GtkWidget **buttons[] = { &basics, &vector, &map, &cstring, &function };
    const unsigned int buttons_count = sizeof(buttons) / sizeof(buttons[0]);
    for (unsigned int i = 0; i < buttons_count; i++) {
        gtk_widget_set_size_request(*buttons[i], TEXT_BUTTON_SIZE_W, TEXT_BUTTON_SIZE_H);
        if (i % 3 == 0) {
            gtk_box_append(GTK_BOX(c_base_v1), *buttons[i]);
        }
        else if (i % 3 == 1) {
            gtk_box_append(GTK_BOX(c_base_v2), *buttons[i]);
        }
        else {
            gtk_box_append(GTK_BOX(c_base_v3), *buttons[i]);
        }
    }

    gtk_box_append(GTK_BOX(c_base_h), c_base_v1);
    gtk_box_append(GTK_BOX(c_base_h), c_base_v2);
    gtk_box_append(GTK_BOX(c_base_h), c_base_v3);
    
    gtk_widget_set_halign(c_base_h, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(c_base_h, GTK_ALIGN_CENTER);

    adw_clamp_set_child(ADW_CLAMP(clamp), c_base_h);

    return clamp;
}