#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "provinciasADT.h"
#include "yearADT.h"

#define MAX_TEXT 100
#define BLOQUE 5

//FUNCIONES AUXILIARES DE MAIN

//Lee los datos del csv de provincias
void readProvs(FILE * provincias, provADT set);
//Lee los datos del csv de nacimientos
void readBirths(FILE * nacimientos, provADT set);
//Utiliza los datos procesados para invocar las queries, genera los archivos necesarios
void mainQuery(provADT set);
//Imprime la provincia junto con su cantidad de nacimientos en orden alfabetico al archivo query1
void query1(FILE * file1, char * name, size_t totalProv);
//Imprime el año junto con los nacimientos separados por sexo en orden ascendente (por año) al archivo query2
void query2(FILE * file2, int year, size_t male, size_t female);
//Imprime la provincia junto con su porcentaje asociado en orden descendente al archivo query3
void query3(FILE * file3, char ** provs, size_t * pcts, int dim);
//Agrega los porcentajes en orden descendente
//void addPct(char *** provs, size_t ** pcts, char * nameProv, size_t auxPct, int dim);

int
main (int argc, char * argv[])
{
    system("clear");
    time_t tStart, tFinish;
    tStart = time(NULL);

    if(argc != 3)
    {
        error(1,"Cantidad de archivos incorrecta.");
    }
    else
    {
        printf("Archivos ingresados:\n\t->%s\n\t->%s\n\n", argv[1], argv[2]);
    }

    FILE * provincias = fopen(argv[1], "rt");
    FILE * nacimientos = fopen(argv[2], "rt");

    if(provincias == NULL || nacimientos == NULL)
    {
        error(2,"No se pudieron abrir los archivos.");
    }


    provADT set = newSet();

    readProvs(provincias, set);

    printf("Provincias cargadas.\n\n");
    //printProv(set);

    readBirths(nacimientos, set);
    printf("Nacimientos cargados.\n\n");

    mainQuery(set);
    printf("ARCHIVOS GENERADOS\n");

    freeSet(set);

    fclose(provincias);
    fclose(nacimientos);

    printf("PROGRAMA FINALIZADO\n");
    tFinish = time(NULL);
    printf("Tiempo de Ejecución: %ds\n", (int)(tFinish - tStart));
    printf("Busque en el directorio del ejecutable generado los documentos csv.\n");
    return 0;
}

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

    //Variables para el query1
    yearADT auxYearSet = newYears();
    char * nameProv;
    size_t totalProv;
    size_t totalSet = getTotalSet(set);
    printf("TOTAL NACIMIENTOS: %lu\n", totalSet);

    //Variables para el query2
    size_t male, female, ns;
    int year;

    //Variables para el query3
    size_t auxPct;
    size_t * pcts = NULL;
    char ** provs = NULL;
    int dim = 0;

    //Encabezados de query1, query2 y query3
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

        //pasar a funcion
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
        //addPct(&provs, &pcts, nameProv, (auxPct = (totalProv * 100) / totalSet), dim);

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
/*Arreglar
void
addPct(char *** provs, size_t ** pcts, char * nameProv, size_t auxPct, int dim)
{
    char * ans1 = NULL;
    char * ans2 = NULL;
    if(auxPct > 0)
    {
        if(dim % BLOQUE == 0)
        {
            ans1 = realloc(ans1, (dim + BLOQUE) * sizeof(char *));
            ans2 = realloc(ans2, (dim + BLOQUE) * sizeof(size_t));
        }
        ans1[dim] = nameProv;
        ans2[dim] = auxPct;
        dim++;
    }
    ans1 = realloc(ans1, (dim) * sizeof(char *));
    ans2 = realloc(ans2, (dim) * sizeof(size_t));
    ans2[dim]=0;
    *provs=ans1;
    *pcts=ans2;
    return;
}
*/

/*
Tutorial para compilar, borrar mas tarde
gcc -Wall -pedantic -std=c99 -fsanitize=address -o prueba main.c
make all
./prueba provincias.csv nacimientos2.csv
make clean
*/
