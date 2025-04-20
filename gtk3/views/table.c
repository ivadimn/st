/*** 
 * Пример GTK таблицы
*/
#include "../app.h"
#include "table.h"

pd_t pd[4] = {
    {
        .id = 1,
        .name = "Иванов"
    },
    {
        .id = 2,
        .name = "Петров"
    },
    {
        .id = 3,
        .name = "Сидоров"
    },
    {
        .id = 4,
        .name = "Кузнецов"
    }
};

static void show_message()
{
    GtkWidget *dialog = NULL;
    GtkWidget *win = get_main_window();    
    dialog = gtk_message_dialog_new(GTK_WINDOW(win), GTK_DIALOG_MODAL, 
                                    GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, "Сообщение показано");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

GtkWidget *create_table()
{

    GtkWidget *vbox, *hbox;
    GtkListStore *buffer;
    GtkWidget *table; 
    GtkTreeViewColumn *column;
    GtkTreeIter iter;
    GtkCellRenderer *renderer;
    GtkWidget *btn_close;

    //создание буфера таблицы
    buffer = gtk_list_store_new(N_COL, G_TYPE_UINT, G_TYPE_STRING);
    
    for (size_t i = 0; i < 4; i++)
    {
        gtk_list_store_append(buffer, &iter);
        gtk_list_store_set(buffer, &iter,
                                C_ID, pd[i].id,
                                C_NAME, pd[i].name,
                                -1);
    }
    // создание таблицы
    table = gtk_tree_view_new_with_model(GTK_TREE_MODEL(buffer));

    //добавление столбцов в таблицу
    renderer = gtk_cell_renderer_text_new();
    column = gtk_tree_view_column_new_with_attributes(
             "Ид.", renderer, "text", C_ID, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(table), column);
    
    column = gtk_tree_view_column_new_with_attributes(
             "Наименование", renderer, "text", C_NAME, NULL);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(table), column);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    
    btn_close = gtk_button_new_with_label("Сообщение");
    
    
    g_signal_connect(G_OBJECT(btn_close), "clicked", G_CALLBACK(show_message), NULL);
    gtk_box_pack_start(GTK_BOX(hbox), btn_close, TRUE, TRUE, 10);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(vbox), table, TRUE, TRUE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, TRUE, 5);
    
    return vbox;

}