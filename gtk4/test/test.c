#include <gtk/gtk.h>

int main(void)
{
    PangoContext *c;
    GObject *o;

    c = pango_context_new();
    o = G_OBJECT(c);

    g_object_unref(o);

    return 0;
}
