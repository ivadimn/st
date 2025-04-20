/* Сначала рисуется окно с черно-белым шахматным узором. Затем на этом окне рисуются два
 прямоугольника. Фон каждого из этих
 двух окон белый. Затем создается GC с передним
 цветом черного. Этот GC используется для рисования переднего плана двух окон
 черным цветом. Третий создается с черным фоном и отображается
 поверх двух окон. Это наложенное окно затем удаляется. Этот
 процесс управляется событием с задержкой в ​​2 секунды в цикле событий.
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define backing_width 16
#define backing_height 16
static unsigned char backing_bits[] = {
0xff, 0x00, 
0xff, 0x00, 
0xff, 0x00, 
0xff, 0x00, 
0xff, 0x00, 
0xff, 0x00,
0xff, 0x00, 
0xff, 0x00, 
0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff,
0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff } ;

int main(int argc, char *argv[])
{
    Display *mydisplay;
    XSetWindowAttributes myat;
    Window mywindow, win1, win2, ontop;
    XWindowChanges alter;
    XSizeHints wmsize;
    XWMHints wmhints;
    XTextProperty windowName, iconName;
    XEvent myevent;
    GC gc;
    char *window_name = "Uncover";
    char *icon_name = "Uc";
    int screen_num, done;
    unsigned long valuemask;
    Pixmap back, back1, back2;
    int count;

    /* 1. открыть соединенте с сервером X window */
    mydisplay = XOpenDisplay("");
    if (mydisplay == NULL)
    {
        printf("Can't connect X server: %s\n", strerror( errno ));
        exit(1);
    }

    /* 2. создать верхнеуровневое (root) окно */
    screen_num = DefaultScreen(mydisplay);
    myat.background_pixel = WhitePixel(mydisplay, screen_num);
    //myat.background_pixel = 0x1F1F1FFF;
    myat.border_pixel = BlackPixel(mydisplay, screen_num);
    myat.event_mask = ButtonPressMask | ExposureMask;
    myat.save_under = True;
    valuemask = CWBackPixel | CWBorderPixel | CWEventMask | CWSaveUnder;

    printf("создаём окно с полным набором атрибутов\n");
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
    printf("создаём Pixmap\n");
    back = XCreatePixmapFromBitmapData(mydisplay, mywindow,
                                    (char*) backing_bits, backing_width, backing_height,
                                    BlackPixel(mydisplay, screen_num),
                                    WhitePixel(mydisplay, screen_num), 
                                    DefaultDepth(mydisplay, screen_num));                        

    printf("Задаём фон Pixmap\n");     
    XSetWindowBackgroundPixmap(mydisplay, mywindow, back);

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
    gc = XCreateGC(mydisplay, mywindow, 0, NULL);
    XSetForeground(mydisplay, gc, BlackPixel(mydisplay, screen_num));
    XSetBackground(mydisplay, gc, WhitePixel(mydisplay, screen_num));

    /*  5. Создать все остальные необходимые окна  */
    win1 = XCreateWindow(mydisplay, mywindow, 
                          100, 30, 50, 70, 2,
                          DefaultDepth(mydisplay, screen_num),
                          InputOutput,
                          DefaultVisual(mydisplay, screen_num),
                          valuemask, &myat);

    back1 = XCreatePixmapFromBitmapData(mydisplay, win1,
                                    (char*) backing_bits, backing_width, backing_height,
                                    0xFF00FF00,
                                    //BlackPixel(mydisplay, screen_num),
                                    0xFF0000FF,
                                    //WhitePixel(mydisplay, screen_num), 
                                    DefaultDepth(mydisplay, screen_num));                        

    XSetWindowBackgroundPixmap(mydisplay, win1, back1);                      
    win2 = XCreateWindow(mydisplay, mywindow, 
                          100, 150, 150, 30, 2,
                          DefaultDepth(mydisplay, screen_num),
                          InputOutput,
                          DefaultVisual(mydisplay, screen_num),
                          valuemask, &myat);                      
    myat.background_pixel = BlackPixel(mydisplay, screen_num);
    ontop = XCreateWindow(mydisplay, mywindow, 
                          120, 40, 80, 130, 2,
                          DefaultDepth(mydisplay, screen_num),
                          InputOutput,
                          DefaultVisual(mydisplay, screen_num),
                          valuemask, &myat);
    /*  6. Выбрать события для каждого окна  */
    /*  7. Сопоставить окна  */
    XMapWindow(mydisplay, mywindow); // Сделать окно видимым
    XMapWindow(mydisplay, win1); // Сделать окно видимым
    XMapWindow(mydisplay, win2); // Сделать окно видимым

    done = 0;
    count = 0;
    while (done == 0)
    {
        XFlush(mydisplay);
        XNextEvent(mydisplay, &myevent);
        sleep(2);
        switch (myevent.type)
        {
        case Expose :
            /* code */
            count++;
            switch (count)
            {
            case 1:
                printf("1\n");
                XFillRectangle(mydisplay, win1, gc, 0, 0, 50, 70);
                XFillRectangle(mydisplay, win2, gc, 0, 0, 150, 30);
                break;
            case 3:
                printf("3\n");
                XMapWindow(mydisplay, ontop);
                break;
            case 6:
                printf("6\n");
                XUnmapWindow(mydisplay, ontop);
                break;    
            case 9:
                printf("9\n");
                XUnmapWindow(mydisplay, win2);
                break;        
            default:
                break;
            }
            break;
        case ButtonPress:
            done = 1;
            break;    
        default:
            break;
        }
    }
    
    
    XUnmapWindow(mydisplay, mywindow);
    XDestroyWindow(mydisplay, mywindow);
    XCloseDisplay(mydisplay);   
    return 0;

}