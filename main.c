#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "provinciasADT.h"
#include "yearADT.h"

#define MAX_TEXT 100

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
void query3(FILE * file3, char ** provs, int * pcts, int dim);
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
        fprintf(stderr, "Cantidad de archivos incorrecta.\n");
        exit(1);
    }
    else
    {
        printf("Archivos ingresados:\n\t->%s\n\t->%s\n\n", argv[1], argv[2]);
    }

    FILE * provincias = fopen(argv[1], "rt");
    FILE * nacimientos = fopen(argv[2], "rt");

    if(provincias == NULL || nacimientos == NULL)
    {
        fprintf(stderr, "Los archivos no se pudieron abrir: ");
        perror("");
        exit(1);
    }

    provADT set = newSet();

    readProvs(provincias, set);

    printf("Provincias cargadas.\n\n");

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

    fgets(prov, MAX_TEXT, provincias); //Elimina encabezado.

    printf("\nCARGANDO PROVINCIAS...\n");
    while(fscanf(provincias,"%d,%[^\r\n]\n", &cod, prov) == 2)
    {
        if(!addProv(set, cod, prov))
        {
            fprintf(stderr, "No se pudo agregar provincia. Cod: %d\tProv: %s\n", cod, prov);
            exit(1);
        }
    }
    if(!finalizeProvAddition(set))
    {
        fprintf(stderr, "Falla en estructura\n");
        exit(3);
    }

}

void
readBirths(FILE * nacimientos, provADT set)
{
    char aux[MAX_TEXT];
    int provres, year, gen, tipoParto;

    fgets(aux, MAX_TEXT, nacimientos); //Elimina encabezado.

    printf("\nCARGANDO NACIMIENTOS...\n");
    while(fscanf(nacimientos, "%4d,%d,%d,%d,%[^\r\n]\n", &year, &provres, &tipoParto, &gen,aux) == 5)
    {
        if(!addBirth(set, year, provres, gen))
        {
            printf("No se pudo agregar nacimiento. Provres: %d\n", provres);
        }
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
    //size_t auxPct;
    int dim = getQtyProv(set);
    int i = 0;
    int pcts[dim];
    char * provs[dim];

    //Encabezados de query1, query2 y query3
    fprintf(file1, "Provincias;Codigo\n");
    fprintf(file2, "Año;Varón;Mujer\n");
    fprintf(file3, "Provincia;Porcentaje\n");

    alphaSort(set);

    toBeginProv(set);

    while(hasNextProv(set))
    {
        nameProv = getName(set);
        totalProv = getTotalProv(set, auxYearSet);
        query1(file1, nameProv, totalProv);

        provs[i] = nameProv;
        pcts[i++] = (totalProv * 100) / totalSet;

        nextProv(set);
    }

    toBeginYear(auxYearSet);
    while(hasNextYear(auxYearSet))
    {
        getCurrentTotals(auxYearSet, &male, &female, &ns, &year);
        query2(file2, year, male, female);
        nextYear(auxYearSet);
    }

    query3(file3, provs, pcts, dim);

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
query3(FILE * file3, char ** provs, int * pcts, int dim)
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
        if(pcts[max] > 0)
        {
            fprintf(file3, "%s;%d%%\n", provs[max], pcts[max]);
        }
        pcts[max] = -1;
    }
    return;
}
