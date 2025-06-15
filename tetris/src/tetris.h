#ifndef TETRIS_H
#define TETRIS_H


typedef struct tet_block
{
    int b;
} tet_block;

// падающая фигура
typedef struct tet_figure
{
    int x;                      // координаты
    int y;
    int size;                   // пространство из блоков которое имеет фигура - это квадрат со стороной size
    tet_block* blocks;          // массив блоков соотвествующий фигуре
};


typedef struct tet_figurest
{
    int count;                  // количество фигур
    int size;                   // длина стороны квадратной области которая занимает фигура
    tet_block* blocks;          // непрерывная обласит памяти ссылающаяся на все шаблоны сразу
} tet_figurest;


/*
* игровое поле
*/
typedef struct tet_field
{
    int width;
    int height;
    tet_block* blocks;
} tet_field;

/*
* структура определяющая игру
*/
typedef struct tet_game
{
    tet_field* field;           // игровое поле
    tet_figure* figure;         // падающая фигура
    tet_figurest* figurest;     // все типовые фигур
} tet_game;

tet_game* create_tet_game(int field_width,              // ширина поля
                        int field_heght,                // высота поля
                        int figure_size,                // размер области фигуры
                        int count,                      // количество шаблонов фигур
                        tet_block* figures_template     // сведения о блоках соответствующих набору шаблонов
                    );

/*
* процедура, просчитывающая один игровой такт
*/
void calculate(tet_game* tetg);


#endif
