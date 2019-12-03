#include "ProvinciasADT.h"
#include "YearADT.h"


//estructura a usar
typedef struct nodeProv //Se utiliza unicamente para cargar los datos.
{
    char * code; //Codigo de identificacion de la Provincia
    char * value; //Nombre de la Provincia
    struct nodeProv * tail;
} nodeProv;

//IDEA LOCA HACER UN TAD PARA YEAR CON SU PROPIO .H

typedef struct tProvVec
{
    char * code;  //Codigo de identificacion de la Provincia
    char * value; //Nombre de la provincia
    yearADT years; //Lista donde se almacena la cantidad de nacimientos por años
} tProvVec;

typedef struct provCDT
{
    size_t qProv; //Cantidad de Provincias
    tProvVec * provVec; //vector a ser creado en listToArray
    nodeProv * firstList; //Lista en donde se cargan las provincias ordenadas por codigo
} provCDT;

static nodeProv * addProvRec(nodeProv * firstList, char * code, char * value, size_t * size);
static int compare(const char * c1, const char * c2);

provADT
newSet(void)
{
    return calloc (1,sizeof(provCDT));
}

int
addProv(provADT set, char * code, char * value)
{
    size_t auxQuant = set->qProv;
    set->firstList = addProvRec(set->firstList, code, value, &(set->qProv));
    return auxQuant != set->qProv;
}

static nodeProv *
addProvRec(nodeProv * firstList, char * code, char * value, size_t * size)
{
    if(firstList == NULL || compare(firstList->code, code) < 0)
    {
        nodeProv * aux = malloc(sizeof(nodeProv));
        aux->tail = firstList;

        size_t codeLength = strlen(code);
        size_t valueLength = strlen(value);

        aux->code = malloc((1 + codeLength) * sizeof(char));
        strcpy(aux->code, code);

        aux->value = malloc((1 + valueLength) * sizeof(char));
        strcpy(aux->value, value);

        (*size)++;

        return aux;
    }

    firstList->tail = addProvRec(firstList->tail, code, value, size);
    return firstList;
}

//Si c1>c2 retorna 1 y va primero c1, si c2>c2 retorna -1 y va primero c2
static int
compare(const char * c1, const char * c2)
{
    int i=0;
    while(c1[i]!=0 && c2[i]!=0)
    {
        if(c1[i]>c2[i])
        {
            return -1;
        }
        else if (c1[i]<c2[i])
        {
            return 1;
        }
        i++;
    }
    if(c1[i]==0)
    {
        return 1;
    }
    return -1;
}



void
printProv(provADT set)
{
    nodeProv * aux = set->firstList;

    while(aux != NULL)
    {
        printf("COD: %s\tPROV: %s\n", aux->code, aux->value);
        aux = aux->tail;
    }
    return;
}

void query(provADT set)
{
    FILE * file1 = fopen("query1.csv", "w");

    fprintf(file1, "Provincias,Codigo\n");

    nodeProv * aux = set->firstList;
    while(aux != NULL)
    {
            fprintf(file1, "%s,%s\n", aux->value, aux->code);
            aux = aux->tail;
    }

    fclose(file1);
}
