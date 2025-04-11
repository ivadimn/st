#include <gtk/gtk.h>


static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;

    user_data;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Window");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 300);
    gtk_window_present(GTK_WINDOW(window));
}


int main(int argc, char** argv)
{
    GtkApplication *app;
    int status;

    //создать объект приложения 
    app = gtk_application_new("ru.ivadimn.gtk", G_APPLICATION_FLAGS_NONE);

    // присоединить сигнал активации приложения для запуска функции
    // которая создаёт оконные объекты и отображает их 
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    // запустить поток приложения по завершению приложение вернёт статус
    status = g_application_run(G_APPLICATION(app), argc, argv);

    // уничтожить объект приложения
    g_object_unref(app);

    return status;
}