
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


void
addYear (yearADT yearSet, unsigned int year, size_t male, size_t female)
{

}

void
toBeginYear (yearADT yearSet)
{

}

nodeYear *
nextYear (provADT yearSet)
{

}

int
hasNextYear (provADT yearSet)
{

}

int
getMale (nodeYear * currentYear)
{

}

int
getFemale(nodeYear * currentYear)
{

}

int
getTotal (nodeYear * currentYear)
{

}
