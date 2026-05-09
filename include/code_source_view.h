#ifndef CODE_SOURCE_VIEW_H
#define CODE_SOURCE_VIEW_H

#include <gtk/gtk.h>

GtkWidget* create_code_source_page(GtkWindow *parent, const char *initial_code, bool is_ui);

#endif