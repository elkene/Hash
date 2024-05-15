#pragma once
#include "../lista/lista.h"
#include"../nodo/nodo.h"

void IniciarListaDoble(ListaDoble *lista);
void AddHead(ListaDoble *lista, void *dato);
void AddTail(ListaDoble *lista, void *dato);
NodoDoble *GetNodoPos(ListaDoble *lista, int pos);

void ImprimirLista(ListaDoble *lista, void (*func)(void *));

void LiberarLista(ListaDoble *lista);
NodoDoble *GetNodo(ListaDoble *lista, void *dato);
void BorrarNodo(ListaDoble *lista, void *dato);
int comparar(void *a, void *b);

int compararchar(const void *a, const void *b);

void imprimir_entero(void *dato);
int isEmptyList(ListaDoble *lista);