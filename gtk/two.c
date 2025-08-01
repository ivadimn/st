#include <gtk/gtk.h>

static void print_hello(GtkWidget *widget, gpointer data)
{
    g_print("Hello world!!\n");
}

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *box; 

    user_data;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Window");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 300);

    //создаём менеджер компоновки вертикальных box 
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_widget_set_halign(box, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(box, GTK_ALIGN_CENTER);

    gtk_window_set_child(GTK_WINDOW(window), box);

    button = gtk_button_new_with_label("Hello button");
    //присоединить обрабоччик сигнала нажатия на кнопку
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);
    //присоединить обрабоччик сигнала нажатия на кнопку здесь в качестве 
    //GtkWidget в функцию gtk_window_destroy передаётся window
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_window_destroy), window);

    gtk_box_append(GTK_BOX(box), button);

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