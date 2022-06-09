#include <stdio.h>
#include <stdlib.h>
#include "personaje.h"
#include "sprite.h"
#include "graphics.h"


/****Comentado****/
void personaje_Ini(PERSONAJE*per,int vida,int ptos)
{
    //Copiamos las características proporcionadas al personaje
    per->vida=vida;
    per->puntos=ptos;
}


/******Comentado******/
void personaje_Reacomoda(PERSONAJE*per,int dir)
{
    //Solo avanzará si se le da alguna dirección
    if(dir)
    {
        //Se "reinicia" el nodo original
        int tipo=per->ptrPer->tipo,puntos;
        per->ptrPer->tipo=0;
        SPRITE *copia;
        copia=per->ptrPer->sprt;
        per->ptrPer->sprt=NULL;
        //Se revisa si el nodo siguiente tiene un tesoro para asignar los puntos antes de reasignar el tipo
        switch (dir)
        {
            case DIR_DERECHA:
                if(per->ptrPer->nodoDer->tipo==TESORO)
                {
                    puntos=rand()%40;
                    per->puntos+=puntos;
                }
                else
                {
                    if(per->ptrPer->nodoDer->tipo==ENEMIGO)
                        per->vida--;
                }
                per->ptrPer=per->ptrPer->nodoDer;
                break;
            case DIR_ABAJO:
                if(per->ptrPer->nodoAba->tipo==TESORO)
                {
                    puntos=rand()%50;
                    per->puntos+=puntos;
                }
                else
                {
                    if(per->ptrPer->nodoAba->tipo==ENEMIGO)
                        per->vida--;
                }
                per->ptrPer=per->ptrPer->nodoAba;
                break;
            case DIR_IZQUIERDA:
                if(per->ptrPer->nodoIzq->tipo==TESORO)
                {
                    puntos=rand()%60;
                    per->puntos+=puntos;
                }
                else
                {
                    if(per->ptrPer->nodoIzq->tipo==ENEMIGO)
                        per->vida--;
                }
                per->ptrPer=per->ptrPer->nodoIzq;
                break;
            case DIR_ARRIBA:
                if(per->ptrPer->nodoArri->tipo==TESORO)
                {
                    puntos=rand()%80;
                    per->puntos+=puntos;
                }
                else
                {
                    if(per->ptrPer->nodoArri->tipo==ENEMIGO)
                        per->vida--;
                }
                per->ptrPer=per->ptrPer->nodoArri;
                break;
        }
        //Se pasan los datos copiados el siguiente nodo
        per->ptrPer->sprt=copia;
        per->ptrPer->tipo=tipo;

    }

}


/***Comentado****/
//Solo imprime en una sona determinada el nivel, la vida, las flechas restantes y el puntaje
void personaje_MuestraEstadisticas(PERSONAJE per,int fle,int nivel)
{
    int x_I=0,y_I=getmaxy()-getmaxy()/10;
    char str[3],fullStr[9];
    setfillstyle(SOLID_FILL,BLACK);
    rectangle(x_I,y_I,getmaxx()-100,getmaxy());
    floodfill(x_I+5,y_I+5,WHITE);
    settextstyle(3,HORIZ_DIR,3);
    setcolor(WHITE);
    x_I+=30;
    y_I+=30;

    sprintf(str,"%d",nivel);
    strcpy(fullStr,"Nivel:");
    strcat(fullStr,str);
    outtextxy(x_I,y_I,fullStr);
    sprintf(str,"%d",per.vida);
    strcpy(fullStr,"Vida:");
    strcat(fullStr,str);
    outtextxy(x_I+100,y_I,fullStr);
    sprintf(str,"%d",per.puntos);
    strcpy(fullStr,"Puntos:");
    strcat(fullStr,str);
    outtextxy(x_I+200,y_I,fullStr);
    sprintf(str,"%d",fle);
    strcpy(fullStr,"flechas:");
    strcat(fullStr,str);
    outtextxy(x_I+300,y_I,fullStr);
}
