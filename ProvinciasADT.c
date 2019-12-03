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
    size_t total;//Cantidad de nacimientos en el pais
    size_t qProv; //Cantidad de Provincias
    tProvVec * provVec; //vector a ser creado en listToArray
    nodeProv * firstList; //Lista en donde se cargan las provincias ordenadas por codigo
    int current;
} provCDT;

static nodeProv * addProvRec(nodeProv * firstList, char * code, char * value, size_t * size);

static int compare(const char * c1, const char * c2);
static void printVec(provADT set);

//static int binarySearch(tProvVec * datos, size_t dim, char * num, int * idx);
static int binarySrch(tProvVec * prov, int min, int max, char * num);

static void listToArray(provADT set);

static void freeListRec(nodeProv * first);

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
    if(firstList == NULL || /*compare(firstList->code, code)*/strcmp(code,firstList->code) < 0)
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
        //printf("Print 2: %s\t%s\n", aux->code, aux->value);
        return aux;
    }

    firstList->tail = addProvRec(firstList->tail, code, value, size);
    return firstList;
}

void finalizeProvAddition(provADT set)
{
    listToArray(set);
    //ESTO SE TIENE QUE IR A LA MIERDA
    printVec(set);
    //char * aBuscar = "11000";
    //printf("Esta el codigo %i\n", binarySearch(set->provVec,set->qProv, aBuscar));
}

static void listToArray(provADT set)
{
    int i = 0;
    nodeProv * aux = set->firstList;

    set->provVec = calloc(set->qProv, sizeof(tProvVec));

    while(aux != NULL)
    {
        set->provVec[i].code = aux->code;
        set->provVec[i].value = aux->value;

        aux = aux->tail;
        i++;
    }
}
/*
//Si c1>c2 retorna 1 y va primero c1, si c2>c2 retorna -1 y va primero c2
static int
compare(const char * c1, const char * c2)
{
    int i=0;
    while(c1[i] !=0 && c2[i] !=0)
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
    if (c2[i]==0)
    {
        return -1;
    }
    return 0;
}
*/

void
printProv(provADT set)
{
    nodeProv * aux = set->firstList;
    int i=0;
    while(aux != NULL)
    {
        printf("idx:%d\t COD: %s\tPROV: %s\n", i++, aux->code, aux->value);
        aux = aux->tail;
    }
    return;
}

void
query(provADT set)
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

void
toBeginProv(provADT set)
{
    set->current = 0;
}

int
hasNextProv(provADT set)
{
    return set->current < set->qProv;
}

void
nextProv(provADT set)
{
    set->current ++;
}

//hace una busqueda binaria del array obtenito de la lista y retorna el indice
static int
binarySearch(tProvVec * prov, size_t dim, char * num, int * idx)
{
    int a = dim%2;

    if(dim == 0)
    {
        return -1000;
    }
    int comp = strcmp(prov[dim/2].code, num);
    if(comp == 0)
    {
        *idx +=dim/2;
        return dim/2+a;
    }

    if(comp>0)
    {
        return binarySearch(prov, dim/2, num, idx);
    }
    *idx += dim/2 + 1;
    return binarySearch(prov + dim/2 + 1, dim/2, num, idx)+dim/2+a;
}

static int
binarySrch(tProvVec * prov, int min, int max, char * num)
{
    if (max-min==0)
    {
        return -1;
    }
    int comp = strcmp(prov[min + (max-min)/2].code,num);
    if (comp==0)
    {
        return min + (max-min)/2;
    }
    if (comp>0)
    {
        return binarySrch(prov, min, (max-min)/2 - 1, num);
    }
    return binarySrch(prov, (max-min)/2 + 1, max, num);
}

int addBirth(provADT set, char * year, char * provres, char * gen)
{
    char aux[3];
    aux[2] = 0;
    int idx;
    for(int i = 0; i < 100; i++)
    {
        idx=0;
        aux[1] = (i % 10) + '0';
        aux[0] = ((i / 10) % 10) + '0';
        binarySearch(set->provVec,set->qProv, aux, &idx);
        //idx = binarySrch(set->provVec, 0, set->qProv - 1, aux);
        printf("Codigo: %s\ti: %d\tIndice: %d\n",aux, i,  idx);
    }
    size_t currentTotal=set->total;
    printf("Teremino el binary\tIndice: %d\n", idx);
    if (addYear(set->provVec[idx].years,atoi(year),atoi(gen)) && idx!=-1)
    {
        printf("%ld\n", set->total++);
    }
    return set->total != currentTotal;
}
void printVec(provADT set)
{
    printf("Tamaño: %ld\n", set->qProv);
    for(int i = 0; i < set->qProv; i++)
    {
        printf("%s\t%s\n", set->provVec[i].code, set->provVec[i].value);
    }
}

void
freeSet(provADT set)
{
    for(int i = 0; i < set->qProv; i++)
    {
        freeYears(set->provVec[i].years);
    }
    free(set->provVec);
    freeListRec(set->firstList);
    free(set);
}

static void
freeListRec(nodeProv * first)
{
    if(first == NULL)
    {
        return;
    }

    freeListRec(first->tail);
    free(first->code);
    free(first->value);
    free(first);
    return;
}
