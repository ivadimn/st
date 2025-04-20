#include "../app.h"
#include "menu.h"


GtkWidget *menu_bar;

GtkWidget* create_menu()
{
    GtkWidget *menu;
    menu_bar = gtk_menu_bar_new();
    menu = gtk_menu_item_new_with_label("Файл");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu_bar), menu);
    //gtk_menu_bar_append(GTK_MENU_BAR(menu_bar), menu);

    //gtk_application_set_menubar(GTK_APPLICATION(get_appliation()), G_MENU_MODEL(menu_bar));

    return menu_bar;
    
}
