#include "sprite.h"
#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"



/************Comentado*********/
int sprite_Lee(SPRITE*gr,char name[])
{
    //Necesitaremos estos indices para leer la matriz
    int i,j,read=1;
    //apuntador a archivo
    FILE *archGrid;
    archGrid=fopen(name,"rb");
    if (archGrid==NULL)
    {
        //Si no se pudo abrir se retorna 0
        read=0;
    }
    if(read)
    {
        //Lee uno por uno los datos del dibujo
        fread(&gr->cellsize,sizeof(gr->cellsize),1,archGrid);
        fread(&gr->col,sizeof(gr->col),1,archGrid);
        fread(gr->name,sizeof(gr->name),1,archGrid);
        fread(&gr->pixSize,sizeof(gr->pixSize),1,archGrid);
        fread(&gr->row,sizeof(gr->row),1,archGrid);
        //Se asigna la memoria para poder asignar los renglones (apuntador a apuntadores)
        gr->grid=(int**)malloc(sizeof(int*)*gr->row);
        //Leemos la matriz renglón por dato por dato
        if(gr->grid)
        {
            for(i=0;i<gr->row;i++)
            {
                //Asignando siempre el renglón que se va a leer
                *(gr->grid+i)=(int*)malloc(sizeof(int)*gr->col);
                for(j=0;j<gr->col;j++)
                    fread((*(gr->grid+i)+j),sizeof(int),1,archGrid);
            }
        }
        else
            read=0;//Si no se pudo asignar memoria para la matriz regresa 0
    }
    //Se cierra el archivo
    fclose(archGrid);
    return read;
}

/*****Comentado*****/
//Esta función recorre las posiciones del arreglo dinamico donde se aloja la información del sprite y lo dibuja
void sprite_Dibuja(SPRITE gr,int xi, int yi,int pS)//Se necesita tener las cordenadas de inicio de dibujado
{
    int r,c,col;
    for(r=0;r<gr.row;r++)
        for(c=0;c<gr.col;c++)
        {
            col=gr.grid[r][c];
            if(col!=-1&&col!=COLOR(226,218,170))
            {
                //dibuja los cuadros de preview con el color asignado
                setfillstyle(SOLID_FILL,col);
                bar(xi+c*pS,yi+r*pS,xi+(c+1)*pS,yi+(r+1)*pS);
            }
        }

}

/****Comentado*****/
//Es lo mismo que la anterior pero dibuja el sprite en la dirección contraria
void sprite_Dibuja_Reves(SPRITE gr,int xi, int yi,int pS)//Se necesita tener las cordenadas de inicio de dibujado
{
    int r,c;
    for(r=0;r<gr.row;r++)
        for(c=0;c<gr.col;c++)
        {
            if(gr.grid[r][c]!=-1&&gr.grid[r][c]!=COLOR(226,218,170))
            {
                //dibuja los cuadros de preview con el color asignado
                setfillstyle(SOLID_FILL,(*(*(gr.grid+r)+c)));
                bar(xi+(gr.col-c)*pS,yi+r*pS,xi+(gr.col-c+1)*pS,yi+(r+1)*pS);
            }
        }

}
