#include "flecha.h"
#include <stdlib.h>
#include <stdio.h>
#include "graphics.h"
#ifndef _FAN
#define _FAN 7

#endif

/**Comentado**/
//Se inicializará la lista de flechas
void flecha_Inicializa(FLECHA*cabF)
{
    *cabF=NULL;
}

//Esta es la creación de un nodo en la lista de flechas
int flecha_Crea(FLECHA*nueva)
{
    int res=0;
    //Asignacion de memoria
    *nueva=(FLECHA)malloc(sizeof(struct nodoFlecha));
    if(*nueva)
    {
        //Asignación de datos
        (*nueva)->sig=NULL;
        res=1;
    }
    return res;
}


/******Comentado****/
//Cuando se precione la tecla se añadirá la flecha a la lista
void flecha_Inserta(FLECHA*cabF,PERSONAJE per)
{
    FLECHA nueva;
    if(flecha_Crea(&nueva))
    {
        if(per.dir==DIR_DERECHA)
            nueva->nodo=per.ptrPer->nodoDer;
        else
            nueva->nodo=per.ptrPer->nodoIzq;
        if(nueva->nodo->tipo==ENEMIGO)
        {
            nueva->nodo->tipo=0;
            nueva->nodo->sprt=NULL;
        }
        nueva->dir=per.dir;
        nueva->sig=*cabF;
        *cabF=nueva;
    }
}

/****Comentado****/
//Esta función hace que la flecha apunte al siguente nodo para que se dibuje sobre él
void flechas_Modifica(FLECHA cabAuxF)
{
    while(cabAuxF)
    {
        if(cabAuxF->dir==DIR_DERECHA)
            if(cabAuxF->nodo->nodoDer)
                cabAuxF->nodo=cabAuxF->nodo->nodoDer;
        if(cabAuxF->dir==DIR_IZQUIERDA)
            //Si el siguiente nodo no apunta no las mueve
            if(cabAuxF->nodo->nodoIzq)
                cabAuxF->nodo=cabAuxF->nodo->nodoIzq;
        //Si el nodo en el que se mueve tiene un enemigo el tipo se cambia a 0 y el enemigo desaparece
        if(cabAuxF->nodo->tipo==ENEMIGO)
        {
            cabAuxF->nodo->tipo=0;
            cabAuxF->nodo->sprt=NULL;
        }
        cabAuxF=cabAuxF->sig;
    }
}


/****Comentado***/
//Esta función recorre la lista de flechas y las va dibujando en su nodo correspondiente
void flechas_Muestra(FLECHA cabAuxF)
{
    int color=getcolor();
    setcolor(WHITE);
    while(cabAuxF)
    {
        if(cabAuxF->nodo->tipo!=ARBOL&&cabAuxF->nodo->tipo!=MURO)
            outtextxy(cabAuxF->nodo->x_I+20,cabAuxF->nodo->y_I+20,"-");
        cabAuxF=cabAuxF->sig;
    }
    setcolor(color);
}


/**Comentado***/
//Liberará las flechas que estén fuera de la pantalla para que no se dibujen
void flechas_Libera (FLECHA*fle,int x_I,int x_F)
{
    FLECHA aux=*fle,ant,aux2;
    while(aux)
    {
        if(aux->nodo->x_I<x_I||aux->nodo->x_I>=x_F)
        {
            aux2=aux;
            if(aux==*fle)
            {
                aux=*fle=aux->sig;
            }
            else
            {
                aux=aux->sig;
                ant->sig=aux;
            }
            free(aux2);
        }
        else
        {
            ant=aux;
            aux=aux->sig;
        }
    }
}
