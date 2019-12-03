#include "ProvinciasADT.h"
//bibliografia tutorialspoint
#define MAX_TEXT 1000

void readProvs(FILE * provincias, provADT set);
void readBirths(FILE * nacimientos, provADT set);

int main (int argc, char * argv[])
{
    if(argc == 3)
    {
        printf("Archivos ingresados:\n\t->%s\n\t->%s\n\n", argv[1], argv[2]);
    }
    else
    {
        printf("Cantidad de archivos incorrecta\n");
        exit(1);
    }

    FILE * provincias = fopen(argv[1], "r");
    FILE * nacimientos = fopen(argv[2], "r");

    if(provincias == NULL || nacimientos == NULL)
    {
        printf("No se puedo abrir el archivo\n");
        exit(2);
    }

    provADT set = newSet();

    readProvs(provincias, set);
    //printf("\nImpresion de lista:\n");
    //printProv(set);
    
    readBirths(nacimientos, set);
    query(set);
    freeSet(set);
    fclose(provincias);
    fclose(nacimientos);

    printf("Finalizo el programa\n");
    return 0;
}

void
readProvs(FILE * provincias, provADT set)
{
    char aux[MAX_TEXT] = {'0'};
    int cod;
    char prov[MAX_TEXT] = {'0'};
    //while(fgetc(provincias)!='\n');
    fgets(aux, MAX_TEXT, provincias); //Elimina encabezado
    printf("CARGA DE DATOS...\n");
    while(fscanf(provincias,"%d,%[^\n]\n", &cod, prov) == 2)
    {
        prov[strlen(prov)-1]=0;
        addProv(set, cod, prov);
        //printf("Print 1: %s\t%s\n", cod, prov);
    }
    finalizeProvAddition(set);
}

void
readBirths(FILE * nacimientos, provADT set)
{
    char aux[MAX_TEXT];
    int provres;
    int year;
    char gen;
    char tipoParto;
    unsigned long i=1;
    //CARGAMOS LOS NACIMIENTOS
    fgets(aux, MAX_TEXT, nacimientos); //Elimina encabezado
    //printf("AN\tPROV\tGEN\n");
    while(fscanf(nacimientos, "%4d,%d,%c,%c,%[^\n]\n", &year, &provres, &tipoParto, &gen,aux) == 5)
    {
        i++;
       /* if(i % 10000 == 0)
            printf("LINEAS: %lu\n", i);*/
        //printf("%d\t%d\t%d\n", year, provres, gen);
        addBirth(set, year, provres, gen);
    }
    printf("LINEAS LEIDAS: %lu\n", i);
}

/*
gcc -Wall -pedantic -std=c99 -fsanitize=address -o prueba main.c
./prueba provincias.csv nacimientos2.csv
*/
