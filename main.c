#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_TEXT 100

enum csvProvincias {COD = 0, PROV = 1};
enum csvNacimientos {YEAR = 0, PROVRES = 1, GEN = 3};

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

    char text[MAX_TEXT];
    char delim[3] = ",\n";
    char * token;
    int i;

    char * cod;
    char * prov;

    fgets(text, MAX_TEXT, provincias); //Elimina encabezado

    //CARGAMOS LAS PROVINCIAS
    while(fgets(text, MAX_TEXT, provincias))
    {
        token=strtok(text,delim);
        i = 0;

        while(token != NULL)
        {
            switch(i)
            {
                case COD:
                {
                    cod = token;
                    printf("COD: %s\t", cod);
                }break;

                case PROV:
                {
                    prov = token;
                    printf("PROV: %s\n", prov);
                }break;
            }
            token = strtok(NULL, delim);
            i++;
        }
        //Mandamos cod y prov al tad para que lo guarde
    }

    char * provres;
    char * year;
    char * gen;

    //CARGAMOS LOS NACIMIENTOS
    fgets(text, MAX_TEXT, nacimientos); //Elimina encabezado

    while(fgets(text, MAX_TEXT, nacimientos))
    {
        token=strtok(text,delim);
        i = 0;

        while(token != NULL)
        {
            switch(i)
            {
                case YEAR:
                {
                    year = token;
                    printf("AÑO: %s\t", year);
                }break;

                case PROVRES:
                {
                    provres = token;
                    printf("PROVRES: %s\t", provres);
                }break;
                case GEN:
                {
                    gen = token;
                    printf("GEN: %s\n", gen);
                }break;
            }
            token = strtok(NULL, delim);
            i++;
        }
        //Mandamos cod y prov al tad para que lo guarde
    }
    fclose(provincias);
    fclose(nacimientos);

    return 0;
}

/*
gcc -Wall -pedantic -std=c99 -fsanitize=address -o prueba main.c
./prueba provincias.csv nacimientos2.csv
*/
