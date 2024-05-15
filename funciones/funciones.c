#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funciones.h"
#include "../lista/lista.h"
#include"../nodo/nodo.h"

void IniciarListaDoble(ListaDoble *lista) {
    lista->head = NULL;
    lista->tail = NULL;
    lista->size = 0;
}

void AddHead(ListaDoble *lista, void *dato) {
    NodoDoble *nuevo = (NodoDoble *)malloc(sizeof(NodoDoble));
    if (nuevo == NULL) {
        printf("Error: No se pudo asignar memoria para el nuevo nodo\n");
        return;
    }
    nuevo->data = dato;
    nuevo->next = lista->head;
    nuevo->prev = NULL;
    if (lista->head != NULL) {
        lista->head->prev = nuevo;
    } else {
        lista->tail = nuevo;
    }
    lista->head = nuevo;
    lista->size++;
}

void AddTail(ListaDoble *lista, void *dato) {
    NodoDoble *nuevo = (NodoDoble *)malloc(sizeof(NodoDoble));
    if (nuevo == NULL) {
        printf("Error: No se pudo asignar memoria para el nuevo nodo\n");
        return;
    }
    nuevo->data = dato;
    nuevo->next = NULL;
    nuevo->prev = lista->tail;
    if (lista->tail != NULL) {
        lista->tail->next = nuevo;
    } else {
        lista->head = nuevo;
    }
    lista->tail = nuevo;
    lista->size++;
}

NodoDoble *GetNodoPos(ListaDoble *lista, int pos) {
    NodoDoble *temp = lista->head;
    while (temp != NULL && pos > 0) {
        temp = temp->next;
        pos--;
    }
    return temp;
}



void ImprimirLista(ListaDoble *lista, void (*func)(void *)) {
    NodoDoble *actual = lista->head;
    while (actual != NULL) {
        func(actual->data);
        actual = actual->next;
    }
}


void LiberarLista(ListaDoble *lista) {
    NodoDoble *temp;
    while (lista->head != NULL) {
        temp = lista->head;
        lista->head = lista->head->next;
        free(temp->data);
        free(temp);
    }
    lista->tail = NULL;
    lista->size = 0;
}

NodoDoble *GetNodo(ListaDoble *lista, void *dato) {
    NodoDoble *temp = lista->head;
    while (temp != NULL) {
        if (temp->data == dato) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void BorrarNodo(ListaDoble *lista, void *dato) {
    NodoDoble *curr = GetNodo(lista, dato);
    if (curr == NULL) {
        printf("No se encontro el nodo\n");
        return;
    }

    if (curr->prev == NULL) {
        lista->head = curr->next;
    } else {
        curr->prev->next = curr->next;
    }

    if (curr->next == NULL) {
        lista->tail = curr->prev;
    } else {
        curr->next->prev = curr->prev;
    }

    free(curr);
    lista->size--;
}

int comparar(void *a, void *b) {
    int *int_a = (int *)a;
    int *int_b = (int *)b;
    return (*int_a - *int_b);
}

int compararchar(const void *a, const void *b) {
    if (*(char *)a < *(char *)b) return -1;
    if (*(char *)a > *(char *)b) return 1;
    return 0;
}

void imprimir_entero(void *dato) {
    int *valor = (int *)dato;
    printf("%d ", *valor);
}

int isEmptyList(ListaDoble *lista) {
    return lista->head == NULL;
}
