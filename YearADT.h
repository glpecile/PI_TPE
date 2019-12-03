#ifndef _yearADT_h
#define _yearADT_h

    #include <stdio.h>
	#include <stddef.h>
    #include <stdlib.h>

    typedef struct yearCDT * yearADT;

    yearADT newYears (void);

    //recibe la el set->provVec->years y crea un nodo
    int addYear (yearADT yearSet, int year, int gen);

    void toBeginYear (yearADT yearSet);

    yearADT * nextYear (yearADT yearSet);

    int hasNextYear (yearADT yearSet);

    //int getMale (yearADT * currentYear);
    //int getFemale(yearADT * currentYear);
    //devuelve los totales de hombres y mujeres como parametro de salida
    //en su nombre retorna el total de donde esta el current
    int getTotals (yearADT yearSet, int * male, int * female);

    //para Q2 el usuario invoca
    void addYearTotal(yearADT yearSet, size_t male, size_t female);

    void freeYears(yearADT years);

#endif
