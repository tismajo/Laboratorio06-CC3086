#include <iostream>
#include <pthread.h>
#include <vector>

using namespace std; 

struct ThreadData {
    int n;
    double result;
};

// Función que ejecutarán los hilos
void* calculate_term(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int n = data->n;
    data->result = 1.0 / (n * (n + 1)); // Cálculo del término de la serie
    pthread_exit(nullptr);
}

int main() {
    int max_n;

    // Pedir al usuario el valor máximo de n
    cout << "Ingrese el valor máximo de n: ";
    cin >> max_n;

    // Crear un vector para los hilos y los datos
    vector<pthread_t> threads(max_n);
    vector<ThreadData> thread_data(max_n);

    for (int i = 1; i <= max_n; ++i) {
        thread_data[i-1].n = i;
        pthread_create(&threads[i-1], nullptr, calculate_term, &thread_data[i-1]);
    }

    double sum = 0.0;

    // For para los resultados
    for (int i = 0; i < max_n; ++i) {
        pthread_join(threads[i], nullptr);
        sum += thread_data[i].result;
    }

    // Imprimir el resultado final
    cout << "El valor de convergencia de la serie es: " << sum << std::endl;

    return 0;
}
