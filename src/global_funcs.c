#include "global_funcs.h"

void center2_align(GtkWidget *widget){
    gtk_widget_set_halign(widget, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(widget, GTK_ALIGN_CENTER);
}

void start_center_aling(GtkWidget *widget){
    gtk_widget_set_halign(widget, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(widget, GTK_ALIGN_START);
}

GtkWidget* page_init(GtkWidget *box, const char *title){
    GtkWidget *window = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    GtkWidget *header = adw_header_bar_new();

    adw_header_bar_set_title_widget(ADW_HEADER_BAR(header), adw_window_title_new(title, NULL));
    gtk_box_append(GTK_BOX(window), header);

    gtk_box_append(GTK_BOX(window), box);

    return window;
}