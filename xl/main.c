#include <X11/Xlib.h>
#include <X11/Xutil.h>

int main(int argc, char* argv[])
{
    Display *mydisplay;
    XSetWindowAttributes myat;
    Window mywindow;
    XSizeHints wmsize;
    XWMHints wmhints;
    XTextProperty windowName, iconName;
    XEvent myevent;
    char *window_name = "Basic";
    char *icon_name = "Ba";
    int screen_num, done;
    unsigned long valuemask;

    /* 1. открыть соединенте с сервером X window */
    mydisplay = XOpenDisplay("");

    /* 2. создать верхнеуровневое (root) окно */
    screen_num = DefaultScreen(mydisplay);
    myat.background_pixel = WhitePixel(mydisplay, screen_num);
    myat.border_pixel = BlackPixel(mydisplay, screen_num);
    myat.event_mask = ButtonPressMask;
    valuemask = CWBackPixel | CWBorderPixel | CWEventMask;
    mywindow = XCreateWindow(mydisplay, RootWindow(mydisplay, screen_num), 
                            200, 200, 600, 400, 2,
                            DefaultDepth(mydisplay, screen_num), InputOutput, 
                            DefaultVisual(mydisplay, screen_num), 
                            valuemask, &myat);

    /* 3. дайте подсказки диспетчеру окон */
    

}