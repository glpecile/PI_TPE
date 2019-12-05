#ifndef _provinciasADT_h
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

//Inicializa la estructura.
provADT newSet(void);

//Agrega una provincia a la lista de la estructura, su función recursiva da el orden.
int addProv(provADT set, int code, char * value);

//Elimina la estructura de adición de datos llamando a listToArray.
void finalizeProvAddition(provADT set);

/*Agrega nacimientos a la provincia indicada llamando a addInYear en
yearADT desde un indice obtenido con binarySearch.*/
int addBirth(provADT set, int year, int provres, int gen);

//Ordena el vector en orden alfabetico.
void alphaSort(provADT set);

//Comienza el iterador.
void toBeginProv(provADT set);

//Retorna en su nombre si hay un próximo vector en la estructura.
int hasNextProv(provADT set);

//Itera al vector.
void nextProv(provADT set);

/*Retorna en su nombre el total de la provincia donde está el currentTotal.
En la estructura de parametro entrada/salida yearSet va guardando el
total de nacimientos por año.*/
int getTotalProv(provADT set, yearADT yearSet);

//Retorna en su nombre el total de nacimientos.
size_t getTotalSet(provADT set);

//Retorna en su nombre la cantidad de provincias.
size_t getQtyProv(provADT set);

//Retorna en su nombre la provincia actual.
char * getName(provADT set);

//Libera la estructura junto con sus nodos y vector.
void freeSet(provADT set);

#endif
