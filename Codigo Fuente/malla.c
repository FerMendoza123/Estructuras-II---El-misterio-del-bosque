#include <stdlib.h>
#include "malla.h"
#include <stdio.h>
#include "graphics.h"
#include "sprite.h"
#include "personaje.h"


/*****Comentada**/
void malla_Inicializa(MALLA*cabM)
{
    //Solo ponemos nos indicando que está vacía
    *cabM=NULL;
}

/******Comentado********/
//Esta funcion creará un nodo con todas las ligas en NULL
int malla_CreaNodo(MALLA*nuevo,int dato)
{
    //Suponemos que no se podrá crear
    int res=0;
    //Asignamos la memoria necesaria
    *nuevo=(MALLA)malloc(sizeof(struct nodoMalla));
    if(*nuevo)
    {
        //Si se pudo entonces haremos que sis ligas apunten a null
        (*nuevo)->nodoAba = (*nuevo)->nodoArri = (*nuevo)->nodoDer = (*nuevo)->nodoIzq = NULL;
        //Y asignaremos el tipo de dato
        (*nuevo)->tipo=dato;
        //Y regresaremos un 1
        res=1;
    }
    return res;
}

/*Esta funcion crea la malla añadiendo nodos uno por uno
Hay que:
    - Leer los archivos de las imagenes (mallas) openfile
    - pasar la información (será un apuntador)

*/


/*****************Funcionamiento general de la función
    -Dependiendo del parametro level se selecciona el nombre del archivo que se abrirá
    -El nombre es  seleccionado y se guarda en auxStr
    -Se abre el archivo y de ahí se lee el valor de cada nodo en auxStr,después se copia
    -El se busca un sprite en la lista con el mismo nombre copiado al nodo y se hace qye el nodo apunte a el
************************/
/*****Comentada*******/
int malla_Construlle(MALLA*cabM,int nRen,int nCol,LISTA*li,int level)
{
    //Necesitaremos dos indices, supóndremos que el valor de retorni es afirmativo, nom es el tipo de sprite
    int i,j,res=1,nom;
    //arrS guardará la posicion de el primer elemento del renglon anterior
    //arrM se moverá a los siguientes elementos del mismo renglón para asignar uno a cada nuevo
    //ant unirá el nuevo con el antrior
    MALLA nuevo, ant, arrS,arrM;
    //Aquí decidiremos el nivel dependiendo del parametro recibido
    char auxStr[15];
    switch(level)
    {
        case 1:sprintf(auxStr,"%s","nivel_1.txt");
                break;
        case 2:sprintf(auxStr,"%s","nivel_2.txt");
                break;
        case 3:sprintf(auxStr,"%s","nivel_3.txt");
                break;
    }

    FILE*archMalla;
    archMalla=fopen(auxStr,"r");
    //Si por algona razon no hubiera espacio con res se saldria
    for(i=0;i<nRen&&res;i++)
    {

        for(j=0;j<nCol&&res;j++)
        {
                //Se leerá el archivo en la cadena auxiliar
                //Solo se lee el numero que representa el tipo de sprite
                //Se detendrá hasta que se acabe el archivo
                if(!feof(archMalla))
                {
                    //Los numeros están separados por un espacio o un salto de linea, por eso solo lee uno
                    fscanf(archMalla,"%s",auxStr);
                }
                //ahora se combierte el numero a una variable
                if(feof(archMalla))
                    //Si se acabaron los elementos será 0
                    nom=0;
                else
                    //Si no entonces habrá un numero que signar
                    nom=atoi(auxStr);
                //Crea el nodo de la malla y le asigna el valor para el tipo de sprite
                res=malla_CreaNodo(&nuevo,nom);
                if (res)
                {
                    //Si es un 0 no lleva nada, es un espacio en blanco (ver define´s en malla.h)
                    if(nom)
                        //Si es algun tipo de sprite se buscará en la lista de sprite
                        lista_Busca(&nuevo->sprt,auxStr,li);//Pasaré el apuntador del nodo, así solo tendre que igualar
                    //Asignación de las cordenadas de inicio de dibujado para cada nodo de la maya
                    nuevo->x_I=getmaxx()/2+(j-4)*TAMPIX*NUMPIX;
                    nuevo->y_I=getmaxy()/2+(i-nRen/2)*TAMPIX*NUMPIX;

                    if(!i&&!j)//Entrará solo en el primer nodo de todos
                    {
                        *cabM=nuevo;
                    }
                    if(!j) //entrará siempre al primer nodo del renglón
                    {
                        arrM=arrS; //Le otorgará a arrM el primer valor de la iteracion anterior (como si fuera el primer elemento de arriba)
                        ant=arrS=nuevo; //Actualiza el elemento de arriba (aun no es arriba) para la siguiente iteracion (será arriba)
                    }
                    else
                    {
                        nuevo->nodoIzq=ant;
                        ant->nodoDer=nuevo;
                        ant=ant->nodoDer;//por el orden de enlace seria lo mismo poner = nuevo
                    }
                    if(i)//Solo se tendrá un nodo arriba cuando el nivel sea mayor a 0 (el primero)
                    {
                        arrM->nodoAba=nuevo;//conectará el nodo de arriba con el nuevo
                        nuevo->nodoArri=arrM;
                        arrM=arrM->nodoDer;//recorrerá el apuntador
                    }
                }
        }
    }
    //Se cierra el archivo
    fclose(archMalla);
    return res;
}

/******Comentado****/
//Con esta función se dibujan todos los sprites de la malla en la pantalla, se usa para dibujarla en las 2 paginas al principio de cada nivel
void malla_Muestra(MALLA cabM)
{
    //Basicamente es una auxiliar que recorre todos los nodos de la malla
    MALLA aux;
    int iniP=(getmaxx()-TAMSCREEN)/2;
    while(cabM)
    {
        aux=cabM;
        while(aux)
        {
            //Se dibuja solo la parte de la malla que este en la zona de la "pantalla"
            if(aux->x_I<TAMSCREEN&&aux->x_I>=iniP)
                //El personaje tiene un tamaño diferente, así que se hace una excepción para que lo dibuje con otro tamaño
                if(aux->tipo)
                {
                        if(/*aux->tipo==4||*/aux->tipo==ENEMIGO)
                            sprite_Dibuja(*aux->sprt,aux->x_I,aux->y_I,1);
                        else
                            if(aux->tipo!=PERS_CONS)
                                sprite_Dibuja(*aux->sprt,aux->x_I,aux->y_I,TAMPIX);
                }
            aux=aux->nodoDer;
        }
        cabM=cabM->nodoAba;
    }
}


/****Comentado*****/
//Esta función solo dibuja aquellos nodos que pueden cambiar de sprite dentro del juego
void malla_Remuestra(MALLA cabM,int dir)
{
    //Es casi igual que la función anterior
    MALLA aux;
    int iniP=(getmaxx()-TAMSCREEN)/2;
    while(cabM)
    {
        aux=cabM;
        while(aux)
        {
            if(aux->x_I<TAMSCREEN&&aux->x_I>=iniP)
            {
                if(aux->tipo)
                {
                    //Aquí discriminamos aquellos nodos que tienen un dibujo estático a lo largo del juego
                    if(aux->tipo!=ARBOL&&aux->tipo!=MURO)
                    {
                        //Si es el personaje entonces tienen la posibilidad de dibujarse al reves
                        if(aux->tipo==PERS_CONS||aux->tipo==ENEMIGO)
                        {
                            //Por eso tiene una bandera para la dirección
                            if(aux->tipo==PERS_CONS&&dir==DIR_IZQUIERDA)
                                sprite_Dibuja_Reves(*aux->sprt,aux->x_I,aux->y_I,1);
                                else
                            //El fantasma se dibuja con el mismo tamaño de pixel
                            sprite_Dibuja(*aux->sprt,aux->x_I,aux->y_I,1);
                        }
                        else
                            sprite_Dibuja(*aux->sprt,aux->x_I,aux->y_I,TAMPIX);
                    }

                }
                else
                {
                    //Si no hay nada en el cuadro sólo se dibuja un cuadro negro
                    setfillstyle(SOLID_FILL,BLACK);
                    bar(aux->x_I,aux->y_I,aux->x_I+TAMPIX*NUMPIX,aux->y_I+TAMPIX*NUMPIX);
                }
            }
            aux=aux->nodoDer;

        }
        cabM=cabM->nodoAba;
    }
}


/******Recursiva*****/
/*******Comentado*******/
void malla_Elimina(MALLA*cabM)
{
    if(*cabM)
    {
        //Se irá al último renglón
        malla_Elimina(&((*cabM)->nodoAba));
        //Cuando llegue recorrera todos los nodos de ese rengón
        malla_Elimina(&((*cabM)->nodoDer));
        if((*cabM)->nodoArri)
            //El nodo de arriba tendrá NULL
            (*cabM)->nodoArri->nodoAba=NULL;
        free(*cabM);
        //El nodo de atras tendrá NULL
        *cabM=NULL;
    }
}




/****Comentado******/
void lista_Inicializa(LISTA*li)//Solo pondremos la lista en null
{
    //Se apunta a nul, no hay ningun elemento
    *li=NULL;
}

/****Comantado*****/
int lista_Crea(LISTA*li)
{
    //Supondremos que no se podrá crear
    int res=0;
    //Necesitaremos dos auxiliares, uno para el nuevo elemento y otro para enlazar el anterior
    LISTA nuevo,ant;
    //Primer miembro de la lista (se van creando los nodos)
    if(lista_CreaNodo(&nuevo))
    {
        if(sprite_Lee(&nuevo->sprt,"1"))//Alojará el sprite tipo 1
        {
            *li=nuevo;
            ant=*li;
        }
        if(lista_CreaNodo(&nuevo))//Segundo miembro de la lista
        {
            if(sprite_Lee(&nuevo->sprt,"2"))//Alojará el sprite tipo 2
            {
                ant->sig=nuevo;
                ant=ant->sig;
            }
            if(lista_CreaNodo(&nuevo))//Tercer miembro
            {
                if(sprite_Lee(&nuevo->sprt,"3"))//Alojará el sprite tipo 3
                {
                    ant->sig=nuevo;
                    ant=ant->sig;
                }
                if(lista_CreaNodo(&nuevo))
                {
                    if(sprite_Lee(&nuevo->sprt,"4"))
                    {
                        ant->sig=nuevo;
                        ant=nuevo;
                        if(lista_CreaNodo(&nuevo))
                        {
                            if(sprite_Lee(&nuevo->sprt,"5"))
                            {
                                ant->sig=nuevo;
                                res=1; //Solo si todos los sprites se leyeron se regresa 1
                            }
                        }
                    }
                }
            }
        }
    }
    return res;
}

/*******Comentado********/
int lista_CreaNodo(LISTA *nue)
{
    int res=0;
    //Asigna el espacio necesario
    *nue=(LISTA)malloc(sizeof(nodoLista));
    if(*nue)
    {
        (*nue)->sig=NULL;
        res=1;
    }//Si se pudo regresa 1
    return res;
}

/*****Comentado*****/
/****Recursiva*****/
void lista_Busca(SPRITE**ptr,char*nombre,LISTA*li)
{
    //Si sigue apuntando se puede seguir recorriendo
    if(*li)
    {
        //Si el nombre del sprite buscado coincide con el elemento de la lista entonces hemos encontrado el tipo de sprite
        if(strcmp(nombre,(*li)->sprt.name)==0)
            //Hacemos que el apuntador apunte a la dirección de la lista
            *ptr=&(*li)->sprt;
        else
            //si no seguimos buscando
            lista_Busca(ptr,nombre,&(*li)->sig);
    }
}

/****Comentado****/
//Con esta función se libera el espacio reservado para la lista (con todo y sprites)
void lista_Libera(LISTA li)
{
    LISTA aux;
    while(li)
    {
        aux=li;
        li=li->sig;
        free(aux);
    }
}

//Esta función nos dará el apuntador a un nodo para una estructura personaje
/*****Comentado*********/
void malla_Busca(MALLA*sp,MALLA cabM,int tipo)
{
    MALLA aux;
    //Si no lo encuentrá se quedará con null
    *sp=NULL;
    //Buscará con dos auxiliares el nodo donde está el sprite del tipo especificado
    while(cabM)
    {
        aux=cabM;
        while(aux)
        {
            if(aux->tipo==tipo)
            {
                //Si lo encuentra asigna el nodo correspondiente
                *sp=aux;
                return;
            }
            aux=aux->nodoDer;
        }
        cabM=cabM->nodoAba;
    }
}

/******Comentado****/
//Cuando se llega a los bordes izquierdo o derecho en la malla si no son nodods finales entonces se reccore a la parte siguiente o anterior del escenario
void malla_Reacomoda(MALLA fondo,int dir)
{
    //Se recorre todos los nodos modificando su cordenada en x sumando o restando el tamaño de pixeles de la pantalla
    MALLA aux;
    int cambio=TAMSCREEN-TAMPIX*NUMPIX;
    if(dir==DIR_IZQUIERDA)
        cambio=-cambio;
    while(fondo)
    {
        aux=fondo;
        while(aux)
        {
            aux->x_I-=cambio;
            aux=aux->nodoDer;
        }
        fondo=fondo->nodoAba;
    }
}
