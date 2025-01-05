#include "app.h"

#include "views/table.h"
#include "views/menu.h"

GtkWidget *window;
GtkApplication *app;

GtkWidget *get_main_window()
{
    return window;
}

GtkApplication *get_appliation() 
{
    return app;
}

static void activate(GtkApplication *app, gpointer *user_data)
{
    GtkWidget *table;
    GtkWidget *menu_bar;
    GtkWidget *vbox;
    GError *err = NULL;
    
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Тест GTK");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    gtk_window_set_default_icon_from_file("android.png", &err);
    //gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    if (err != NULL)
    {
        printf("Ошибка загрузки иконки %s\n", err->message);
    }
    
    menu_bar = create_menu();
    table = create_table(window);
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(vbox), menu_bar, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), table, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), vbox);
    gtk_widget_show_all(window);
}

int main(int argc, char** argv) 
{
    
    int ret;

    app = gtk_application_new("db.staffs", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    ret = g_application_run(G_APPLICATION(app), argc, argv);

    g_object_unref(app);

    return ret;
}
