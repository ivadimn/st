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

    wmsize.flags = USPosition | USSize;
    XSetWMNormalHints(mydisplay, mywindow, &wmsize);
    wmhints.initial_state = NormalState;
    wmhints.flags = StateHint;
    XSetWMHints(mydisplay, mywindow, &wmhints);
    XStringListToTextProperty(&window_name, 1, &windowName);
    XSetWMName(mydisplay, mywindow, &windowName);
    XStringListToTextProperty(&icon_name, 1, &iconName);
    XSetWMIconName(mydisplay, mywindow, &iconName);

    /*     4. Установить ресурсы окон  */
    /*  5. Создать все остальные необходимые окна  */
    /*  6. Выбрать события для каждого окна  */
    /*  7. Сопоставить окна  */

    XMapWindow(mydisplay, mywindow);

    done = 0;
    while (done == 0)
    {
        XNextEvent(mydisplay, &myevent);
        switch (myevent.type)
        {
        case ButtonPress:
            break;
        }
    }
    XUnmapWindow(mydisplay, mywindow);
    XDestroyWindow(mydisplay, mywindow);
    XCloseDisplay(mydisplay);   
    return 0;

}