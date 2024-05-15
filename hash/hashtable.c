#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include "../hash/hashtable.h"
#include "../funciones/funciones.h"
#include "../lista/lista.h"
#include"../nodo/nodo.h"
void initTableHash(TablaHash *tabla, int capacidad, FuncionHash hash1, FuncionHash hash2, char *colision) {
    tabla->hash1 = hash1;
    tabla->hash2 = hash2;
    tabla->capacidad = capacidad;
    tabla->size = 0;
    strcpy(tabla->tipocolision, colision);

    tabla->slots = (ListaDoble*)malloc(capacidad * sizeof(ListaDoble));
    for (int i = 0; i < capacidad; i++) {
        IniciarListaDoble(&tabla->slots[i]);
    }
}
void Put(TablaHash *tabla, Tupla *dato)
{
    int indice=tabla->hash1(dato->llave)% tabla->capacidad;
    AddTail(&tabla->slots[indice],dato);
    tabla->size++;
}


float factorCarga(TablaHash tabla) {
    return (float)tabla.size / tabla.capacidad;
}

int linearProbing(void *index) {
    return *((int*)index) + 1;
}

int quadraticProbing(int index, int time) {
    return index + (time * time);
}

int heuristicaDoubleHash(int a, int b, int times) {
    return a + (times * b);
}



int miHashFunc(void *llave)
{
    char *ll = (char*) llave;
    int letra = ll[0];

    if(letra >= 'A' && letra <= 'Z')
    {
        return letra - 'A';
    }

    return letra - 'a';

}

void printTupla(void *a)
{
    Tupla d= *(Tupla *)a;
    printf("(%s ,%s),",(char *)d.llave, (char *)d.dato);
}

void printTabla(TablaHash tabla)
{
    for(int i = 0; i<tabla.capacidad; i++)
    {
        ListaDoble *l = &tabla.slots[i];
        printf("[%d]",i);
        ImprimirLista(l,printTupla);
        printf("\n");
    }
}

void insertBack(ListaDoble *lista, Tupla *dato) {
    NodoDoble *nuevoNodo = (NodoDoble*)malloc(sizeof(NodoDoble));
    nuevoNodo->data = dato;
    nuevoNodo->next = NULL;

    if (isEmptyList(lista)) {
        nuevoNodo->prev = NULL;
        lista->head = nuevoNodo;
        lista->tail = nuevoNodo;
    } else {
        nuevoNodo->prev = lista->tail;
        lista->tail->next = nuevoNodo;
        lista->tail = nuevoNodo;
    }
}

Tupla* Get(TablaHash *tabla, char *llave, size_t size_llave) {
    int indice = tabla->hash1(llave) % tabla->capacidad;
    ListaDoble lista = tabla->slots[indice];
    NodoDoble *current = lista.head;
    while (current != NULL) {
        Tupla *tupla = (Tupla *)current->data;
        if (strcmp((char *)tupla->llave, llave) == 0) {
            return tupla;
        }
        current = current->next;
    }
    return NULL;
}

float ecuacion(float x1, float x2)
{
    return (x1 - 2) * (x1 - 2) + (x2 + 3) * (x2 + 3);
}
// gradiente de la ecuación
void gradiente(float x1, float x2, float *grad)
{
    grad[0] = 2 * (x1 - 2) * 1;
    grad[1] = 2 * (x2 + 3) * 1;
}
// algoritmo de gradiente descendente
void SGD(float *pesos, float *grad, float alpha, int size)
{
    for (int i = 0; i < size; i++)
        pesos[i] = pesos[i] - alpha * grad[i];
}
// función de error
float SSE(float true, float pred)
{
    return (true - pred) * (true - pred);
}
// graficar información
void GRAFICARDOS(TablaHash tabla, char *llave)
{
    Tupla dic = *Get(&tabla, llave, sizeof(char *));
    TablaHash *subtabla = (TablaHash *)dic.dato;
    // Tupla dominio = *Get(subtabla, "epocas", sizeof(char *));
    Tupla solucion = *Get(subtabla, "solucion", sizeof(char *));
    Tupla error = *Get(subtabla, "error", sizeof(char *));
    Tupla iteraciones = *Get(subtabla, "iteraciones", sizeof(char *));

    // graficar
    FILE *gnuplot = fopen("gnuplot -persistent", "w");

    fprintf(gnuplot, "set multiplot layout 1,2 title '%s'\n", (char *)llave);

    // PLOT ERROR
    fprintf(gnuplot, "set style line 1 lt rgb '#ff0000' lw 3 pt 7 \n");
    fprintf(gnuplot, "set title 'error de (x1-2)^2 + (x2+3)^2 = 0' \n");
    fprintf(gnuplot, "set xlabel 'Iteraciones' \n");
    fprintf(gnuplot, "set ylabel 'Error' \n");
    fprintf(gnuplot, "plot '-' using 1:2 with linespoints ls 1\n");
    for (int i = 0; i < *(int *)iteraciones.dato; i++)
        fprintf(gnuplot, "%d %f\n", i + 1, ((float *)error.dato)[i]);
    fprintf(gnuplot, "e\n");

    // PLOT FX y SOLUCIÓN
    fprintf(gnuplot, "set style line 1 lt rgb '#0000ff' lw 3 pt 7 \n");
    fprintf(gnuplot, "set title 'F(X)= (x1-2)^2 + (x2+3)^2' \n");
    fprintf(gnuplot, "set xlabel 'X1' \n");
    fprintf(gnuplot, "set ylabel 'X2' \n");
    fprintf(gnuplot, "set zlabel 'F(X1,X2)' \n");
    fprintf(gnuplot, "splot '-' using 1:2:3 with linespoints ls 1, ");
    fprintf(gnuplot, "'-' using 1:2:3:(1) with points lc rgb 'red' pt 2 ps 4\n");
    fprintf(gnuplot, "set view 0, 0\n");
    for (int x1 = -3; x1 <= 3; x1++)
    {
        for (int x2 = -3; x2 <= 3; x2++)
        {
            fprintf(gnuplot, "%d %d %f\n", x1, x2, ecuacion(x1, x2));
        }
    }
    fprintf(gnuplot, "e\n");
    float solx[2] = {((float *)solucion.dato)[0], ((float *)solucion.dato)[1]};
    fprintf(gnuplot, "%f %f %f\n", solx[0], solx[1], ecuacion(solx[0], solx[1]));
    fprintf(gnuplot, "e\n");
    fprintf(gnuplot, "unset multiplot\n");
    fflush(gnuplot);
}

void LiberarTablaHash(TablaHash *tabla) {
    free(tabla->slots);
}
