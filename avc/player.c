#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <gtk-3.0/gtk/gtk.h>

#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/opt.h>
#include <libavutil/imgutils.h>
#include <libswresample/swresample.h>

#include <gstreamer-1.0/gst/gst.h>
#include <gstreamer-1.0/gst/video/videooverlay.h>

#include <gdk/gdk.h>
#include <gdk/gdkx.h>

GtkWidget *main_window;

int main(int argc, char** argv)
{
    gtk_init(&argc, &argv);

    main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(main_window), "Video Editor");

    g_signal_connect(main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(main_window);
    gtk_main();

    return 0;
}

