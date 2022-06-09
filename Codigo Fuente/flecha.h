#include "personaje.h"
#define VEL_FLECHA 7


/*******Se necesita tener una estructura para lista de flechas**********/

typedef struct nodoFlecha
{
    MALLA nodo;
    struct nodoFlecha*sig;
    int dir;
}*FLECHA;

//Se inicializar� la lista de flechas
void flecha_Inicializa(FLECHA*cabF);
//Esta es la creaci�n de un nodo en la lista de flechas, le asignar� sus cordenadas de dibujado
int flecha_Crea(FLECHA*nueva,MALLA*nodo);
//Cuando se precione el boton se a�adir� la flecha a la lista
void flecha_Inserta(FLECHA*cabF,PERSONAJE per);

void flechas_Modifica(FLECHA cabAuxF);
//Mostrar� con un recorrido las flechas
void flechas_Muestra(FLECHA cabAuxF);
//Liberar� las flechas que est�n fuera de la pantalla
void flechas_Libera (FLECHA*fle,int x_I,int x_F);

