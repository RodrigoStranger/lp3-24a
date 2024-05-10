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

