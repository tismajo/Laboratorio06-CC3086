// Crear rutina. Los parámetros sonimportantes, setearslo y capturarlos.
// El programa lo que cebe hacer es apsar un parámetro desde la rutina principal hacia el hilo. ¿Qué hilo en el for está diciendo hola¡
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define NUM_THREADS 10

void *PrintHello(void *paramID) {
    // convertir puntero a void - puntero a int
    int *id; // puntero a int
    // Hacer el cast
    id = (int*)paramID; // Cast explícito de void* a int*
    printf("Hola mundo desde el pthread #%d!\n", *id);
    pthread_exit(NULL);
    return NULL;
}

int main(int argc, char *argv[]) {
    // Identificar hilos de manera segura.
    pthread_t threadsID[NUM_THREADS];

    // Parametro a compartir equivalente al num del n hilo
    int rc, t, param[NUM_THREADS];

    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // Cada hilo se crea individualmente y se hace join en el mismo ciclo.
    for(t=0; t<NUM_THREADS; t++) {
        printf("Rutina Main: creando el hilo No. %d\n", t);
        // Asignar valor al parámetro que pasará a subrutina.
        param[t] = t; // Para que cada uno tenga un valor diferente.
        rc = pthread_create(&threadsID[t], &attr, PrintHello, (void *)&param[t]);

        // verificar que todos los hilos se crearon correctamente.
        if(rc) {
            printf("ERROR: código retornado desde pthread_create()");
            exit(-1);
        }

        pthread_join(threadsID[t], NULL); // Join en el mismo ciclo.
    }

    pthread_attr_destroy;
    pthread_exit(NULL);
}
