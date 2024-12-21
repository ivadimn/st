#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define BTNS_COUNT 17
#define BUFF_SIZE 128
#define SIZE 10

char *btns[BTNS_COUNT] = {
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", ".", "+", "-","*", "/", "C", "=" 
};

typedef struct {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *button[17];
} calc;

GtkWidget *box;

char input_buffer[BUFF_SIZE] = {0};
char output_buffer[BUFF_SIZE] = {0};

bool clear_buffer = false;
bool add = false;
bool mul = false;
bool div = false;
bool sub = false;

float result = 0.0;
static float num[SIZE];
int count = 0;

static void calculate(GtkButton *button, gpointer data)
{
    const gchar* text = gtk_button_get_label(button);
}

static void activate(GtkApplication *app, gpointer user_data)
{
    calc widget;

    widget.window = gtk_application_window_new(app);
    gtk_window_set_position(GTK_WINDOW(widget.window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(widget.window), "Las Creations Calculator");
    gtk_window_set_default_size(GTK_WINDOW(widget.window), 200, 200);
    gtk_container_set_border_width(GTK_CONTAINER(widget.window), 10);

    widget.grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(widget.window), widget.grid);
    
    box = gtk_entry_new();
    gtk_editable_set_editable(GTK_EDITABLE(box), FALSE);

    for(int i = 0; i < BTNS_COUNT; i++) 
    {
        widget.button[i] = gtk_button_new_with_label(btns[i]);
    }
    gtk_grid_attach(GTK_GRID(widget.grid), box, 0, 0, 4, 1);

    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[15], 0, 1, 3, 1);
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[14], 3, 1, 1, 1);

    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[7], 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[8], 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[9], 2, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[13], 3, 2, 1, 1);

    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[4], 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[5], 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[6], 2, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[12], 3, 3, 1, 1);

    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[1], 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[2], 1, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[3], 2, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[11], 3, 4, 1, 1);

    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[0], 0, 5, 2, 1);
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[10], 2, 5, 1, 1);
    gtk_grid_attach(GTK_GRID(widget.grid), widget.button[16], 3, 5, 1, 1);

    for(int i = 0; i < BTNS_COUNT; i++)
    {
        g_signal_connect(widget.button[i], "clicked", G_CALLBACK(calculate), NULL);
    }


    gtk_widget_show_all(widget.window);
}


int main(int argc, char **argv)
{
    GtkApplication *app;
    int ret;
    app = gtk_application_new("app.calculator", G_APPLICATION_FLAGS_NONE);
    
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    ret = g_application_run(G_APPLICATION(app), argc, argv);
    
    g_object_unref(app);
	
   
    return ret;

}
