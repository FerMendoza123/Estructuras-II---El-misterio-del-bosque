
#define TOP 10

typedef struct
{
    char nombre[30];
    int puntaje;
}RECORD;

typedef struct
{
    RECORD top[TOP];//Arreglo con los 10 mejores
}RECORDS;


void records_Lee(RECORDS*re);
void records_Imprime(RECORDS recs);
void records_Guarda(RECORDS re);
int records_Verifica(RECORDS re,int pun);

void recods_Incerta(RECORDS*re,int puntos,char*nombre);
