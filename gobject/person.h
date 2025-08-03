#ifndef _PERSON_H_
#define _PERSON_H_

#include <glib-object.h>

G_BEGIN_DECLS

#define TYPE_PERSON (person_get_type()) 
G_DECLARE_FINAL_TYPE(Person, person, DB, PERSON, GObject)

G_END_DECLS


#endif