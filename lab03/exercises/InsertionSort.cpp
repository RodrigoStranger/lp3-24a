// Commit 2: cc937eb4f
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std;

// Commit 5: f6acea3
using namespace std::chrono;

// Commmit 1: c88f6a2
// Commit 2: cc937eb4
// Definimos nuestra funcion InsertionSort  
void InsertionSort(vector<int>& arr, int n) { 
    for (int i = 1; i < n; i++) { 
        int key = arr[i];
        int j = i - 1;
        while (j > -1 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Commit 3: 43efb6e
// Definimos nuestra funcion en la cual mide el tiempo en microsegundos
chrono::microseconds MedirTiempo(vector<int>& arr) {
    typedef chrono::high_resolution_clock clock;
    auto inicio = clock::now();
    InsertionSort(arr, arr.size());
    auto fin = clock::now();
    auto duracion = chrono::duration_cast<chrono::microseconds>(fin - inicio);
    return duracion;
}

// Commit 4: 81e701e
// Definimos nuestra funcion para imprimir un vector
void PrintArray(const vector<int>& arr,const int longitud) {
    for (int i = 0; i < longitud; i++) {
        cout <<arr[i] << " ";
    }
}

// Commit 7: 31fa36f
// Definimos nuestra funcion para imprimir un vector de vectores
void PrintArrayContenedor(const vector<vector<int>>& arr,const int longitud) {
    for (int i = 0; i < longitud; ++i) {
        cout << i + 1 << ": ";
        PrintArray(arr[i], arr[i].size());
        cout<<endl;
    }
}

// Commit 5: f6acea3
// Definimos nuestra funcion para generar un contenedor de peores casos
vector<vector<int>> GenerarYAlmacenarPeoresCasos(int n) {
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

// Commit 6: ee85f6b
// Commit 7: 31fa36f
// Funcion principal de ejecucion
int main() {
    // Creamos nuestro numero de casos
    int casos;
    cout<< "Ingrese el numero de casos a tratar: ";
    cin >> casos;
    
    // Generamos nuestro vector de vectores llamado Contenedor2 con el numero de casos establecidos
    vector<vector<int>> Contenedor2 = GenerarYAlmacenarPeoresCasos(casos);
    
    // Generando Datos....
    cout << "Generando datos...." << endl;

    // Abriendo el archivo para escritura
    ofstream myfile("InsertionSort.dat");

    // Ordenamos cada caso y medimos el tiempo de ejecución de cada caso y duracion final del progama, escribiendo en el archivo
    typedef chrono::high_resolution_clock clock;
    auto inicio1 = clock::now();
    for (int i = 0; i < casos; i++) {
        auto tiempo = MedirTiempo(Contenedor2[i]);
        myfile << i + 1 << "\t" << tiempo.count() << endl;
    }
    auto fin1 = clock::now();
    auto duracion1 = chrono::duration_cast<chrono::seconds>(fin1 - inicio1);
    myfile.close();
    
    // Datos generados....
    cout << "Datos generados...." << endl;
    cout << "Duracion final de los ordenamientos: "<<duracion1.count()<<" segundos";
    return 0;
}