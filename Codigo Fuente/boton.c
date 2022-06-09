#include "boton.h"
#include <string.h>
#include "graphics.h"

/*******Comentado*******/
void boton_Inicializate(BOTON*btn,char*texto,int x,int y,int ancho,int alto,int color)
{
    //Copiamos los parametros insertados en la estructura

    //Coordenadas de posicion de inicio
    btn->x=x;
    btn->y=y;
    //Dimensiones
    btn->ancho=ancho;
    btn->alto=alto;
    //Color
    btn->c=color;
    //Etiqueta
    strcpy(btn->texto,texto);
}

/**********Comentado*******/
void boton_Dibuja(BOTON bt)
{
    //Pone el color de dibujo en blanco (el borde del botón)
    setcolor(WHITE);
    //color especificado previamente y tipo de llenado solido
    setfillstyle(SOLID_FILL,bt.c);
    //Dibuja rectangulo (borde)
    rectangle(bt.x, bt.y, bt.x+bt.ancho, bt.y+bt.alto);
    //Rellena tomando como referencia un punto dentro del rectangulo y el color de dibujo
    floodfill(bt.x+1,bt.y+1,getcolor());
    //Dibuja la etiqueta (texto) con el color de dibujo
    settextstyle(8,HORIZ_DIR,1);
    outtextxy(bt.x+15,bt.y+15,bt.texto);
}

/**********Comentado*******/
int boton_Verificate(BOTON btn)
{
    int res=0;
    //Cuando se dió clic se checa que las cordenadas están sobre un boton
    if( mousex()>btn.x && mousex()<btn.x+btn.ancho &&
        mousey()>btn.y && mousey()<btn.y+btn.alto )
    {
        //Si es así regresaremos un 1
        res=1;

    }
    return res;
}

