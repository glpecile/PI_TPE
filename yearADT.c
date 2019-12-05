#include "yearADT.h"

//Estructura para los nacimientos por año, funciona como lista.
typedef struct nodeYear
{
    int year;   //Año en el que se encuantra.
    size_t male;    //Cantidad de hombres.
    size_t female;  //Cantidad de mujeres.
    size_t ns;  //Cantidad de no especificado.
    struct nodeYear * tail;
}nodeYear;

typedef struct yearCDT
{
	nodeYear * firstYear;  //Primer nodo de la lista.
	nodeYear * currentYear;    //Iterador de la lista.
}yearCDT;

//Funciones static de yearADT:

//Añade un nodo de forma recursiva.
static nodeYear * addYearRec(nodeYear * node, int year, int gen, size_t qty, int * flag);
//Agrega al género indicado pasado como parámetro la cantidad pasada.
static void addByGender(nodeYear * node, int gen, size_t qty);
//Libera los nodos de la estructura de forma recursiva.
static void freeYearRec(nodeYear * first);

//Fin de funciones static.

//FUNCIONES PRINCIPALES DEL TAD DE NACIMIENTOS POR AÑO:
yearADT newYears (void)
{
	return calloc(1,sizeof(yearCDT));
}

int addInYear (yearADT yearSet, int year, int gen, size_t qty)
{
    int flag = 0;

    yearSet->firstYear = addYearRec(yearSet->firstYear, year, gen, qty, &flag);

    return flag;
}

static nodeYear *
addYearRec(nodeYear * node, int year, int gen, size_t qty, int * flag)
{
    if(node == NULL || year < node->year )
    {
        nodeYear * aux = calloc(1,sizeof(nodeYear));

//        if(aux == NULL)
        {

        }

        aux->tail = node;
        aux->year = year;
        addByGender(aux, gen, qty);

        *flag = 1;
        return aux;
    }
    if(year == node->year)
    {
        addByGender(node,gen, qty);
        *flag = 1;
        return node;
    }
    node->tail = addYearRec(node->tail, year, gen, qty, flag);
    return node;
}

static void
addByGender(nodeYear * node, int gen, size_t qty)
{
	switch(gen)
	{
		case MALE:
		{
			(node->male)+= qty;
		}break;

		case FEMALE:
		{
			(node->female)+= qty;
		}break;

		case NOT_SPECIFIED:
		{
			(node->ns)+= qty;
		}break;
	}

	return;
}

int
getCurrentTotals(yearADT yearSet, size_t * male, size_t * female, size_t * ns, int * year)
{
    *male = yearSet->currentYear->male;
    *female = yearSet->currentYear->female;
    *ns = yearSet->currentYear->ns;
    *year = yearSet->currentYear->year;
	return (*male + *female + *ns);
}

void
toBeginYear(yearADT yearSet)
{
	yearSet->currentYear = yearSet->firstYear;
}

void
nextYear(yearADT yearSet)
{
	yearSet->currentYear = yearSet->currentYear->tail;
	return;
}

int hasNextYear(yearADT yearSet)
{
	return yearSet->currentYear != NULL;
}

void freeYears(yearADT years)
{
	freeYearRec(years->firstYear);
	free(years);
}

static void
freeYearRec(nodeYear * first)
{
	if(first == NULL)
	{
		return;
	}

	freeYearRec(first->tail);
	free(first);
	return;
}
