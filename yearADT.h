#ifndef _yearADT_h
#define _yearADT_h

#include <stdio.h>
#include <stdlib.h>

enum gender {MALE = 1, FEMALE, NOT_SPECIFIED = 9};

typedef struct yearCDT * yearADT;

/*
*/
yearADT newYears (void);

/*recibe el set->provVec->years y crea un nodo
*/
int addInYear(yearADT yearSet, int year, int gen, size_t qty);

/*int getMale (yearADT * currentYear);
**int getFemale(yearADT * currentYear);
**devuelve los totales de hombres, mujeres y ns como parametro de salida
**en su nombre retorna el total de donde esta el current
*/
int getCurrentTotals(yearADT yearSet, size_t * male, size_t * female, size_t * ns, int * year);

/*Permite añadir las cantidad male y female en el año
**donde esta parado current
*/
void addCurrentYearTotal(yearADT yearSet, size_t male, size_t female, size_t ns);

/*
*/
void toBeginYear (yearADT yearSet);

/*
*/
void nextYear (yearADT yearSet);

/*
*/
int hasNextYear (yearADT yearSet);

/*
*/
void freeYears(yearADT years);

#endif
