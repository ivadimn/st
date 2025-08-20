#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "dml.h"


table_t* new_table(char* name, size_t count_fields, ...)
{
    table_t *t = (table_t*) malloc(sizeof(table_t));
    if (t == NULL)
        return NULL;
   
    strncpy(t->name, name, DBOBJECT_NAME_LEN - 1);
    
    t->fields = NULL;
    t->fcount = 0;
    if (count_fields == 0)
        return t;
    
    t->fields = (field_t*) malloc(sizeof(field_t) * count_fields);
    if (t->fields == NULL)
        return NULL;
        
    t->fcount = count_fields;

    va_list fs;
    va_start(fs, count_fields);
    for (size_t i = 0; i < count_fields; i++)
    {
        t->fields[i].type = TYPE_TEXT;
        strncpy(t->fields[i].name, va_arg(fs, char*), DBOBJECT_NAME_LEN);
           
    }
    va_end(fs);
    return t;
    
}

void free_table(table_t *t)
{
    if (t->fields != NULL)
        free(t->fields);
    free(t);    
}


void str_fields(table_t *t, char* buf)
{
    size_t wrote = 0;
    if (t->fcount == 0)
        return;
    
    wrote = snprintf(buf, DBOBJECT_NAME_LEN * 2 - 1, " %s.%s", t->name, t->fields[0].name);
    for (size_t i = 1; i < t->fcount; i++)
    {
        wrote += snprintf(buf + wrote, DBOBJECT_NAME_LEN * 2 - 1, ", %s.%s", t->name, t->fields[i].name);
    }
    
}

void print_table_info(table_t *t)
{
    printf("Table name: %s\n", t->name);
    for (size_t i = 0; i < t->fcount; i++)
    {
        printf("\tField name: %s type: %d pk is %d\n", t->fields[i].name, t->fields[i].type, t->fields[i].pk);
    }
    
}

/*
* функции join_t
*/

void __add_join(join_t* parent, join_t* child)
{
    if (parent->joins == NULL)
    {
        /* code */
    }
    
}


join_t * create_join(join_t* parent, table_t *table, size_t count_lf, ...)
{
    join_t *join = (join_t*) malloc(sizeof(join_t));
    if (join == NULL)
        crit("Ошибка распределения памяти для объекта <join>");
    
    join->parent = parent;    
    memcpy(&(join->table), table, sizeof(table_t));
    join->count_lf = count_lf;
    join->lf = NULL;
    join->joins = NULL;

    if (count_lf == 0)
        return join;
    
    join->lf = (link_fields_t*) malloc(sizeof(link_fields_t) * count_lf);
    
    va_list fs;
    va_start(fs, count_lf);
    for (size_t i = 0; i < count_lf; i++)
    {
        memcpy(&(join->lf[i]), va_arg(fs, link_fields_t*), sizeof(link_fields_t));
    }
    va_end(fs);
    if (parent)
    {
        /* code */
    }
    
    return join;
}

void free_join(join_t* join)
{
    if (join->lf)
        free(join->lf);
    if (join->joins)
        del_array(join->joins);
    free(join);
}

void print_join(join_t *join)
{
    
    printf("Table name: %s\n", join->table.name);
    for (size_t i = 0; i < join->table.fcount; i++)
    {
        printf("\tField name: %s type: %d pk is %d\n", join->table.fields[i].name, 
            join->table.fields[i].type, join->table.fields[i].pk);
    }    
    if (join->lf)
    {
        printf("Link fields:\n");
        for (size_t i = 0; i < join->count_lf; i++)
        {
            printf("%s %s %s\n", join->lf[i].f1, join->lf[i].op, join->lf[i].f2);
        }
    }
}


void dml_select1(char* sql, varray_t* tables, field_t* fields, varray_t* params)
{
    
}