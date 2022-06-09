#include "menu.h"
#include <conio.h>
#include "graphics.h"
#include "juego.h"
#include <stdio.h>
#include "text.h"

/*******Función menu*********/
void menu()
{
    //Bandera para estado visual del menu, si es 0 se dibujará de nuevo
    int banderaMenu=0;
    //Creamos los botones necesarios
    BOTON bNueva,bRecord,bAyuda,bSalir;
    //Inicialización de botones
    boton_Inicializate(&bNueva,"Nueva partida",(getmaxx()/2)-90,(getmaxy()/2)-100,180,40,BLUE);
    boton_Inicializate(&bRecord,"Records",(getmaxx()/2)-60,(getmaxy()/2),120,40,GREEN);
    boton_Inicializate(&bAyuda,"Ayuda",(getmaxx()/2)-60,(getmaxy()/2)+100,120,40,RED);
    boton_Inicializate(&bSalir,"Salir",(getmaxx()/2)-60,(getmaxy()/2)+200,120,40,YELLOW);
    //Se crean los records y se leen
    RECORDS recs;
    int puntos;
    char nombre[20];
    records_Lee(&recs);
    // Esta es la pantalla de presentación
    muestraPantallaInicio();
    //Ciclo para el funcionamiento del menú
    while(1)
    {
        if(!banderaMenu)
        {
            //Dibujaremos el menu siempre que sea necesario
            dibujaMenu(bNueva,bRecord,bAyuda,bSalir);
            banderaMenu=1;
        }
        //Checamos si se hizo un clic
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            //Checamos para todos los botones si el clic fue  sobre ellos
            if(boton_Verificate(bNueva))
            {
                //Se iniciará el juego

                juego(&puntos);/*****************************************FALTA COMENTAR EL JUEGO*******************/

                ///Hacer una funcion para checar si el puntaje entra en el top 10

                if(records_Verifica(recs,puntos))
                {
                    pideNombre(nombre);
                    recods_Incerta(&recs,puntos,nombre);
                    records_Guarda(recs);
                }
                //Será necesario redibujar la pantalla
                banderaMenu=0;
            }
            if(boton_Verificate(bRecord))
            {
                //Se muestra la pantalla de records
                pantallaRecords(recs);
                banderaMenu=0;
            }
            if(boton_Verificate(bAyuda))
            {
                //Se muestra la pantalla de ayuda
                pantallaAyuda();
                banderaMenu=0;
            }
            if(boton_Verificate(bSalir))
            {
                ///Gaurdar archivo de records
                break;
            }
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
}

/**********Función para dibujar el menu**********/
/*********Comentado*********/
void dibujaMenu(BOTON bNue,BOTON bRe,BOTON bAyu,BOTON bSal)
{
    //Se limpia la pantalla
    cleardevice();
    //Se coloca la imagen de fondo
    readimagefile("bos.jpg",0,0,getmaxx(),getmaxy());
    //Se dibuja el titulo con ese estili de texto
    settextstyle(5,HORIZ_DIR,5);
    outtextxy(125,100,"El misterio del bosque");
    //Se dibujan los botones
    boton_Dibuja(bNue);
    boton_Dibuja(bRe);
    boton_Dibuja(bAyu);
    boton_Dibuja(bSal);
}

/*********Comentado*****/
void pantallaAyuda()
{
    //Boton para salir
    BOTON salir;
    boton_Inicializate(&salir,"salir",getmaxx()-80,getmaxy()-40,80,40,BLUE);
    cleardevice();
    boton_Dibuja(salir);
    //Cadena para leer caracter por caracter
    char c[2];
    //Apuntador para leer el archivo
    FILE*archAyuda;
    //Apertuar de archivo
    archAyuda=fopen("ayuda.txt","r");

    //Titulo de la pantalla
    settextstyle(5,HORIZ_DIR,5);
    outtextxy(150,50,"Records");
    //Se imprimen uno por uno los caracteres
    settextstyle(10,HORIZ_DIR,2);
    moveto(50,150);
    //Mientras no se acabe el archivo
    while(!feof(archAyuda))
    {
        //Se copia un caracter
        c[0]=fgetc(archAyuda);
        //Final de cadena
        c[1]='\0';
        //Se imprimira´en la posión actual (solo si está dentro de ascci)
        if(c[0]>=32&&c[0]<=126)
            outtext(c);
        //se avanza de posición en la pantalla
        moveto(getx()+4,gety());
        //Si es un final de linea o si se revasó el limite se salta al siguiente renglón
        if(c[0]=='\n'||getx()>getmaxx()-80)
        {
            //Solo si no es salto de linea es porque se paso, imprime un guión
            if(c[0]!='\n'&&c[0]!=' ')
                outtext("- ");
            moveto(50,gety()+20);
        }
    }
    //Ciclo para el clic
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            if(boton_Verificate(salir))
                break;
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
}

/********Comentado*****/
void pantallaRecords(RECORDS recs)
{
    //Se necesita un boton para salir
    BOTON salir;
    //Se inicializa
    boton_Inicializate(&salir,"salir",getmaxx()-80,getmaxy()-40,80,40,BLUE);
    //Se limpia la pantalla
    cleardevice();
    //Se dibuja el boton
    boton_Dibuja(salir);
    //Titulo de la pantalla
    settextstyle(5,HORIZ_DIR,5);
    outtextxy(150,50,"Records");
    //Impresión de recods
    settextstyle(10,HORIZ_DIR,2);
    records_Imprime(recs);
    //Checado de un clic
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {

            if(boton_Verificate(salir))
                //Se sale del ciclo y después termina la función
                break;
            //La entrada del mouse venía sucia, entrará al ciclo por primera vez y la limpiará
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
}


/*******Comentado*******/
void muestraPantallaInicio()
{
    //Se leen e imprimen las imagenes de los logos
    readimagefile("UASLP.bmp",40,20,180,180);
    readimagefile("FIUASLP.bmp",getmaxx()-180,20,getmaxx()-40,180);
    //necesitamos coordenadas de referencia para la impresión del texto y un color para el parpadeo
    int x=100,col=YELLOW;
    int y=220;
    //Se imprime Por renglones (ajustando las cordenadas)
    settextstyle(4,HORIZ_DIR,2);
    outtextxy(x-70,y,"Universidad Autónoma de San Luis Potosí");
    y+=70;
    outtextxy(x+70,y,"Facultad de ingeniería");
    y+=50;
    outtextxy(x,y,"Area: Ciencias de la computacion");
    y+=30;
    outtextxy(x,y,"Carrera: Ing. Sistemas inteligentes");
    y+=30;
    outtextxy(x+20,y,"Materia: Estructuras de datos II");
    y+=30;
    outtextxy(x-45,y,"Alumno: Mendoza Rodríguez Fernando");
    y+=30;
    outtextxy(x-50,y,"Profesor: De la Cruz López Miguel Ángel");
    y+=30;
    outtextxy(x+20,y,"Proyecto: El misterio del bosque");
    y+=80;
    //Dibuja el texto parpadeante
    while(!kbhit())
    {
        //Asigna el color
        setcolor(col);
        //Imprime el texto
        outtextxy(x-70,y,"Presiona enter");
        //Cambia el color
        col=col==WHITE?YELLOW:WHITE;
        //Espera para cambiar el color
        delay(450);
    }
}

/*******Comentado*****/
void pideNombre(char*nombre)
{
    //Con esta función se hace lo necesario para capturar el nombre si se entra en el top
    cleardevice();
    outtextxy(100,100,"Has entrado en el top de puntajes!!!!");
    outtextxy(100,140,"Dame tu nombre");
    intextxy(100,180,nombre);
}
