#include <gtk/gtk.h>

static void print_hello(GtkWidget *widget, gpointer data)
{
    g_print("Hello world!!\n");
}

static void activate(GtkApplication *app, gpointer user_data)
{
    
    //создаём посторитель интерфрейса 
    GtkBuilder *builder = gtk_builder_new();
    //загружаем из файла
    gtk_builder_add_from_file(builder, "builder.ui", NULL);

    GObject *window = gtk_builder_get_object(builder, "window");
    gtk_window_set_application(GTK_WINDOW(window), app);


    GObject *button = gtk_builder_get_object(builder, "button1"); 
    //присоединить обрабоччик сигнала нажатия на кнопку
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);

    button = gtk_builder_get_object(builder, "button2"); 
    //присоединить обрабоччик сигнала нажатия на кнопку
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), NULL);


    button = gtk_builder_get_object(builder, "quit"); 
    //присоединить обрабоччик сигнала нажатия на кнопку здесь в качестве 
    //GtkWidget в функцию gtk_window_destroy передаётся window
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_window_destroy), window);
   
    gtk_widget_set_visible(GTK_WIDGET(window), TRUE);
    
    g_object_unref(builder);
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