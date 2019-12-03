#include "YearADT.h"
#include <stddef.h>
#define MALE 1
#define FEMALE 2
typedef struct nodeYear //estructura para el año Funciona como lista
{
    unsigned int year;
    size_t male;    //Cantidad de hombres
    size_t female;  //Cantidad de mujeres
    struct nodeYear * tail;
} nodeYear;

typedef struct yearCDT
{
  nodeYear * firstYear;
  nodeYear * current;
} yearCDT;


static int
compare(unsigned int  c1, unsigned int c2)
{
    return c1-c2;
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

nodeYear *
addYearRec(nodeYear * node, int year, int gen, int * flag)
{
    if(node == NULL || year<node->year)
    {
        nodeYear * aux = malloc(sizeof(nodeYear));
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
    return node->tail;

}
int
addYear (yearADT yearSet, int year, int gen)
{
    int flag = 0;
    printf("ADD YEAR\n");
    yearSet->firstYear = addYearRec(yearSet->firstYear,year,gen,&flag);
    return flag;
}
