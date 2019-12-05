#ifndef _yearADT_h
#define _yearADT_h

#include <stdio.h>
#include <stdlib.h>

enum gender {MALE = 1, FEMALE, NOT_SPECIFIED = 9};

typedef struct yearCDT * yearADT;

//Inicializa la lista.
yearADT newYears (void);

/*Recibe el set->provVec->years y crea un nodo nuevo si el año no existe.
Si el año ya existe, actúa como bagADT y suma uno a su género correspondiente.*/
int addInYear(yearADT yearSet, int year, int gen, size_t qty);

/*Retorna como parametro entrada/salida los totales de hombres, mujeres y no especificado.
En su nombre retorna la suma total de los sexos nacidos ese año.*/
int getCurrentTotals(yearADT yearSet, size_t * male, size_t * female, size_t * ns, int * year);

//Permite añadir las cantidad male, female y no especificado en el año donde esta parado current.
void addCurrentYearTotal(yearADT yearSet, size_t male, size_t female, size_t ns);

//Inicia el iterador de currentYear.
void toBeginYear (yearADT yearSet);

//Avanza el iterador.
void nextYear (yearADT yearSet);

//Retorna en su nombre si hay un siguiente nodo en la lista.
int hasNextYear (yearADT yearSet);

//Libera la lista llamando a su función recursiva para los nodos.
void freeYears(yearADT years);

#endif
