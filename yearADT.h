#ifndef _yearADT_h
#define _yearADT_h

#include <stdio.h>
#include <stdlib.h>

#define MALE 1
#define FEMALE 2
#define NOT_SPECIFIED 9

typedef struct yearCDT * yearADT;

/*
*/
yearADT newYears (void);

/*recibe el set->provVec->years y crea un nodo
*/
int addInYear (yearADT yearSet, int year, int gen);

/*int getMale (yearADT * currentYear);
**int getFemale(yearADT * currentYear);
**devuelve los totales de hombres y mujeres como parametro de salida
**en su nombre retorna el total de donde esta el current
*/
int getTotals(yearADT yearSet, int * male, int * female/*, int * ns*/);

/*Permite añadir las cantidad male y female en el año
**donde esta parado current
*/
void addYearTotal(yearADT yearSet, size_t male, size_t female/*, size_t ns*/);

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
