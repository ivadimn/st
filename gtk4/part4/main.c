/* vim: colorcolumn=80 ts=4 sw=4
 */
/* main.c:  Boilerplate stub to view our demo widget.
 */

#include "demowidget.h"

static void demo_toggle_cb(DemoWidget *demo, gpointer user_data)
{
	g_print("DemoWidget says hello\n");
}

static void
activate (GtkApplication *app, gpointer user_data)
{
	GtkWidget *window;
	GtkWidget *box;
	GtkWidget *demo;
	GtkWidget *button;

	(void)user_data;	/* unused */

	window = gtk_application_window_new (app);

	box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
	//Определяет, будет ли всем дочерним элементам отведено равное место в поле.
	gtk_box_set_homogeneous(GTK_BOX(box), TRUE);

	button = gtk_button_new_with_label("Yo");


	demo = demo_widget_new();
	/*
	Устанавливает, будет ли виджет использовать доступное дополнительное горизонтальное пространство. 
	Когда пользователь изменяет размер окна, виджеты ...
	*/
	gtk_widget_set_hexpand(demo, TRUE);

	gtk_box_append(GTK_BOX(box), demo);
	gtk_box_append(GTK_BOX(box), button);

	/* задать метку кнопке используя стаедартный GObject setter */
	g_object_set(demo, "label", "foo bar baz", NULL);

	g_signal_connect(demo, "toggled", G_CALLBACK(demo_toggle_cb), NULL);

	g_signal_connect_swapped(button, "clicked", 
			G_CALLBACK(demo_widget_toggle_selection), demo);

	gtk_window_set_title (GTK_WINDOW(window), "Window");
	gtk_window_set_default_size (GTK_WINDOW(window), 400, 400);
	gtk_window_set_child (GTK_WINDOW(window), box);
	gtk_widget_show (window);
}

int
main (int argc, char *argv[])
{
	GtkApplication *app;
	int status;

	app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK(activate), NULL);
	status = g_application_run (G_APPLICATION(app), argc, argv);
	g_object_unref (app);

	return status;
}
