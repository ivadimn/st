#pragma once

#include <gtk/gtk.h>

/* Type declaration */
#define DEMO_TYPE_WIDGET demo_widget_get_type()
G_DECLARE_FINAL_TYPE (DemoWidget, demo_widget, DEMO, WIDGET, GtkWidget)

/* Method declarations */
GtkWidget* demo_widget_new(void); 
void demo_widget_set_label(DemoWidget *self, const char* label);
const char* demo_widget_get_label(DemoWidget *self);
void demo_widget_toggle_selection(DemoWidget *self);

