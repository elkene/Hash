#pragma once
typedef struct _NodoDoble {
    void *data;
    struct _NodoDoble *next;
    struct _NodoDoble *prev;
    struct _NodoDoble *current;
} NodoDoble;

