#ifndef _provinciasADT_h
#define _provinciasADT_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "yearADT.h"

typedef struct provCDT * provADT;

/*
** Función:         newSet
** Uso:             set = newSet();
** ------------------------------------------------------------------
** Descripción:     Inicializa el set de provincias.
**                  Si no se pudo asignar memoria, retorna NULL.
** ------------------------------------------------------------------
** Precondición:    -
** Postcondición:   Set de provincias creado.
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
**                  Retorna 1 si pudo preparar la estructura.
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
**                  la misma en orden alfabético.
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
** Función:         hasNextProv
** Uso:             hasNextProv(set);
** ------------------------------------------------------------------
** Descripción:     Retorna en su nombre si hay más provincia en
**                  la estructura.
** ------------------------------------------------------------------
** Precondición:    Debe haberse ejecutado toBeginProv.
** Postcondición:   -
*/
int hasNextProv(provADT set);


/*
** Función:         nextProv
** Uso:             nextProv(set)
** ------------------------------------------------------------------
** Descripción:     Itera sobre la estructura.
** ------------------------------------------------------------------
** Precondición:    Se debe haber asegurado que existe una provincia
**                  siguiente, utilizando hasNextProv.
** Postcondición:   Avanza el iterador a la próxima provincia.
*/
void nextProv(provADT set);


/*
** Función:         getTotalProv
** Uso:             getTotalProv(set, year);
**                  getTotalProv(set, NULL);
** ------------------------------------------------------------------
** Descripción:     Retorna en su nombre el total de nacimientos de la
**                  provincia donde está el iterador. En la estructura
**                  de parametro entrada/salida yearSet va guardando
**                  el total de nacimientos por año.
**                  Si sólo se desea obtener el total de nacimientos
**                  yearSet se debe pasar como NULL.
** ------------------------------------------------------------------
** Precondición:    Set valido con la estructura cargada con los
**                  nacimientos y provincias, y una estructura de
**                  tipo yearADT previamente creada.
** Postcondición:   La estructura de tipo yearADT obtiene todos los
**                  años con sus respectivos nacimientos.
*/
int getTotalProv(provADT set, yearADT yearSet);


/*
** Función:         getTotalSet
** Uso:             getTotalSet(set)
** ------------------------------------------------------------------
** Descripción:     Retorna en su nombre el total de nacimientos.
** ------------------------------------------------------------------
** Precondición:    Set válido con los nacimientos y las provincias
**                  cargadas
** Postcondición    -
*/
size_t getTotalSet(provADT set);


/*
**
** Función:         getQtyProv
** Uso:             getQtyProv(set)
** ------------------------------------------------------------------
** Descripción:     Retorna en su nombre la cantidad de provincias.
** ------------------------------------------------------------------
** Precondición:    Set válido con las provincias previamente cargadas
** Postcondición:   -
*/
size_t getQtyProv(provADT set);


/*
** Función:         getName
** Uso:             getName(set)
** ------------------------------------------------------------------
** Descripción:     Retorna en su nombre la provincia donde está el
**                  iterador.
** ------------------------------------------------------------------
** Precondición:    Set válido con las provincias previamente cargadas
**                  y el iterador inicializado. Además se debe haber
**                  ejecutado la funcion hasNextProv.
** Postcondición:   -
*/
char * getName(provADT set);


/*
** Función:         freeSet
** Uso:             freeSet(set);
** ------------------------------------------------------------------
** Descripción:     Elimina el set, liberando todos los recursos en
**                  memoria utilizados.
** ------------------------------------------------------------------
** Precondición:    Set válido.
** Postcondición:   Los recursos utilizados por el set fueron liberados.
*/
void freeSet(provADT set);

#endif
