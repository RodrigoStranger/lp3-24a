#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <cmath>
#include <vector>
#include <atomic>
#include <thread>
#include <memory>
using namespace std;
using namespace chrono;

// Definición de la función y(x)
double y(double x) {
    return 2 * pow(x, 2) + 1;
}

// Definición de la clase Trapecio
class Trapecio {
private:
    double altura;
    double basemayor;
    double basemenor;
public:
    Trapecio(double _altura, double _basemayor, double _basemenor): altura(_altura), basemayor(_basemayor), basemenor(_basemenor) {}

    double calculararea() {return ((basemayor + basemenor) * altura) / 2;}
};

// Función que calcula el área total en paralelo utilizando el método del trapecio
double areatotalparalela(int trapezoids, double lowerLimit, double upperLimit){
    double p = (upperLimit - lowerLimit) / trapezoids;
    atomic<double> totalArea(0.0);
    atomic<int> next(0);
    int numThreads = thread::hardware_concurrency();
    unique_ptr<thread[]> threads(new thread[numThreads]);

    auto worker = [&](){
        while(true) {
            int i = next.fetch_add(1);
            if(i >= trapezoids){
                break;
            }
            double x = lowerLimit + i * p;
            unique_ptr<Trapecio> trapezoid(new Trapecio(p, y(x + p), y(x)));
            double area = trapezoid->calculararea();
            double currentTotal = totalArea.load();
            while(!totalArea.compare_exchange_weak(currentTotal, currentTotal + area)) {}
        }
    };

    for (int i = 0; i < numThreads; i++){
        threads[i] = thread(worker);
    }

    for(int i = 0; i < numThreads; i++){
        threads[i].join();
    }

    return totalArea;
}


// Función para medir tiempos de ejecución para diferentes cantidades de trapecios
void medirTiempos(double limiteinferior, double limitesuperior) {
    // Definir la cantidad máxima de trapecios a probar
    int maxTrapecios = 100000;

    // Abriendo un archivo para escribir los resultados
    ofstream myfile;
    myfile.open("TrapecioParalelo.dat");

    // Iterar sobre diferentes cantidades de trapecios y medir el tiempo
    for (int trapecios = 1; trapecios <= maxTrapecios; trapecios++) {
        auto start_time = high_resolution_clock::now();

        double area = areatotalparalela(trapecios, limiteinferior, limitesuperior);

        auto end_time = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(end_time - start_time);

        // Escribir en el archivo
        myfile << trapecios << "\t" << duration.count() << endl;
    }
    
    // Cerrar el archivo
    myfile.close();
}


int main() {
    double limiteinferior, limitesuperior;
    cout << "Ingrese el límite inferior: ";
    cin >> limiteinferior;
    cout << "Ingrese el límite superior: ";
    cin >> limitesuperior;

    int maxTrapecios = 1000000; // Definir la cantidad máxima de trapecios a probar
    medirTiempos(limiteinferior,limitesuperior);
    
    cout << "Area total calculada: " << areatotalparalela(maxTrapecios, limiteinferior, limitesuperior) << endl;

    return 0;
}