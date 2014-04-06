#ifndef TEXTEDITOR_H_INCLUDED
#define TEXTEDITOR_H_INCLUDED

#include "List.h"

typedef struct
{
    List data;
    int cur_x,
        cur_y,
        max_x,
        max_y,
        max_height; //0-без ограничений
}Text;

void text_init(Text *txt, int max_x, int max_y);
void text_set_position(Text *txt, int x, int y);
void text_down(Text *txt);
void text_up(Text *txt);
void text_left(Text *txt);
void text_right(Text *txt);

void text_insert(Text *txt, char symbol);
//void text_insert(Text *txt, List *ins);

void text_delete(Text *txt);
//void text_delete(Text *txt, int begin, int end);

#endif // TEXTEDITOR_H_INCLUDED
