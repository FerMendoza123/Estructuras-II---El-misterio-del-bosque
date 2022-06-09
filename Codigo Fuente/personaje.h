#include "sprite.h"
#include "malla.h"
#ifndef _PER
#define _PER 5

#define DIR_DERECHA 3
#define DIR_IZQUIERDA 1
#define DIR_ABAJO 4
#define DIR_ARRIBA 2

#define CAB_NORM 1
#define CAB_ATTACK 2
#define CAB_ATTACK2 3
#define CAB_RUN 4


typedef struct
{
    MALLA ptrPer;
    int dir;
    int vida;
    int puntos;
}PERSONAJE;

#endif

void personaje_Reacomoda(PERSONAJE*per,int dir);
void personaje_Ini(PERSONAJE*per,int vida,int ptos);
void personaje_MuestraEstadisticas(PERSONAJE per,int fle,int nivel);
