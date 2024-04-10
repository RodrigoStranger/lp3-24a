#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std;

// Definimos nuestra funcion InsertionSort
void InsertionSort(vector<int>& arr, int n) { 
    for (int i = 1;i < n; i++) { 
        int key = arr[i];
        int j = i - 1;
        while (j > - 1 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Definimos nuestra funcion en la cual mide el tiempo en microsegundos
chrono::microseconds MedirTiempo(vector<int>& arr) {
    typedef chrono::high_resolution_clock clock;
    auto inicio = clock::now();
    InsertionSort(arr, arr.size());
    auto fin = clock::now();
    auto duracion = chrono::duration_cast<chrono::microseconds>(fin - inicio);
    return duracion;
}

// Definimos nuestra funcion para imprimir un vector
void PrintArray(vector<int>& arr, int longitud) {
    for (int i = 0; i < longitud; i++) {
        cout <<arr[i] << " ";
    }
}

// Definimos nuestra funcion para imprimir un vector de vectores
void PrintArrayContenedor(vector<vector<int>>& arr, int longitud) {
    for (int i = 0; i < longitud; ++i) {
        cout << i + 1 << ": ";
        PrintArray(arr[i], arr[i].size());
        cout<<endl;
    }
}

int main() {
    vector<int> caso1={5,2,4,6,1,3};
    cout<<"Array Inicial: ";
    PrintArray(caso1);
    cout<<endl;
    cout<<"Ordenando el Array:"<<endl;
    InsertionSort(caso1);
    cout<<endl;
    cout<<"Resultado Final: ";
    PrintArray(caso1);
    return 0;
}
