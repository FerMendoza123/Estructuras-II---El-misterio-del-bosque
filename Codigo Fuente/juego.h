#include "malla.h"
#include "personaje.h"
#include "boton.h"

void juego(int*puntos);
void iniciaNivel(MALLA*f,LISTA*l,PERSONAJE*per,int nivel);
void mallaMuestraPaginas(MALLA fondo,BOTON salir, int nivel);
void mueveEnemigos(MALLA fondo,PERSONAJE*per,int x_I,int x_F);
