#include <iostream>
#include <cmath>

using namespace std;

// Creamos una funcion, esta posee un f(x):
int y(float x) {
    return 2*pow(x,2)+1; 
}

// Creamos nuestra clase tablero: 
class Trapecio {
// Designamos atributos privados:
private:
    float altura;
    float basemayor;
    float basemenor;
    float area = 0;
public:
// Constructor:
    Trapecio(float _altura, float _basemayor, float _basemenor): 
        altura(_altura), basemayor(_basemayor), basemenor(_basemenor) {}

// Metodo de calcula el area de un trapecio:
    float calculararea() {return area=((basemayor+basemenor)*altura)/2;}
};

int main() {
    
    float intervalomayor;
    float intervalomenor;
    
    cout<<"Digite el intervalo mayor de la funcion: ";
    cin>>intervalomayor;
    cout<<"Digite el intervalo menor de la funcion: ";
    cin>>intervalomenor;
    
    float altura=intervalomayor-intervalomenor;
    float basemenor=y(2);
    float basemayor=y(7);
    
    Trapecio trapecio(altura, basemayor, basemenor);
    float area=trapecio.calculararea();
    cout<<"El area del trapecio calculado en intervalo de "<<intervalomenor<<" a "<<intervalomayor<<" es: "<<area;
    return 0;
}