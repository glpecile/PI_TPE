#include "yearADT.h"

typedef struct nodeYear //estructura para el año Funciona como lista
{
    int year;
    size_t male;    //Cantidad de hombres
    size_t female;  //Cantidad de mujeres
    //size_t ns 	//Cantidad de no especificado
    struct nodeYear * tail;
}nodeYear;

typedef struct yearCDT
{
	nodeYear * firstYear;
	nodeYear * currentYear;
}yearCDT;


/*Funciones auxiliares de yearADT
*/
static nodeYear * addYearRec(nodeYear * node, int year, int gen, int * flag);
static void addByGender(nodeYear * node, int gen);
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
int addInYear (yearADT yearSet, int year, int gen)
{
    int flag = 0;

    yearSet->firstYear = addYearRec(yearSet->firstYear, year, gen, &flag);

    return flag;
}

/*
*/
static nodeYear *
addYearRec(nodeYear * node, int year, int gen, int * flag)
{
    if(node == NULL || year < node->year )
    {
        nodeYear * aux = calloc(1,sizeof(nodeYear));

        aux->tail = node;
        aux->year = year;

        addByGender(aux, gen);

        *flag = 1;
        return aux;
    }
    if(year == node->year)
    {
        addByGender(node,gen);
        *flag = 1;
        return node;
    }
    node->tail = addYearRec(node->tail,year,gen,flag);
    return node;
}

static void
addByGender(nodeYear * node, int gen)
{
	switch(gen)
	{
		case MALE:
		{
			(node->male)++;
		}break;

		case FEMALE:
		{	
			(node->female)++;
		}break;

		/*case NOT_SPECIFIED:
		{
			(node->ns)++;
		}break;*/
	}

	return;
}

/*int getMale (yearADT * currentYear);
**int getFemale(yearADT * currentYear);
**devuelve los totales de hombres y mujeres como parametro de salida
**en su nombre retorna el total de donde esta el current
*/
int 
getTotals(yearADT yearSet, int * male, int * female/*, int * ns*/)
{
	return 0;
}

/*Permite añadir las cantidad male y female en el año
**donde esta parado current
*/
void 
addYearTotal(yearADT yearSet, size_t male, size_t female/*, size_t ns*/)
{
	return;
}

/*
*/
void 
toBeginYear (yearADT yearSet)
{
	yearSet->currentYear = yearSet->firstYear;
}

/*
*/
void 
nextYear (yearADT yearSet)
{
	yearSet->currentYear = yearSet->currentYear->tail;
	return;
}

/*
*/
int hasNextYear (yearADT yearSet)
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