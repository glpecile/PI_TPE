#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "provinciasADT.h"
#include "yearADT.h"

#define MAX_TEXT 100
#define BLOQUE 5

/*Prototipos funciones auxiliares de main
*/
void readProvs(FILE * provincias, provADT set);
void readBirths(FILE * nacimientos, provADT set);
void mainQuery(provADT set);
void query1(FILE * file1, char * name, size_t totalProv);
void query2(FILE * file2, int year, size_t male, size_t female);
void query3(FILE * file3, char ** provs, size_t * pcts, int dim);
//void addPct(char ** provs, size_t ** pcts, char * name, size_t auxPct, int dim);

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
        printf("No se pudo abrir el archivo\n");
        exit(2);
    }

    provADT set = newSet();

    readProvs(provincias, set);

    printf("Provincias cargadas\n\n");
    //printProv(set);

    readBirths(nacimientos, set);
    printf("Nacimientos cargados\n\n");

    mainQuery(set);
    printf("ARCHIVOS GENERADOS\n");

    freeSet(set);

    fclose(provincias);
    fclose(nacimientos);

    printf("PROGRAMA FINALIZADO\n");
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

    fgets(aux, MAX_TEXT, nacimientos); //Elimina encabezado

    printf("\nCARGANDO NACIMIENTOS...\n");
    while(fscanf(nacimientos, "%4d,%d,%d,%d,%[^\r\n]\n", &year, &provres, &tipoParto, &gen,aux) == 5)
    {
        addBirth(set, year, provres, gen);
    }
}

void
mainQuery(provADT set)
{
    FILE * file1 = fopen("query1.csv", "w");
    FILE * file2 = fopen("query2.csv", "w");
    FILE * file3 = fopen("query3.csv", "w");

    /*Variables para el query1
    */
    yearADT auxYearSet = newYears();
    char * nameProv;
    size_t totalProv;
    size_t totalSet = getTotalSet(set);
    printf("TOTAL NACIMIENTOS: %lu\n", totalSet);

    /*Variables para el query2
    */
    size_t male, female, ns;
    int year;

    /*Variables para el query3
    */
    size_t auxPct;
    size_t * pcts = NULL;
    char ** provs = NULL;
    int dim = 0;


    fprintf(file1, "Provincias;Codigo\n");
    fprintf(file2, "Año;Varón;Mujer\n");
    fprintf(file3, "Provincia;Porcentaje\n");

    alphaSort(set);

    toBeginProv(set);

    while(hasNextProv(set))
    {
        //printf("Hay prov\n");
        nameProv = getName(set);
        totalProv = getTotalProv(set, auxYearSet);
        query1(file1, nameProv, totalProv);

        if((auxPct = (totalProv * 100) / totalSet) > 0)
        {
            if(dim % BLOQUE == 0)
            {
                provs = realloc(provs, (dim + BLOQUE) * sizeof(char *));
                pcts = realloc(pcts, (dim + BLOQUE) * sizeof(size_t));
            }

            provs[dim] = nameProv;
            pcts[dim] = auxPct;
            dim++;
        }

        nextProv(set);
    }

    toBeginYear(auxYearSet);
    while(hasNextYear(auxYearSet))
    {
        getCurrentTotals(auxYearSet, &male, &female, &ns, &year);
        query2(file2, year, male, female);
        nextYear(auxYearSet);
    }

    provs = realloc(provs, dim * sizeof(char *));
    pcts = realloc(pcts, dim * sizeof(size_t));
    query3(file3, provs, pcts, dim);

    free(provs);
    free(pcts);
    freeYears(auxYearSet);
    fclose(file1);
    fclose(file2);
    fclose(file3);
    return;
}

void
query1(FILE * file1, char * nameProv, size_t totalProv)
{
    fprintf(file1, "%s;%lu\n", nameProv, totalProv);
    return;
}

void
query2(FILE * file2, int year, size_t male, size_t female)
{
    fprintf(file2, "%d;%lu;%lu\n", year, male, female);
    return;
}

void
query3(FILE * file3, char ** provs, size_t * pcts, int dim)
{
    int max = 0;

    for(int i = 0; i < dim; i++)
    {
        for(int j = 0; j < dim; j++)
        {
            if (pcts[max] < pcts[j])
            {
                max = j;
            }
        }
        fprintf(file3, "%s;%lu%%\n", provs[max], pcts[max]);
        pcts[max] = 0;
    }
    return;
}

/*
void
addPct(char *** provs, size_t ** pcts, char * name, size_t auxPct, int dim)
{
    printf("dimension: %d\n", dim);
    if(dim % BLOQUE == 0)
    {
        printf("Realoc\n");
        *provs = realloc(*provs, (dim + BLOQUE) * sizeof(char *));
        *pcts = realloc(*pcts, (dim + BLOQUE) * sizeof(size_t));
        printf("Realocado\n");
    }
    else
    {
        printf("No entre al realoc\n");
    }

    provs[dim] = name;
    pcts[dim] = auxPct;
    printf("%s\t%lu\n", provs[dim], pcts[dim]);
    printf("Fin addPct\n");

    return;
}
*/

/*
gcc -Wall -pedantic -std=c99 -fsanitize=address -o prueba main.c
make all
./prueba provincias.csv nacimientos2.csv
make clean
*/
