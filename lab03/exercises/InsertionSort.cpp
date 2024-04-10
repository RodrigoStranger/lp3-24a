#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

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

// Definimos nuestra funcion para generar un contenedor de peores casos
vector<vector<int>> generarYAlmacenarPeoresCasos(int n) {
    vector<vector<int>> peoresCasos;
    for (int i = 1; i <= n; i++) {
        vector<int> peorCaso(i);
        int valor = i;
        for (int j = 0; j < i; j++) {
            peorCaso[j] = valor;
            --valor;
        }
        peoresCasos.push_back(peorCaso);
    }
    return peoresCasos;
}

// Funcion principal de ejecucion
int main() {
    // Creamos nuestro numero de casos
    int casos = 10000;
    // Generando Datos....
    cout<<"Generando datos....";
    // Generamos nuestro vector de vectores llamado Contenedor3 con el numero de casos establecidos
	vector<vector<int>> Contenedor2 = generarYAlmacenarPeoresCasos(casos);
    // Determinamos la longitud del vector de vectores
    int longitud = Contenedor2.size();
    // Generamos nuestro Archivo.dat, Ordenamos cada caso y medimos el tiempo de ejecucion
    ofstream myfile;
    myfile.open("InsertionSort.dat");
    for (int i = 0; i < longitud; i++) {
        myfile << i+1 << "\t" << MedirTiempo(Contenedor2[i]).count() << endl;
    }
	myfile.close();
    // Datos generados....
    cout<<"Datos generados...."<<endl;
}
