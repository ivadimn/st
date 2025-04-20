#ifndef __TABLE_H__
#define __TABLE_H__

#include <gtk/gtk.h>

typedef struct 
{
    guint id;
    char* name;
    
} pd_t;

enum
{
    C_ID, C_NAME, N_COL
};

GtkWidget *create_table();

#endif