#include <stdio.h>
#include <pthread.h>

// Estructura para pasar parámetros a los hilos.
struct Parametros {
    int inicio;
    int fin;
};

int n;

void* determinarDivisibilidad(void *arg) {
    struct Parametros *param = (struct Parametros *) arg;

    for(int i = param->inicio; i <= param->fin; i++) {
        if(i % 2 == 0) {
            printf("%d es divisible por 2\n", i);
        }
        if(i % 3 == 0) {
            printf("%d es divisible por 3\n", i);
        }
        if(i % 5 == 0) {
            printf("%d es divisible por 5\n", i);
        }
    }

    return NULL;
}

int main() {
    // Determinar el número de hilos con los que se quiere trabajar.
    int NUM_THREADS;
    printf("Ingresa el número de hilos con los que quieres trabajar: ");
    scanf("%d", &NUM_THREADS);
    pthread_t newthread[NUM_THREADS];

    // Determinar hasta qué número se quiere saber que es divisible entre los establecidos.
    printf("Ingresa el valor máximo: ");
    scanf("%d", &n);

    // Dividir el rango de números entre los hilos.
    int rango = n / NUM_THREADS;
    struct Parametros parametros[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        parametros[i].inicio = i * rango + 1;
        parametros[i].fin = (i + 1) * rango;

        // Ajustar el rango del último hilo para llegar hasta n (la cantidad ingresada por el usuario).
        if (i == NUM_THREADS - 1) {
            parametros[i].fin = n;
        }

        pthread_create(&newthread[i], NULL, determinarDivisibilidad, &parametros[i]);
    }

    // Esperar a que todos los hilos terminen.
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(newthread[i], NULL);
    }

    return 0;
}
