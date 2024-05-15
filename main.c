#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lista/lista.h"
#include "nodo/nodo.h"
#include "hash/hashtable.h"
#include "funciones/funciones.h"

int main(void)
{
    TablaHash log;
    initTableHash(&log, 3, miHashFunc, NULL, "linear");

    // Experimentos
    char nom_log[][10] = {"log_00", "log_10", "log_20"};
    float initX[3][2] = {{50, 10}, {0, 0}, {100, 200}};

    for (int exp = 0; exp < 3; exp++)
    {
        // tabla de información
        TablaHash experimento;
        initTableHash(&experimento, 4, miHashFunc, NULL, "linear");
        // inicializar en 4 espacios:  epocas, error, iteraciones, solución
        int epocas = 0;
        float *error = malloc(10 * sizeof(float));
        float solucion[2] = {0};
        int iteraciones = 0;
        // variables del experimento
        const int count = 100;

        // X1, X2
        float exis[2] = {initX[exp][0], initX[exp][1]};
        // gradiente numérico
        float grad[2] = {0};
        // tasa de aprendizaje
        float alpha = 0.9;
        // error mínimo aceptado
        float tolerancia = 1e-8;

        for (int i = 0; i < count; i++)
        {
            float y = ecuacion(exis[0], exis[1]);
            // guardar la solución
            solucion[0] = exis[0];
            solucion[1] = exis[1];

            // error, se busca el 0 por eso 0-y
            float e = SSE(0, y);

            // guardar el error
            error[i] = e;
            printf("[%d] %.4f, \t %.4f, \t %.4f, \t %.4f\n", i, exis[0], exis[1], y, e);
            if (e <= tolerancia)
                break;
            gradiente(exis[0], exis[1], grad);
            SGD(exis, grad, alpha, 2);

            // guardar las iteraciones actuales
            iteraciones = i;
        }

        // guardar la información en una tabla hash
        Put(&experimento, &(Tupla){"epocas", &epocas});
        Put(&experimento, &(Tupla){"error", error});
        Put(&experimento, &(Tupla){"iteraciones", &iteraciones});
        Put(&experimento, &(Tupla){"solucion", &solucion});

        // guardar el experimento en una tabla hash
        Put(&log, &(Tupla){nom_log[exp], &experimento});

        // imprimir solución
        printf("solucion X1= %.3f, X2=%.3f; F(X1,X2)= %.3f\n", exis[0], exis[1], ecuacion(exis[0], exis[1]));

        // liberar memoria del arreglo 'error'
        free(error);
    }

    // Graficar
    for (int i = 0; i < log.size; i++)
    {
        GRAFICARDOS(log, nom_log[i]);
    }

    // liberar memoria de las tablas hash
    for (int i = 0; i < log.capacidad; i++)
    {
        LiberarLista(&log.slots[i]);
    }
    free(log.slots);

    return 0;
}

