#include "juego.h"
#include "personaje.h"
#include "malla.h"
#include "conio.h"
#include "graphics.h"
#include "records.h"
#include <stdio.h>
#include <stdlib.h>
#include "flecha.h"
#include <time.h>

/****Comentado******/
void juego(int*puntos)
{
    //Esta bandera servirá para saber en que dirección dibujar el personaje, si está retrocediendo será hacia la izquierda
    int flagDir=0;
    //Bandera para saber que nivel leer
    int nivel=1;
    //Necesittamos estas variables para saber cuando quitar una flecha
    int x_I_Screen,x_F_Screen;
    //Declaramos el apuntador para leer el fondo
    MALLA fondo;
    //Estructuras para guardar las posiciones de los personajes
    PERSONAJE per;
    //Boton de salir
    BOTON salir;
    boton_Inicializate(&salir,"salir",getmaxx()-80,getmaxy()-40,80,40,BLUE);
    //Lista de  flechas
    FLECHA fle;
    //Contador de flechas
    int contF=2;
    flecha_Inicializa(&fle);
    //Usaré direcciones aleatorias para los movimientos de los fantasmas
    srand(time(NULL));
    //Necesito las dos variables de tiempo para decidir cuando se mueven los fantasmas
    time_t t_Actual,t1,t2;
    //Lista para leer los sprites
    LISTA lista;
    lista_Inicializa(&lista);
    //Si se puede crear la lista de sprites entonces
    if(lista_Crea(&lista))
    {
        //Se iniciará el nivel
        iniciaNivel(&fondo,&lista,&per,nivel);
        //Se busca al nodo del enemigo
        //El personaje iniciará viendo hacia la derecha de la pantalla
        per.dir=DIR_DERECHA;
        //Coordenadas utiles
        x_I_Screen=fondo->x_I;
        x_F_Screen=x_I_Screen+TAMPIX*NUMPIX*7;
    }
    else
        //Si no se pudo entonces saldra de la función
        return;
    //Le daremos las características necesarias al personaje y al fantasma
    personaje_Ini(&per,4,0);
    //Se necesita esta variable para cuando se precione una tecla guardarla
    char tecla;
    //Se inicia
    int page=0;
    //Se tiene que dibujar en las dos páginas para poder paginar solo los cuadros necesarios
    mallaMuestraPaginas(fondo,salir,nivel);
    //Solo el movimiento del personaje y el scroll serán activados con los controles
    time(&t1);
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            if(boton_Verificate(salir))
            {
                //Si se cliquea este boton se sale al menu de inicio
                *puntos=0;
                break;
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }
        //Si se presiona una tecla se busca cual fue
        if(kbhit())
        {
            fflush(stdin);
            tecla=getch();
            if(tecla=='c'&&contF>0)
            {
                flecha_Inserta(&fle,per);
                time(&t2);
                contF--;
            }
            else
            //Si se presiona alguna de WASD es para el movimiento del personaje
            if(tecla=='w'&&per.ptrPer->nodoArri&&per.ptrPer->nodoArri->tipo!=ARBOL&&per.ptrPer->nodoArri->tipo!=MURO)
            {
                //Se decide hacia donde avanzará
                flagDir=DIR_ARRIBA;
            }
            else
            {
                if(tecla=='a'&&per.ptrPer->nodoIzq&&per.ptrPer->nodoIzq->tipo!=ARBOL&&per.ptrPer->nodoIzq->tipo!=MURO)
                {
                    //Si es A o D hay que cambiar la orientación del personaje
                    per.dir=flagDir=DIR_IZQUIERDA;
                }
                else
                {
                    if(tecla=='s'&&per.ptrPer->nodoAba&&per.ptrPer->nodoAba->tipo!=ARBOL&&per.ptrPer->nodoAba->tipo!=MURO)
                    {
                        flagDir=DIR_ABAJO;
                    }
                    else
                        if(tecla=='d')
                        {
                            //Si hay un nodo a la derecha
                            if(per.ptrPer->nodoDer)
                            {
                                //Y si es diferente de los nodos arbol o muro
                                if(per.ptrPer->nodoDer->tipo!=ARBOL&&per.ptrPer->nodoDer->tipo!=MURO)
                                    //avanzará
                                    per.dir=flagDir=DIR_DERECHA;
                            }
                            else
                            {
                                //Si no apunta es el final del nivel
                                nivel++;
                                //Hay que eliminar el nivel
                                malla_Elimina(&fondo);
                                //Solo hay 3 niveles pero pueden agregarse mas
                                if(nivel<=3)
                                {
                                    //Y leer el siguiente
                                    iniciaNivel(&fondo,&lista,&per,nivel);
                                    //Y se dibuja de nuevo en las dos páginas
                                    mallaMuestraPaginas(fondo,salir,nivel);
                                    //Se busca de nuevo al enemigo
                                }
                                else
                                {
                                    *puntos=per.puntos;
                                    break;
                                }
                            }
                        }
                }
            }
            //Mueve al nodo del personaje
            personaje_Reacomoda(&per,flagDir);
            if(per.vida<=0)
            {
                *puntos=0;
                break;
            }
            //una vez que se movio el personaje quitamos el movimiento
            flagDir=0;
            //Si el personaje excede el borde izzquierdo o derecho la pantalla se mueve
            if(per.ptrPer->x_I>x_F_Screen)
            {
                malla_Reacomoda(fondo,DIR_DERECHA);
                mallaMuestraPaginas(fondo,salir,nivel);
            }
            else
                if(per.ptrPer->x_I<(getmaxx()-TAMSCREEN)/2)
                {
                    malla_Reacomoda(fondo,DIR_IZQUIERDA);
                    mallaMuestraPaginas(fondo,salir,nivel);
                }

        }
        //checa y libera constantemente aquellas flechas que ya no son útiles
        flechas_Libera(&fle,x_I_Screen,x_F_Screen);
        //Cada sierto tiempo mueve los enemigos, entre mayor sea el nivel menos tiempo espera
        time(&t_Actual);
        if(t_Actual-t1>=3-nivel)
        {
            mueveEnemigos(fondo,&per,x_I_Screen,x_F_Screen);
            time(&t1);
        }
        //Se tienen que mostrar las flechas en las dos páginas porque son muy rápidas
        flechas_Muestra(fle);
        setactivepage(page);
        //cleardevice();
        flechas_Muestra(fle);
        //Se muestran los nodos modificables de la malla
        malla_Remuestra(fondo,per.dir);
        //Muestra las estadisticas
        personaje_MuestraEstadisticas(per,contF,nivel);
        setvisualpage(page);
        //Cambia la página
        page=page==1? 0 : 1;
        //Modifica la posición de las flechas
        flechas_Modifica(fle);
        //Solo se dibujará una vez el escenario, después solo se redibujará el personaje los enemigos y las flechas

        //aux=*per.cab;
    }
    //Cuando se sale del juego libera toda la memoria pedida
    malla_Elimina(&fondo);
    lista_Libera(lista);
}


/***********Comentado********/
void iniciaNivel(MALLA*f,LISTA*l,PERSONAJE*per,int nivel)
{
    //Se inicializa la malla
    malla_Inicializa(f);
    //Se insertan los nodos con los renglones y columnas de los parametros y el nivel especificado
    malla_Construlle(f,5,18,l,nivel);
    //Se busca el nodo donde está el personaje
    malla_Busca(&per->ptrPer,*f,PERS_CONS);
}

/********Comentado******/
void mallaMuestraPaginas(MALLA fondo, BOTON salir, int nivel)
{
    //Se dibujará todo lo que no se mueve en las dos páginas
    int page=0;
    char niv[8],num[2];
    setactivepage(page);
    cleardevice();
    malla_Muestra(fondo);
    boton_Dibuja(salir);

    //Se prepara la cadena para indicar el nivel
    sprintf(niv,"%s","Nivel:");
    sprintf(num,"%d",nivel);
    strcat(niv,num);
    //outtextxy(30,getmaxy()-getmaxy()/10+30,niv);

    setvisualpage(page);
    //Se cambia de página
    page=page==1? 0 :1;
    setactivepage(page);
    cleardevice();
    malla_Muestra(fondo);
    boton_Dibuja(salir);
    //outtextxy(30,getmaxy()-getmaxy()/10+30,niv);
}


/***Comentado***/
//Esta función recorre toda la malla moviendo de nodo a los enemigos
void mueveEnemigos(MALLA fondo,PERSONAJE*per,int x_I,int x_F)
{
    MALLA aux;
    SPRITE*copia;//Se copia el apuntador al sprite del enemigo en la lista
    int dir;
    while(fondo)
    {
        aux=fondo;
        while(aux)
        {
            //Solo mueve a los que están en la zona de la pantalla
            if(aux->x_I<x_F+NUMPIX*TAMPIX&&aux->x_I>=x_I)
            {
                if(aux->tipo==ENEMIGO)
                {
                    //La dirección se decide de manera aleatoria
                    dir=rand()%5;
                        switch(dir)
                        {
                            case DIR_ABAJO:
                                if(aux->nodoAba&&aux->nodoAba->tipo!=MURO&&aux->nodoAba->tipo!=ARBOL&&aux->nodoAba->tipo!=ENEMIGO)
                                {
                                    copia=aux->sprt;
                                    aux->sprt=NULL;
                                    aux->tipo=0;

                                    if(aux->nodoAba->tipo!=PERS_CONS)
                                    {
                                        aux->nodoAba->sprt=copia;
                                        aux->nodoAba->tipo=ENEMIGO;
                                    }
                                    else
                                        per->vida--;
                                }
                                break;
                            case DIR_IZQUIERDA:
                                if(aux->nodoIzq&&aux->nodoIzq->tipo!=MURO&&aux->nodoIzq->tipo!=ARBOL&&aux->nodoIzq->tipo!=ENEMIGO)
                                {
                                    copia=aux->sprt;
                                    aux->sprt=NULL;
                                    aux->tipo=0;

                                    if(aux->nodoIzq->tipo!=PERS_CONS)
                                    {
                                        aux->nodoIzq->sprt=copia;
                                        aux->nodoIzq->tipo=ENEMIGO;
                                    }
                                    else
                                        per->vida--;
                                }
                                break;
                            case DIR_DERECHA:
                                if(aux->nodoDer&&aux->nodoDer->tipo!=MURO&&aux->nodoDer->tipo!=ARBOL&&aux->nodoDer->tipo!=ENEMIGO&&aux->nodoDer->x_I<x_F+NUMPIX*TAMPIX)
                                {
                                    copia=aux->sprt;
                                    aux->sprt=NULL;
                                    aux->tipo=0;

                                    if(aux->nodoDer->tipo!=PERS_CONS)
                                    {
                                        aux->nodoDer->sprt=copia;
                                        aux->nodoDer->tipo=ENEMIGO;
                                    }
                                    else
                                        per->vida--;
                                }
                                break;
                            case DIR_ARRIBA:
                                if(aux->nodoArri&&aux->nodoArri->tipo!=MURO&&aux->nodoArri->tipo!=ARBOL&&aux->nodoArri->tipo!=ENEMIGO)
                                {
                                    copia=aux->sprt;
                                    aux->sprt=NULL;
                                    aux->tipo=0;

                                    if(aux->nodoArri->tipo!=PERS_CONS)
                                    {
                                        aux->nodoArri->sprt=copia;
                                        aux->nodoArri->tipo=ENEMIGO;
                                    }
                                    else
                                        //Si se decide que se mueva al nodo del personaje no se cambia nada
                                        //(el nodo seguirá apuntando al personaje) y al personaje se le baja una vida
                                        per->vida--;
                                }
                                break;
                        }
                    }
            }
            aux=aux->nodoAba;

        }
        fondo=fondo->nodoDer;
    }
}
