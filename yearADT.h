#ifndef _yearADT_h
#define _yearADT_h

#include <stdio.h>
#include <stdlib.h>

enum gender {MALE = 1, FEMALE, NOT_SPECIFIED = 9};

//Estructura para los nacimientos por año, funciona como lista bag.
typedef struct yearCDT * yearADT;


/*
** Función:         newYears
** Uso:             years = newYears();
** ------------------------------------------------------------------
** Descripción:     Inicializa la lista.
**                  Si no se pudo asignar memoria, retorna NULL.
** ------------------------------------------------------------------
** Precondición:    -
** Postcondición:   Lista de años con nacimientos y géneros.
*/
yearADT newYears (void);


/*
** Función:         addInYear
** Uso:             addInYear(years, 2016, 9, 1);
** ------------------------------------------------------------------
** Descripción:     Agrega qty nacimientos en el año year.
**                  Retorna 1 si pudo añadir los nacimientos.
** ------------------------------------------------------------------
** Precondición:    Lista de años válida, previamente creada.
** Postcondición:   Lista years con los nuevos nacimientos.
*/
int addInYear(yearADT yearSet, int year, int gen, size_t qty);


/*
** Función:         getCurrentTotals
** Uso:             getCurrentTotals(auxYearSet, &male, &female, &ns, &year)
** ------------------------------------------------------------------
** Descripción:     Retorna como parametro entrada/salida los totales
**                  de hombres, mujeres y no especificado. En su nombre
**                  retorna la suma total de los sexos nacidos ese año.
** ------------------------------------------------------------------
** Precondición:    Lista de años válida. toBeginYear iniciado.
** Postcondición:   -
*/
int getCurrentTotals(yearADT yearSet, size_t * male, size_t * female, size_t * ns, int * year);


/*
** Función:         toBeginYear
** Uso:             toBeginYear(auxYearSet)
** ------------------------------------------------------------------
** Descripción:     Inicia el iterador de currentYear.
** ------------------------------------------------------------------
** Precondición:    Lista de años válida, previamente creada.
** Postcondición:   Se pueden iterar los años.
*/
void toBeginYear (yearADT yearSet);


/*
** Función:         nextYear
** Uso:             nextYear(yearSet);
** ------------------------------------------------------------------
** Descripción:     Avanza el iterador.
** ------------------------------------------------------------------
** Precondición:    Lista de años válida, previamente creada e iterada.
** Postcondición:   Avanza el iterador al próximo año.
*/
void nextYear (yearADT yearSet);


/*
** Función:         hasNextYear
** Uso:             hasNextYear(yearSet)
** ------------------------------------------------------------------
** Descripción:     Retorna en su nombre si hay un siguiente año
**                  en la lista.
** ------------------------------------------------------------------
** Precondición:    Lista de años válida, previamente creada y toBeginYear
**                  ejecutado.
** Postcondición:   -
*/
int hasNextYear (yearADT yearSet);


/*
** Función:         freeYears
** Uso:             freeYears(yearSet)
** ------------------------------------------------------------------
** Descripción:     Elimina la lista de años y libera los recursos
**                  previamente reservados en la memoria.
**------------------------------------------------------------------
** Precondición:    Lista de años creada y válida.
** Postcondición:   Los recursos utilizados por la lista  fueron liberados.
*/
void freeYears(yearADT years);

#endif
