#include "global_funcs.h"

void center2_align(GtkWidget *widget){
    gtk_widget_set_halign(widget, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(widget, GTK_ALIGN_CENTER);
}

void start_center_aling(GtkWidget *widget){
    gtk_widget_set_halign(widget, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(widget, GTK_ALIGN_START);
}