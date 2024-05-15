#pragma once 

#include "../funciones/funciones.h"
#include "../lista/lista.h"
#include"../nodo/nodo.h"


typedef int (*FuncionHash)(void *llave);

typedef struct _Tupla
{
    void *llave;
    void *dato;

}Tupla;

typedef struct _TablaHash
{
    FuncionHash hash1;
    FuncionHash hash2;

    ListaDoble *slots;
    int size;
    int capacidad;

    char tipocolision[15];
}TablaHash;



void initTableHash(TablaHash *tabla, int capacidad, FuncionHash hash1, FuncionHash hash2, char *colision);
void Put(TablaHash *tabla, Tupla *dato);
float factorCarga(TablaHash tabla);

int linearProbing(void *index);
int quadraticProbing(int index, int time);
int heuristicaDoubleHash(int a, int b, int times );

int miHashFunc(void *llave);
void printTupla(void *a);
void printTabla(TablaHash tabla);
void insertBack(ListaDoble *lista, Tupla *dato);
Tupla* Get(TablaHash *tabla, char *llave, size_t size_llave);
float ecuacion(float x1, float x2);
// // gradiente de la ecuación
void gradiente(float x1, float x2, float *grad);
// // algoritmo de gradiente descendente
void SGD(float *pesos, float *grad, float alpha, int size);
// // función de error
float SSE(float true, float pred);
// // graficar información
void GRAFICARDOS(TablaHash tabla, char *llave);
void LiberarTablaHash(TablaHash *tabla);