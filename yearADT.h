#ifndef _yearADT_h
#define _yearADT_h

#include <stdio.h>
#include <stdlib.h>

enum gender {MALE = 1, FEMALE, NOT_SPECIFIED = 9};

typedef struct yearCDT * yearADT;

/*
** Inicializa la lista.
** Función:
** Uso:
** ------------------------------------------------------------------
** Descripción:
** ------------------------------------------------------------------
** Precondición:
** Postcondición:
*/
yearADT newYears (void);

/*
** Recibe el set->provVec->years y crea un nodo nuevo si el año no existe.
** Si el año ya existe, actúa como bagADT y suma uno a su género correspondiente.
** Función:
** Uso:
** ------------------------------------------------------------------
** Descripción:
** ------------------------------------------------------------------
** Precondición:
** Postcondición:
*/
int addInYear(yearADT yearSet, int year, int gen, size_t qty);

/*
** Retorna como parametro entrada/salida los totales de hombres, mujeres y no especificado.
** En su nombre retorna la suma total de los sexos nacidos ese año.
** Función:
** Uso:
** ------------------------------------------------------------------
** Descripción:
** ------------------------------------------------------------------
** Precondición:
** Postcondición:
*/
int getCurrentTotals(yearADT yearSet, size_t * male, size_t * female, size_t * ns, int * year);

/*
** Inicia el iterador de currentYear.
** Función:
** Uso:
** ------------------------------------------------------------------
** Descripción:
** ------------------------------------------------------------------
** Precondición:
** Postcondición:
*/
void toBeginYear (yearADT yearSet);

/*
** Avanza el iterador.
** Función:
** Uso:
** ------------------------------------------------------------------
** Descripción:
** ------------------------------------------------------------------
** Precondición:
** Postcondición:
*/
void nextYear (yearADT yearSet);

/*
** Retorna en su nombre si hay un siguiente nodo en la lista.
** Función:
** Uso:
** ------------------------------------------------------------------
** Descripción:
** ------------------------------------------------------------------
** Precondición:
** Postcondición:
*/
int hasNextYear (yearADT yearSet);

/*
** Libera la lista llamando a su función recursiva para los nodos.
** Función:
** Uso:
** ------------------------------------------------------------------
** Descripción:
** ------------------------------------------------------------------
** Precondición:
** Postcondición:
*/
void freeYears(yearADT years);

#endif
