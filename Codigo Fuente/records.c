#include "records.h"
#include <stdlib.h>
#include <stdio.h>
#include "graphics.h"

/*******Comentado******/
void records_Lee(RECORDS*re)
{
    //Recorreremos cada uno de los records ya sea leyendolos o inicializandolos
    int i;
    //Declaramos un apuntador para poder leer el archivo
    FILE *arRec;
    //Intentamos abrirlo
    arRec=fopen("records","rb");
    if(!arRec) //Si no existe obtendremos NULL (porque nunca lo hemos jugado)
    {
        //Entonces inicializaremos los records
        for(i=0;i<TOP;i++)
        {
            sprintf(re->top[i].nombre,"%s","Vacio");
            re->top[i].puntaje=0;
        }
    }
    else//Se pudo abrir el archivo
    {
        //Se leerá cada registro dentro de la estructura
        for(i=0;i<TOP;i++)
        {
            fread(re->top[i].nombre,sizeof(re->top[i].nombre),1,arRec);
            fread(&re->top[i].puntaje,sizeof(re->top[i].puntaje),1,arRec);
        }
    }
    fclose(arRec);
}

/****Comentado********/
void records_Imprime(RECORDS recs)
{
    //Recorreremos todos los records (necesitamos un indice)
    int i;
    //Necesitaremos esta cadena para almacenar la conversion del puntaje
    char str[5];
    //Dibujamos los nombres de las columnas
    moveto(50,200);
    outtext("Nombre");
    moveto(300,gety());//Se imprimen  por renglones, por eso gety
    outtext("Puntaje");
    //Ahora imprimimos los nombres y puntajes
    for(i=0;i<TOP;i++)
    {
        //Se imprime un nombre
        moveto(50,gety()+20);
        outtext(recs.top[i].nombre);
        //Se imprime su puntaje
        moveto(300,gety());
        sprintf(str,"%d",recs.top[i].puntaje);
        outtext(str);
        //no nos preocupamos de aumentar variables de posición de impresión porque se hace con la del gráfico
        //(se mueve con moveto)
    }
}

/***Comentado*****/
//Abre el archivo y sobreescribe la información de los registros del top
void records_Guarda(RECORDS re)
{
    int i;
    FILE*arRe;
    arRe=fopen("records","wb");
    for(i=0;i<TOP;i++)
    {
        fwrite(re.top[i].nombre,sizeof(re.top[i].nombre),1,arRe);
        fwrite(&re.top[i].puntaje,sizeof(re.top[i].puntaje),1,arRe);
    }
    fclose(arRe);
}

/****Comentado****/
int records_Verifica(RECORDS re,int pun)
{
    int i;
    //Para saber si entra solo necesitamos checar el ultimo elemento del top (El puntaje mas bajo dentro)
    //Si pun > a los puntos del ultimo elemento es seguro que entrará
    //Si el último elemento es 0 tambien es seguro que el nuebo record entrara
    if(pun>0&&!re.top[TOP-1].puntaje||pun>re.top[TOP-1].puntaje)
        return 1;
    return 0;
}

/****Comentado****/
//Recorre el arreglo de registros buscando la posición que le corresponde al nuevo record
void recods_Incerta(RECORDS*re,int puntos,char*nombre)
{
    int i,j;
    for(i=0;i<TOP&&puntos<re->top[i].puntaje;i++);
    //Recorre los registros anteriores
    for(j=TOP-1;j>i;j--)
    {
        re->top[j]=re->top[j-1];
    }
    //Se copian los nuevos datos en la posición
    re->top[i].puntaje=puntos;
    strcpy(re->top[i].nombre,nombre);
}
