#include <stdlib.h>
#include "tetris.h"

#ifndef TETRIS_C
#define TETRIS_C

tet_field* create_tet_field(int width, int height)
{
    tet_field* tetf = (tet_field*)malloc(sizeof(tet_field));
}

tet_game* create_tet_game(int field_width,              // ширина поля
                        int field_heght,                // высота поля
                        int figure_size,                // размер области фигуры
                        int count,                      // количество шаблонов фигур
                        tet_block* figures_template     // сведения о блоках соответствующих набору шаблонов
                    )
{
    tet_game* tetg = (tet_game*)malloc(sizeof(tet_game));
    tetg->field = create_tet_field(field_width, field_heght);
    tetg->figurest = create_tet_figurest(count, figure_size, figures_template);

    return tetg;

}

/*
* процедура, просчитывающая один игровой такт
*/
void calculate(tet_game* tetg);


#endif
