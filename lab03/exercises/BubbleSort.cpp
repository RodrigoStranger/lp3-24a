// Commit 1: 3a59951
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

// Commit 1: 3a59951
// Definimos el Ordenamiento Burbuja
void BubbleSort(vector<int>& arr, int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			if(arr[i] > arr[j]) {
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}	
}	  

// Commit 2: b25af76
// Definimos nuestra funcion en la cual mide el tiempo en microsegundos
chrono::microseconds MedirTiempo(vector<int>& arr) {
    typedef chrono::high_resolution_clock clock;
    auto inicio = clock::now();
    BubbleSort(arr, arr.size());
    auto fin = clock::now();
    auto duracion = chrono::duration_cast<chrono::microseconds>(fin - inicio);
    return duracion;
}

// Commit 3: e5b362f
// Definimos nuestra funcion para imprimir un vector
void PrintArray(const vector<int>& arr,const int longitud) {
    for (int i = 0; i < longitud; i++) {
        cout <<arr[i] << " ";
    }
}

// Commit 3: e5b362f
// Definimos nuestra funcion para imprimir un vector de vectores
void PrintArrayContenedor(const vector<vector<int>>& arr,const int longitud) {
    for (int i = 0; i < longitud; ++i) {
        cout << i + 1 << ": ";
        PrintArray(arr[i], arr[i].size());
        cout<<endl;
    }
}

// Commit 4: 52df16a
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

// Commit 5: 973f491
// Funcion principal
int main() {
    // Creamos nuestro numero de casos
    int casos;
    cout<< "Ingrese el numero de casos a tratar: ";
    cin >> casos;
    
    // Generamos nuestro vector de vectores llamado Contenedor con el numero de casos establecidos
    vector<vector<int>> Contenedor = GenerarYAlmacenarPeoresCasos(casos);
    
    // Generando Datos....
    cout << "Generando datos...." << endl;

    // Abriendo el archivo para escritura
    ofstream myfile("BubbleSort.dat");

    // Ordenamos cada caso y medimos el tiempo de ejecución de cada caso y duracion final del progama, escribiendo en el archivo
    typedef chrono::high_resolution_clock clock;
    auto inicio1 = clock::now();
    for (int i = 0; i < casos; i++) {
        auto tiempo = MedirTiempo(Contenedor[i]);
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