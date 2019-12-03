#include "YearADT.h"
#define MALE 1
#define FEMALE 2

typedef struct nodeYear //estructura para el año Funciona como lista
{
    int year;
    size_t male;    //Cantidad de hombres
    size_t female;  //Cantidad de mujeres
    struct nodeYear * tail;
} nodeYear;

typedef struct yearCDT
{
  nodeYear * firstYear;
  nodeYear * current;
} yearCDT;

static void freeYearRec(nodeYear * first);

/*static int
compare(unsigned int  c1, unsigned int c2)
{
    return c1-c2;
}*/

yearADT newYears (void)
{
    return calloc(1,sizeof(yearCDT));
}

static void
addByGender(nodeYear * node, int gen)
{
    if(gen==MALE)
    {
        node->male ++;
    }
    else
    {
        node->female ++;
    }
}

static nodeYear *
addYearRec(nodeYear * node, int year, int gen, int * flag)
{
    if(node == NULL || year < node->year )
    {
        nodeYear * aux = calloc(1,sizeof(nodeYear));
        aux->tail = node;
        aux->year = year;
        addByGender(aux,gen);
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
int
addYear (yearADT yearSet, int year, int gen)
{
    int flag = 0;
    //printf("Entra a ADD YEAR\n");
    yearSet->firstYear = addYearRec(yearSet->firstYear,year,gen,&flag);
    return flag;
}

void
freeYears(yearADT years)
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
