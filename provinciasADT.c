#include "provinciasADT.h"
#include "yearADT.h"

/*
*/
typedef struct nodeProv //Se utiliza unicamente para cargar los datos.
{
    int code; //Codigo de identificacion de la Provincia
    char * value; //Nombre de la Provincia
    struct nodeProv * tail;
}nodeProv;

/*
*/
typedef struct tProvVec
{
    int code;  //Codigo de identificacion de la Provincia
    char * value; //Nombre de la provincia
    yearADT years; //Lista donde se almacena la cantidad de nacimientos por años
}tProvVec;

/*
*/
typedef struct provCDT
{
    size_t total;//Cantidad de nacimientos en el pais
    size_t qProv; //Cantidad de Provincias
    tProvVec * provVec; //vector a ser creado en listToArray
    nodeProv * firstList; //Lista en donde se cargan las provincias ordenadas por codigo
    int current;
}provCDT;

/*
*/



/*PROTOTIPO Funciones auxiliares de provinciasADT
*/
static nodeProv * addProvRec(nodeProv * firstList, int code, char * value, size_t * size);
static void listToArray(provADT set);
static int binarySearch(tProvVec * datos, size_t dim, int num, int * idx);
static void freeListRec(nodeProv * first);

static int 
compare(unsigned int  c1, unsigned int c2)
{
    return c1-c2;
}


/*FUNCIONES PRINCIPALES DEL TAD
*/
/*
*/
provADT
newSet(void)
{
    return calloc (1,sizeof(provCDT));
}

/*
*/
int
addProv(provADT set, int code, char * value)
{
    size_t auxQuant = set->qProv;

    set->firstList = addProvRec(set->firstList, code, value, &(set->qProv));

    return auxQuant != set->qProv;
}

/*
*/
static nodeProv *
addProvRec(nodeProv * firstList, int code, char * value, size_t * size)
{
    if(firstList == NULL || compare(code,firstList->code) < 0)
    {
        nodeProv * aux = malloc(sizeof(nodeProv));

        aux->tail = firstList;
		aux->code = code;
        aux->value = malloc((1 + strlen(value)) * sizeof(char));
        strcpy(aux->value, value);

        (*size)++;

        return aux;
    }

    firstList->tail = addProvRec(firstList->tail, code, value, size);
    return firstList;
}

/*
*/
void finalizeProvAddition(provADT set)
{
    listToArray(set);
}

/*
*/
static void
listToArray(provADT set)
{
    int i = 0;
    nodeProv * aux = set->firstList;

    set->provVec = calloc(set->qProv, sizeof(tProvVec));

    while(aux != NULL)
    {
        set->provVec[i].code = aux->code;
        set->provVec[i].value = aux->value;
        set->provVec[i].years = newYears();
        aux = aux->tail;
        i++;
    }
}

/*
*/
int addBirth(provADT set, int year, int provres, int gen)
{
    int idx=0;
    int flag = binarySearch(set->provVec,set->qProv, provres, &idx);
    size_t currentTotal=set->total;

    if (flag!=-1 && addInYear(set->provVec[idx].years, year, gen))
    {
        set->total++;
    }

    return set->total != currentTotal;
}

/*Retorna -1 si el elemento num no se encuentra
**Retorna mayor que cero si el elemento num se encuentra
**En el parametro de entrada/salida idx devuelve la posicion en 
**la que se encuentra 
*/
static int
binarySearch(tProvVec * prov, size_t dim, int num, int * idx)
{
    if(dim == 0)
    {	*idx = -1;
        return -1;
    }

    int comp = compare(prov[dim/2].code, num);

    if(comp == 0)
    {
        *idx += dim/2;
        return dim/2;
    }

    if(comp > 0)
    {
        return binarySearch(prov, dim/2, num, idx);
    }

    *idx += dim/2 + 1;
    return binarySearch(prov + dim/2 + 1, dim - dim/2 - 1, num, idx);
}

/*
*/
void
alphaSort(provADT set)
{
    int dim = set->qProv;
    tProvVec aux;

    for(int i = 0; i < dim; i++)
    {
        for(int j = i + 1; j < dim; j++)
        {
            if(strcmp(set->provVec[i].value, set->provVec[j].value) > 0)
            {
                aux = set->provVec[i];
                set->provVec[i] = set->provVec[j];
                set->provVec[j] = aux;
            }
        }
    }
}

/*
*/
void
toBeginProv(provADT set)
{
    set->current = 0;
}

/*
*/
int
hasNextProv(provADT set)
{
    return set->current < set->qProv;
}

/*
*/
void
nextProv(provADT set)
{
    (set->current)++;
}

/*Libera el provADT
*/
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

    return;
}

/*Libera los nodos de la lista de provincias
*/
static void
freeListRec(nodeProv * first)
{
    if(first == NULL)
    {
        return;
    }

    freeListRec(first->tail);
    free(first->value);
    free(first);

    return;
}


/*FUNCIONES AUXILIARES DE PRUEBA
*/
void
printProv(provADT set)
{
    nodeProv * aux = set->firstList;
    int i=0;
    while(aux != NULL)
    {
        printf("idx:%d\t COD: %d\tPROV: %s\n", i++, aux->code, aux->value);
        aux = aux->tail;
    }
    return;
}

void
printVec(provADT set)
{
    printf("Tamaño: %ld\n", set->qProv);
    for(int i = 0; i < set->qProv; i++)
    {
        printf("%2d\t%s\n", set->provVec[i].code, set->provVec[i].value);
    }
}

void
query(provADT set)
{
    FILE * file1 = fopen("query1.csv", "w");

    fprintf(file1, "Provincias,Codigo\n");

    nodeProv * aux = set->firstList;
    while(aux != NULL)
    {
        fprintf(file1, "%s,%2d\n", aux->value, aux->code);
        aux = aux->tail;
    }

    fclose(file1);
}