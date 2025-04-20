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
    XEvent myevent;
    int screen_num, done;
    unsigned long valuemask;
    
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
    myat.background_pixel = 0x0000FF00;
    myat.border_pixel = BlackPixel(mydisplay, screen_num);
    valuemask = CWBackPixel;
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
   
    /*     4. Установить ресурсы окон  */
    /*  5. Создать все остальные необходимые окна  */
    /*  6. Выбрать события для каждого окна  */
    /*  7. Сопоставить окна  */

    XMapWindow(mydisplay, mywindow); // Сделать окно видимым

    XNextEvent(mydisplay, &myevent);
    
    return 0;

}