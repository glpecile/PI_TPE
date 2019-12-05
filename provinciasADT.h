#ifndef _provinciasADT_h
#define _provinciasADT_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "yearADT.h"

typedef struct provCDT * provADT;
typedef struct tPercentList * percentList;

/*
** Función:         newSet
** Uso:             set = newSet();
** ------------------------------------------------------------------
** Descripción:     Inicializa el set de provincias.
** ------------------------------------------------------------------
** Precondición:    -
** Postcondición:   Set de provincias creados.
*/
provADT newSet(void);

/*
** Función:         addProv
** Uso:             res = addProv(set, 06, "Buenos Aires");
** ------------------------------------------------------------------
** Descripción:     Inserta una provincia al set. Se insertan de forma
**                  ordenada por código.
**                  Retorna 1 si lo pudo agregar.
** ------------------------------------------------------------------
** Precondición:    Set que sea válido, previamente creado.
** Postcondición:   Set con la nueva provincia.
*/
int addProv(provADT set, int code, char * value);

/*
** Función:         finalizeProvAddition
** Uso:             finalizeProvAddition(set);
** ------------------------------------------------------------------
** Descripción:     Indica que se terminó el proceso de adición de
**                  provincias, y prepara la estructura de datos
**                  para comenzar a cargar los datos de nacimientos.
**                  Debe usarse una vez que se termina de agregar las provincias.
                    Retorna 1 si pudo preparar la estructura.
** ------------------------------------------------------------------
** Precondición:    Set que sea válido, previamente creado.
** Postcondición:   Estructura preparada para cargar nacimientos.
*/
int finalizeProvAddition(provADT set);

/*
** Función:         addBirth
** Uso:             addBirth(set,2015,06,2);
** ------------------------------------------------------------------
** Descripción:     Agrega un nacimiento en la provincia de código
**                  provres. Recibe el año del nacimiento (year), el
**                  género del nacido (gen) y el código de la
**                  provincia donde se debe agregar (provres).
**                  Retorna 1 si pudo agregar, 0 si no.
** ------------------------------------------------------------------
** Precondición:    Set que sea válido al igual que el provres. Si se
**                  agrega un codigo provres que no forma parte de las
**                  provincias previamente agregadas no se agrega el
**                  nacimiento ingresado.
** Postcondición:   Se agrega un nacimiento al set.
*/
int addBirth(provADT set, int year, int provres, int gen);

/*
** Función:         alphaSort
** Uso:             alphaSort(set);
** ------------------------------------------------------------------
** Descripción:     Prepara la estructura set para poder iterar sobre
**                  la misma en orden alfabético. Una vez que se llama ésta
**                  no se pueden seguir cargando de nacimientos.
**                  Está pensada para ser utilizada únicamente luego
**                  de la carga de datos.
** ------------------------------------------------------------------
** Precondición:    Estructura preparada para cargar nacimientos,
**                  finalizeProvAddition ejecutado previamente.
** Postcondición:   Estructura ordenada alfabéticamente.
*/
void alphaSort(provADT set);

/*
** Función:         toBeginProv
** Uso:             toBeginProv(set);
** ------------------------------------------------------------------
** Descripción:     Prepara la estructura para poder iterar sobre las
**                  provincias almacenadas en el set.
** ------------------------------------------------------------------
** Precondición:    Estructura con las provincias previamente cargadas.
** Postcondición:   Estructura preparada para iterar en el set.
*/
void toBeginProv(provADT set);

/*
**
** Función:         hasNextProv
** Uso:             hasNextProv(set);
** ------------------------------------------------------------------
** Descripción:     Retorna en su nombre si hay un próximo vector en
**                  la estructura.
** ------------------------------------------------------------------
** Precondición:    Debe haberse ejecutado toBeginProv.
** Postcondición:               -
*/
int hasNextProv(provADT set);

/*
**
** Función:          nextProv
** Uso:              nextProv(set)
** ------------------------------------------------------------------
** Descripción:     Itera sobre la estructura.
** ------------------------------------------------------------------
** Precondición:    Se debe haber asegurado que existe una provincia
**                  siguiente, utilizando hasNextProv.
** Postcondición:   Avanza el iterador a la próxima provincia.
*/
void nextProv(provADT set);

/*
** Función:
** Uso:
** ------------------------------------------------------------------
** Descripción:     Retorna en su nombre el total de la provincia
                    donde está el currentTotal. En la estructura
                    de parametro entrada/salida yearSet va guardando
                    el total de nacimientos por año.
** ------------------------------------------------------------------
** Precondición:
** Postcondición:
*/
int getTotalProv(provADT set, yearADT yearSet);

/*
** Retorna en su nombre el total de nacimientos.
** Función:
** Uso:
** ------------------------------------------------------------------
** Descripción:
** ------------------------------------------------------------------
** Precondición:
** Postcondición:
*/
size_t getTotalSet(provADT set);

/*
** Retorna en su nombre la cantidad de provincias.
** Función:
** Uso:
** ------------------------------------------------------------------
** Descripción:
** ------------------------------------------------------------------
** Precondición:
** Postcondición:
*/
size_t getQtyProv(provADT set);

/*
** Retorna en su nombre la provincia actual.
** Función:
** Uso:
** ------------------------------------------------------------------
** Descripción:
** ------------------------------------------------------------------
** Precondición:
** Postcondición:
*/
char * getName(provADT set);

/*
** Libera la estructura junto con sus nodos y vector.
** Función:         freeSet
** Uso:             freeSet(set);
** ------------------------------------------------------------------
** Descripción:     Elimina el set, liberando todos los recursos en
**                  memoria utilizados.
** ------------------------------------------------------------------
** Precondición:    Set válido.
** Postcondición:
*/
void freeSet(provADT set);

#endif
