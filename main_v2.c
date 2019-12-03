#include "ProvinciasADT.h"
//bibliografia tutorialspoint
#define MAX_TEXT 100
#define DELIM ",\n"

enum csvProvincias {COD = 0, PROV = 1};
enum csvNacimientos {YEAR = 0, PROVRES = 1, GEN = 3};

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
    printf("\nImpresion de lista:\n");
    printProv(set);
    //readBirths(nacimientos, set);
    query(set);
    fclose(provincias);
    fclose(nacimientos);

    return 0;
}

void
readProvs(FILE * provincias, provADT set)
{
    char text[MAX_TEXT] = {'0'};
    char cod[2];
    char prov[MAX_TEXT] = {'0'};

    fgets(text, MAX_TEXT, provincias); //Elimina encabezado
    while(fscanf(provincias,"%[^,],%[^\n]\n", cod, prov) == 2)
    {
        prov[strlen(prov) - 1] = 0;
        addProv(set, cod, prov);
        //printf("%s\t%s\n", cod, prov);
    }
}

void
readBirths(FILE * nacimientos, provADT set)
{
    char text[MAX_TEXT];
    char * token;
    char * provres;
    char * year;
    char * gen;
    int i;

    //CARGAMOS LOS NACIMIENTOS
    fgets(text, MAX_TEXT, nacimientos); //Elimina encabezado

    while(fgets(text, MAX_TEXT, nacimientos))
    {
        token=strtok(text,DELIM);
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
            token = strtok(NULL, DELIM);
            i++;
        }
        //Mandamos cod y prov al tad para que lo guarde
    }
}


/*
gcc -Wall -pedantic -std=c99 -fsanitize=address -o prueba main.c
./prueba provincias.csv nacimientos2.csv
*/
