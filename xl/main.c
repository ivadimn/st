#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

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
    char *msg = "Hello world";

    /* 1. открыть соединенте с сервером X window */
    mydisplay = XOpenDisplay("");
    if (mydisplay == NULL)
    {
        printf("Can't connect X server: %s\n", strerror( errno ));
        exit(1);
    }
    

    /* 2. создать верхнеуровневое (root) окно */
    screen_num = DefaultScreen(mydisplay);
    //myat.background_pixel = WhitePixel(mydisplay, screen_num);
    myat.background_pixel = 0x1F1F1FFF;
    myat.border_pixel = BlackPixel(mydisplay, screen_num);
    myat.event_mask = ButtonPressMask | ExposureMask;
    valuemask = CWBackPixel | CWBorderPixel | CWEventMask;
    /* создаём окно с полным набором атрибутов*/
    mywindow = XCreateWindow(mydisplay, 
                            RootWindow(mydisplay, screen_num),  // родительское окно 
                            200, 200,                           // координаты левого верхнего угла
                            600, 400,                           // ширина и высота окна
                            2,                                  // толщина рамки вокруг окна
                            DefaultDepth(mydisplay, screen_num),// количество разрядов, для кодирования цвета   
                            /* класс окна. Допустимые значения: 
                            InputOutput (ввод и вывод), 
                            InputOnly (только ввод) 
                            или CopyFromParent (установить тип как у окна-предка) */
                            InputOutput,                         // класс окна ввод и вывод
                            DefaultVisual(mydisplay, screen_num),// визуальные характеристики окна. 
                                                                 // Если указать CopyFromParent, данные будут взяты у окна-предка; 
                            valuemask,                           // маска, указывающая, какие параметры из аргумента attributes следует указывать; 
                            &myat);                              // 

    /* 3. дайте подсказки диспетчеру окон */

    wmsize.flags = USPosition | USSize; // запрашивать у пользователя позицию и размер
                                        // можно двигать и менять размер
    XSetWMNormalHints(mydisplay, mywindow, &wmsize); //Установка геометрических параметров окна для нормального состояния
    wmhints.initial_state = NormalState; // обычное состояние
    wmhints.flags = StateHint;
    XSetWMHints(mydisplay, mywindow, &wmhints); // Установка атрибутов окна для оконного менеджера
    XStringListToTextProperty(&window_name, 1, &windowName);
    XSetWMName(mydisplay, mywindow, &windowName); // 
    XStringListToTextProperty(&icon_name, 1, &iconName);
    XSetWMIconName(mydisplay, mywindow, &iconName);

    /*     4. Установить ресурсы окон  */
    /*  5. Создать все остальные необходимые окна  */
    /*  6. Выбрать события для каждого окна  */
    /*  7. Сопоставить окна  */

    XMapWindow(mydisplay, mywindow); // Сделать окно видимым

    done = 0;
    while (done == 0)
    {
        XNextEvent(mydisplay, &myevent);
        switch (myevent.type)
        {
        case Expose:
            printf("get Expose\n");
            XFillRectangle(mydisplay, mywindow, DefaultGC( mydisplay, screen_num ), 20, 20, 20, 20 ); 
            XDrawString(mydisplay, mywindow, DefaultGC( mydisplay, screen_num ), 
                        50, 50, msg, strlen(msg)); 
            break;
        case ButtonPress:
            printf("get ButtonPress\n");
            putchar('\a');
            done = 1;
            break;
        }
    }
    XUnmapWindow(mydisplay, mywindow);
    XDestroyWindow(mydisplay, mywindow);
    XCloseDisplay(mydisplay);   
    return 0;

}