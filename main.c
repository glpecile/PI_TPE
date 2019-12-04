#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "provinciasADT.h"
#include "yearADT.h"

#define MAX_TEXT 100

//13 216 110
//AN,PROVRES,TIPPARTO,SEXO,IMEDAD,ITIEMGEST,IMINSTRUC,IPESONAC,CUENTA
/*Prototipos funciones auxiliares de main
*/
void readProvs(FILE * provincias, provADT set);
void readBirths(FILE * nacimientos, provADT set);


int 
main (int argc, char * argv[])
{
    time_t tStart, tFinish;
    tStart = time(NULL);

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
    
    printf("\nProvincias cargadas:\n\n");
    printProv(set);
    
    readBirths(nacimientos, set);
    
    query(set);
    
    freeSet(set);
    
    fclose(provincias);
    fclose(nacimientos);

    printf("Finalizo el programa\n");
    tFinish = time(NULL);
    printf("Tiempo de Ejecución: %ds\n", (int)(tFinish - tStart));
    return 0;
}

/*FUNCIONES AUXILIARES DE MAIN
*/
void
readProvs(FILE * provincias, provADT set)
{
    int cod;
    char prov[MAX_TEXT];

    fgets(prov, MAX_TEXT, provincias); //Elimina encabezado

    printf("\nCARGANDO PROVINCIAS...\n");
    while(fscanf(provincias,"%d,%[^\r\n]\n", &cod, prov) == 2)
    {
        addProv(set, cod, prov);
    }
    finalizeProvAddition(set);
}

void
readBirths(FILE * nacimientos, provADT set)
{
    char aux[MAX_TEXT];
    int provres, year, gen, tipoParto;

    unsigned long i = 0;

    fgets(aux, MAX_TEXT, nacimientos); //Elimina encabezado

    printf("\nCARGANDO NACIMIENTOS...\n");
    while(fscanf(nacimientos, "%4d,%d,%d,%d,%[^\r\n]\n", &year, &provres, &tipoParto, &gen,aux) == 5)
    {
        i++;
        addBirth(set, year, provres, gen);
    }
    printf("LINEAS LEIDAS: %lu\n", i);
}

/*
gcc -Wall -pedantic -std=c99 -fsanitize=address -o prueba main.c
./prueba provincias.csv nacimientos2.csv
*/
