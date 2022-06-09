//#include "boton.h"
#include "graphics.h"
#include "menu.h"
#include "malla.h"
#include "sprite.h"
/*******************************

    Este videojuego fue programado pensando en simular el paradigma orientado a objetos
    Tambien se tiene en mente el paradigma orientado a eventos

*******************************/


/*************Función principal**************/
int main()
{
    initwindow(640,640,"juego"); //inicializamos la ventana


    /*********Malla**********/

    //Entramos al menu
    menu();

    return 0;
}
