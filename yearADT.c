#include "yearADT.h"

typedef struct nodeYear //estructura para el año Funciona como lista
{
    int year;
    size_t male;    //Cantidad de hombres
    size_t female;  //Cantidad de mujeres
    size_t ns; 	//Cantidad de no especificado
    struct nodeYear * tail;
}nodeYear;

typedef struct yearCDT
{
	nodeYear * firstYear;
	nodeYear * currentYear;
}yearCDT;

static void
Error(const char* s)
{
	fprintf(stderr, "%s\n", s);
	exit(EXIT_FAILURE);
}

/*Funciones auxiliares de yearADT
*/
static nodeYear * addYearRec(nodeYear * node, int year, int gen, size_t qty, int * flag);
static void addByGender(nodeYear * node, int gen, size_t qty);
static void freeYearRec(nodeYear * first);


/*FUNCIONES PRINCIPALES DEL TAD
*/
/*
*/
yearADT newYears (void)
{
	return calloc(1,sizeof(yearCDT));
}

/*Recibe el set->provVec->years y crea un nodo nuevo si el año no existe
**Si el año ya existe, se
*/
int addInYear (yearADT yearSet, int year, int gen, size_t qty)
{
    int flag = 0;

    yearSet->firstYear = addYearRec(yearSet->firstYear, year, gen, qty, &flag);

    return flag;
}

/*
*/
static nodeYear *
addYearRec(nodeYear * node, int year, int gen, size_t qty, int * flag)
{
    if(node == NULL || year < node->year )
    {
        nodeYear * aux = calloc(1,sizeof(nodeYear));

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

/*int getMale (yearADT * currentYear);
**int getFemale(yearADT * currentYear);
**devuelve los totales de hombres, mujeres y ns como parametro de salida
**en su nombre retorna el total de donde esta el current
*/
int
getCurrentTotals(yearADT yearSet, size_t * male, size_t * female, size_t * ns, int * year)
{
    *male = yearSet->currentYear->male;
    *female = yearSet->currentYear->female;
    *ns = yearSet->currentYear->ns;
    *year = yearSet->currentYear->year;
	return (*male + *female + *ns);
}

/*Permite añadir las cantidad male y female en el año
**donde esta parado current
*/
void
addCurrentYearTotal(yearADT yearSet, size_t male, size_t female, size_t ns)
{
    yearSet->currentYear->male = male;
    yearSet->currentYear->female = female;
    yearSet->currentYear->ns = ns;
	return;
}

/*
*/
void
toBeginYear(yearADT yearSet)
{
	yearSet->currentYear = yearSet->firstYear;
}

/*
*/
void
nextYear(yearADT yearSet)
{
	yearSet->currentYear = yearSet->currentYear->tail;
	return;
}

/*
*/
int hasNextYear(yearADT yearSet)
{
	return yearSet->currentYear != NULL;
}

/*
*/
void freeYears(yearADT years)
{
	freeYearRec(years->firstYear);
	free(years);
}

/*
*/
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
