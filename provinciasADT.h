#ifndef _provinciasADT_h
#define _provinciasADT_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct provCDT * provADT;

/*
*/
provADT newSet(void); //Ingreso de Datos de un nuevo pais

/*
*/
int addProv(provADT set, int code, char * value);

/*
*/
void finalizeProvAddition(provADT set);

/*
*/
int addBirth(provADT set, int year, int provres, int gen);

/*
*/
void alphaSort(provADT set);

/*
*/
void toBeginProv(provADT set);

/*
*/
int hasNextProv(provADT set);

/*
*/
void nextProv(provADT set);

/*
*/
void freeSet(provADT set);


//FUNCIONES AUXILIARES DE PRUEBA
    void printProv(provADT set);

    void printVec(provADT set);

    void query(provADT set);

#endif