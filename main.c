#include <stdio.h>

#include "provinciasADT.h"
#include "yearADT.h"

#define MAX_TEXT 100
#define ARG_Q 3         //Cantidad de argumentos que debe recibir el programa.
#define PROV_FMT 2      //Cantidad de argumentos que recibe el formato.
#define BIRTH_FMT 5     //Cantidad de argumentos que recibe el formato.

//FUNCIONES AUXILIARES DE MAIN

/*
**Lee los datos del csv de provincias.
**Retorna 1 si la carga fue satisfactoria.
*/
int readProvs(FILE * provincias, provADT set);
/*
**Lee los datos del csv de nacimientos.
**Retorna 1 si la carga fue satisfactoria.
*/
int readBirths(FILE * nacimientos, provADT set);
/*
**Utiliza los datos procesados para invocar las queries, genera los archivos necesarios.
**Retorna 1 si pudo generar los queries.
*/
int mainQuery(provADT set);
//Imprime la provincia junto con su cantidad de nacimientos en orden alfabetico al archivo query1.
void query1(FILE * file1, char * name, size_t totalProv);
//Imprime el año junto con los nacimientos separados por sexo en orden ascendente por año al archivo query2.
void query2(FILE * file2, int year, size_t male, size_t female);
//Imprime la provincia junto con su porcentaje asociado en orden descendente al archivo query3.
void query3(FILE * file3, char ** provs, int * pcts, int dim);

int
main (int argc, char * argv[])
{
    system("clear");

    if(argc != ARG_Q)
    {
        fprintf(stderr, "Cantidad de archivos incorrecta.\n");
        exit(1);
    }
    else
    {
        printf("Archivos ingresados:\n\t->%s\n\t->%s\n\n", argv[1], argv[2]);
    }

    FILE * provincias = fopen(argv[1], "r");
    FILE * nacimientos = fopen(argv[2], "r");

    if(provincias == NULL || nacimientos == NULL)
    {
        fprintf(stderr, "Los archivos no se pudieron abrir: ");
        perror("");
        exit(1);
    }

    provADT set;

    if((set = newSet()) != NULL && readProvs(provincias, set) && readBirths(nacimientos, set) && mainQuery(set))
    {
        printf("\nARCHIVOS GENERADOS\n");
        printf("Busque en el directorio del ejecutable generado los archivos csv.\n");
    }
    else
    {
        printf("\nNo se generaron archivos csv. Revise salida de errores.\n");
    }

    freeSet(set);

    fclose(provincias);
    fclose(nacimientos);

    printf("\nPROGRAMA FINALIZADO\n");

    return 0;
}

int
readProvs(FILE * provincias, provADT set)
{
    int cod;
    char prov[MAX_TEXT];

    fgets(prov, MAX_TEXT, provincias);  //Elimina encabezado del csv.

    printf("\nCARGANDO PROVINCIAS...\n");
    while(fscanf(provincias,"%d,%[^\r\n]\n", &cod, prov) == PROV_FMT)
    {
        if(!addProv(set, cod, prov))
        {
            return 0;
        }
    }
    if(!finalizeProvAddition(set))
    {
        return 0;
    }

    printf("Provincias cargadas: %lu\n", getQtyProv(set));
    return 1;
}

int
readBirths(FILE * nacimientos, provADT set)
{
    char aux[MAX_TEXT];
    int provres, year, gen, tipoParto;

    fgets(aux, MAX_TEXT, nacimientos);  //Elimina encabezado del csv.

    printf("\nCARGANDO NACIMIENTOS...\n");
    while(fscanf(nacimientos, "%4d,%d,%d,%d,%[^\r\n]\n", &year, &provres, &tipoParto, &gen,aux) == BIRTH_FMT)
    {
        if(!addBirth(set, year, provres, gen))
        {
            return 0;
        }
    }

    printf("Nacimientos cargados: %lu\n", getTotalSet(set));
    return 1;
}

int
mainQuery(provADT set)
{
    FILE * file1 = fopen("query1.csv", "w");
    FILE * file2 = fopen("query2.csv", "w");
    FILE * file3 = fopen("query3.csv", "w");

    //Variables para el query1
    yearADT auxYearSet;
    if((auxYearSet = newYears()) == NULL)
    {
        return 0;
    }
    char * nameProv;
    size_t totalProv;
    size_t totalSet = getTotalSet(set);

    //Variables para el query2
    size_t male, female, ns;
    int year;

    //Variables para el query3
    int dim = getQtyProv(set);
    int i = 0;
    int pcts[dim];
    char * provs[dim];

    //Encabezados de query1, query2 y query3
    fprintf(file1, "Provincias;Nacimientos\n");
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

    return 1;
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
