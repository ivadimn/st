#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "dml.h"
#include "vstrex.h"


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
        parent->joins = new_array(A_TYPE_POINTER, 8, sizeof(join_t*));
    put(parent->joins, parent->count_joins, &child);    
    parent->count_joins++;
}


join_t * create_join(join_t* parent, table_t *table, size_t count_lf, ...)
{
    join_t *join = (join_t*) malloc(sizeof(join_t));
    if (join == NULL)
        crit("Ошибка распределения памяти для объекта <join>");
      
    
    memcpy(&(join->table), table, sizeof(table_t));
    join->count_lf = count_lf;
    join->lf = NULL;
    join->joins = NULL;
    join->count_joins = 0;

    join->parent = parent;    
    if (join->parent) 
        __add_join(join->parent, join);

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

void print_join(join_t *join, int level)
{
    join_t *child;
    printf("-------------------- Level %d ---------------------------\n", level);
    printf("Parent: %p\n", (void*) join->parent);
    printf("Self: %p\n", (void*) join);
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
    for (size_t i = 0; i < join->count_joins; i++)
    {
        get(join->joins, i, &child);
        print_join(child, level + 1);
    }
}


void dml_select1(char* sql, join_t* join, varray_t* params)
{
    vstr_t* sel = vstr_create(2048);
    //size_t wrote = 0;
    char fs[SEL_BUFF_LEN];
    char fa[SEL_BUFF_LEN];
    join_t* child;
    str_fields(&(join->table), fs);
    snprintf(fa, 1023, "SELECT %s FROM %s ", fs, join->table.name);
    vstr_append(sel, fa);
    for (size_t i = 0; i < join->count_joins; i++)
    {
        get(join->joins, i, &child);
        snprintf(fa, 1023, "JOIN %s ON ", child->table.name);
        vstr_append(sel, fa);
        if (child->count_lf > 0)
        {
            snprintf(fa, 1023, "%s.%s %s %s.%s ", join->table.name, child->lf[0].f1, 
                                       child->lf[0].op, 
                                       child->table.name, child->lf[0].f2);
            vstr_append(sel, fa);                           
        }
        
        for (size_t j = 1; j < child->count_lf; j++)
        {
            snprintf(fa, 1023, "AND %s.%s %s %s.%s ", join->table.name, child->lf[j].f1, 
                                       child->lf[j].op, 
                                      child->table.name, child->lf[j].f2);
            vstr_append(sel, fa);
        }
        vstr_append(sel, ";");
    }
    
    vstr_get_data(sel, sql, SQL_QUERY_LEN);
    vstr_free(sel);
    
}