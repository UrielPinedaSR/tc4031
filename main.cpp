#include <iostream>
#include <vector>
#include <omp.h>
#include <cstdlib> // Para rand() y srand()
#include <ctime>   // Para time()

void initializeRandom(std::vector<int>& arr) {
    for (int& num : arr) {
        num = rand() % 100; // Valores aleatorios entre 0 y 99
    }
}

void printArray(const std::vector<int>& arr, const std::string& name, int limit = 10) {
    std::cout << name << ": ";
    for (int i = 0; i < std::min(limit, static_cast<int>(arr.size())); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "...\n";
}

int main() {
    const int arraySize = 1000; // Tamaño del arreglo
    std::vector<int> array1(arraySize);
    std::vector<int> array2(arraySize);
    std::vector<int> result(arraySize);

    // Inicializar números aleatorios
    srand(static_cast<unsigned>(time(0)));
    initializeRandom(array1);
    initializeRandom(array2);

    // Imprimir una parte de los arreglos originales
    printArray(array1, "Array1");
    printArray(array2, "Array2");

    // Realizar la suma en paralelo usando OpenMP
#pragma omp parallel for
    for (int i = 0; i < arraySize; i++) {
        result[i] = array1[i] + array2[i];
    }

    // Imprimir una parte del arreglo resultante
    printArray(result, "Result");

    return 0;
}
