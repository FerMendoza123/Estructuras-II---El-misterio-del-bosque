/*******************

    En este archivo hay que poner la estructura del sprite
        *será un apuntador
    Probablemente tambien la apertura
**************/

#ifndef _SPRITE
#define _SPRITE 1
typedef struct
{
    char name[25];
    int row,col;
    int cellsize;
    int pixSize;
    int**grid;
}SPRITE;
#endif

void sprite_Dibuja(SPRITE gr,int xi, int yi,int pS);
void sprite_Dibuja_Reves(SPRITE gr,int xi, int yi,int pS);
int sprite_Lee(SPRITE*gr,char name[]);
