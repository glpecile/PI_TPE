#ifndef _provinciasADT_h
#define _provinciasADT_h

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <errno.h>

    typedef struct provCDT * provADT;

    /*Funciones*/

    /*
    newSet
    **
    addProvincia ""
    **
    addNacimiento

    */

    provADT newSet(void); //Ingreso de Datos de un nuevo pais

    int addProv(provADT set, char * code, char * value);

    int addBirth(provADT set, char * year, char * provres, char gen);

    void finalizeProvAddition(provADT set);

    void alphaSort(provADT set);

    void printProv(provADT set);

    void query(provADT set);

    void toBeginProv(provADT set);

    int hasNextProv(provADT set);

    void nextProv(provADT set);

    void freeSet(provADT set);

#endif
