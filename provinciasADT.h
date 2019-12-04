#ifndef _provinciasADT_hProvincias
#define _provinciasADT_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "yearADT.h"
__attribute__((used)) static void error(int errorCode, const char *s)
{
    fprintf(stderr, "\nERROR: %s\n",s);
    exit(errorCode);
}
typedef struct provCDT * provADT;
typedef struct tPercentList * percentList;

/*
*/
provADT newSet(void);

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
int getTotalProv(provADT set, yearADT yearSet);

/*
*/
size_t getTotalSet(provADT set);

/*
*/
size_t getQtyProv(provADT set);

/*
*/
char * getName(provADT set);

/*
*/
void freeSet(provADT set);

//FUNCIONES AUXILIARES DE PRUEBA
    void printProv(provADT set);

    void printVec(provADT set);

    void query(provADT set);

#endif
