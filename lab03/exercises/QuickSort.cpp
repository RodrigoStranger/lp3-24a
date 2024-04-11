#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

// Definimos nuestra Particion
int Partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for(int j = low; j <= high; j++) {
        if(arr[j]<pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
  swap(arr[i+1],arr[high]);
  return (i+1);
}

// Definimos nuestro algoritmo QuickSort       
void QuickSort(vector<int>& arr, int low, int high) {
    if(low < high) {
        int pi = Partition(arr, low, high);
        QuickSort(arr,low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}  

// Definimos nuestra funcion en la cual mide el tiempo en microsegundos
chrono::microseconds MedirTiempo(vector<int>& arr) {
    typedef chrono::high_resolution_clock clock;
    auto inicio = clock::now();
    QuickSort(arr, 0, arr.size() - 1);
    auto fin = clock::now();
    auto duracion = chrono::duration_cast<chrono::microseconds>(fin - inicio);
    return duracion;
}

// Definimos nuestra funcion para imprimir un vector
void PrintArray(const vector<int>& arr,const int longitud) {
    for (int i = 0; i < longitud; i++) {
        cout <<arr[i] << " ";
    }
}

// Definimos nuestra funcion para imprimir un vector de vectores
void PrintArrayContenedor(const vector<vector<int>>& arr,const int longitud) {
    for (int i = 0; i < longitud; ++i) {
        cout << i + 1 << ": ";
        PrintArray(arr[i], arr[i].size());
        cout<<endl;
    }
}

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

// Funcion principal de ejecucion
int main() {
    // Creamos nuestro numero de casos
    int casos;
    cout<< "Ingrese el numero de casos a tratar: ";
    cin >> casos;
    
    // Generamos nuestro vector de vectores llamado Contenedor2 con el numero de casos establecidos
    vector<vector<int>> Contenedor1 = GenerarYAlmacenarPeoresCasos(casos);
    
    // Generando Datos....
    cout << "Generando datos...." << endl;

    // Abriendo el archivo para escritura
    ofstream myfile("QuickSort.dat");

    // Ordenamos cada caso y medimos el tiempo de ejecución de cada caso y duracion final del progama, escribiendo en el archivo
    typedef chrono::high_resolution_clock clock;
    auto inicio1 = clock::now();
    for (int i = 0; i < casos; i++) {
        auto tiempo = MedirTiempo(Contenedor1[i]);
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

int main() {

}