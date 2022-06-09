#include "sprite.h"

#define TAMPIX 3
#define NUMPIX 20 //Este numero cambia dependiendo de el estandar de columnas y renglones del sprite
                  //Yo estoy usando cada sprite de 20x20
#define TAMSCREEN 540

#define NADA 0
#define ARBOL 1
#define MURO 2
#define ENEMIGO 3
#define PERS_CONS 4
#define TESORO 5

#ifndef _MALLA
#define _MALLA 1
typedef struct nodoMalla
{
    struct nodoMalla*nodoArri;
    struct nodoMalla*nodoAba;
    struct nodoMalla*nodoIzq;
    struct nodoMalla*nodoDer;
    SPRITE *sprt; /***Aquí va la informacion*/
    int tipo;
    int x_I,y_I;//Coordenadas de inicio del segmento de la malla
}*MALLA;

typedef struct nodoLista
{
    //El sprite tiene el nombre incluido, por ejemplo si ponemos un apuntador desde un nodo a nube tendremos que buscar
    //a nube para hacer que apunte a este sprite
    SPRITE sprt;
    nodoLista*sig;
}*LISTA;
#endif


void malla_Inicializa(MALLA*cabM);
int malla_CreaNodo(MALLA*nuevo,int dato);
int malla_Construlle(MALLA*cabM,int nRen,int nCol,LISTA*li,int level);
void malla_Muestra(MALLA cabM);
void malla_Remuestra(MALLA cabM, int dir);
void malla_Elimina(MALLA*cabM);
void malla_Busca(MALLA*sp,MALLA cabM,int tipo);
void malla_Reacomoda(MALLA fondo,int dir);

void lista_Inicializa(LISTA*li);//Solo pondremos la lista en null
int lista_Crea(LISTA*li);
int lista_CreaNodo(LISTA*nuevo);
void lista_Busca(SPRITE**ptr,char*nombre,LISTA*li);
void lista_Libera(LISTA li);
