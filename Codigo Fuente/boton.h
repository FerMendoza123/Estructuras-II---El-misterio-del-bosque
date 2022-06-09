#ifndef _B
typedef struct
{
    //Cordenadas del boton
    int x,y;
    //Color;
    int c;
    //Dimensiones
    int ancho, alto;
    //Texto
    char texto[30];
}BOTON;
#define _B 5
#endif


void boton_Inicializate(BOTON*btn,char*texto,int x,int y,int ancho,int alto,int color);
void boton_Dibuja(BOTON btn);
//Verifica si un boton fue pulsado
int boton_Verificate(BOTON btn);
