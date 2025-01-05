#ifndef __MENU_H__
#define __MENU_H__

#include <gtk/gtk.h>

static char *menu_headers[] = {
    "Файл",
    "Справочники",
    "О программе..."
};


GtkWidget*  create_menu();

#endif