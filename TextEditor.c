#include <stdlib.h>
#include "TextEditor.h"


void text_init(Text *txt, int max_x, int max_y)
{
    txt=malloc(sizeof(Text));
    insert_list(&(txt->data), '\n', 0);
    txt->cur_x=0;
    txt->cur_y=0;
    txt->max_x=max_x;
    txt->max_y=max_y;
}

void text_down(Text *txt)
{
    if(txt->cur_y==txt->max_y) return;
    txt->cur_y++;
}
