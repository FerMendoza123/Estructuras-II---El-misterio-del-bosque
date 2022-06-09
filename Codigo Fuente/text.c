/**************

    Definicion de funciones relacionadas con texto

***************/

//Bibliotecas
#include "graphics.h"
#include "text.h"


/***Comentado***/
//text es la cadena que recibira todo el texto, (x, y) es el punto a partir del cual se dibuja el cursor
void intextxy (int x, int y, char text[])
{
    /*
        color es el ultimo color que se usó en pantalla (despues de getcolor)
        tecla captura la tecla que se presionó
        i nos sirve de indice para copiar la letra a la cadena text
        x2 es la unicacion del cursor
    */
    int tecla,i=0,color,x2=x;
    char letra[2];
    color=getcolor();
    do{
        //Imprime el cursor en las cordenadas especificadas mientras no se teclea
        do{
            setcolor(color);
            outtextxy(x2,y,"|");
            delay(10);
            setcolor(BLACK);
            outtextxy(x2,y,"|");
            delay(10);
        }while(!kbhit());
        /*
            mientras no sean enter (finalizar) o backspace (borrar letra anterior)
            imprime la letra y la copia a la cadena de un caracter (letra) para ser imprimida
            en pantalla, tambien se copia en la cadena text y se incremente para la siguente letra
        */
        tecla=getch();
        if (tecla!='\n'&&tecla!='\b')
        {
            letra[0]=tecla;
            letra[1]='\0';
            text[i++]=tecla;
            setcolor(color);
            outtextxy(x2,y,letra);
            x2+= textwidth(letra);
        }

        if(tecla==13)
        {
            text[--i]='\0';
            setcolor(color);

        }
        /*
            Si se preciona la tecla backspace se modifica el indice para poder
            sobreescribirlo, tambien se borra la letra, solo se podrá si la
            posicion del cursor es mayor a la inicial
        */
        if(tecla=='\b'&&x2>x)
        {
            //text[--i]='\0';
            setcolor(BLACK);
            outtextxy(x2,y,letra);
            x2-= textwidth(letra);
            i--;
        }
    }
    while(tecla!=13);
}
