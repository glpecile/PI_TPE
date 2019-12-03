#include "YearADT.h"
#include <stddef.h>
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


void addYear (yearADT yearSet, unsigned int year, size_t male, size_t female);

void toBeginYear (yearADT yearSet);

yearADT * nextYear (yearADT yearSet);

int hasNextYear (yearADT yearSet);

int getMale (yearADT * currentYear);

int getFemale(yearADT * currentYear);

int getTotal (yearADT * currentYear);

