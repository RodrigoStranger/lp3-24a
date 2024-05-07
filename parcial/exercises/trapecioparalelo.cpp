#include <iostream>      // Biblioteca estandar de entrada y salida en C++, para entrada/salida basica.
#include <memory>       // Para la gestion de memoria dinamica y la utilizacion de punteros inteligentes.
#include <iomanip>     // Proporciona facilidades para la manipulacion de formatos de entrada/salida.
#include <cmath>      // Contiene funciones matematicas comunes, como sqrt(), sin(), cos(), etc.
#include <vector>    // Ofrece una clase de contenedor de secuencia dinamica, similar a los arrays, pero de tamaño dinamico.
#include <fstream>  // Proporciona las clases necesarias para realizar operaciones de entrada/salida en archivos.
#include <ctime>   // Utilizado para trabajar con funciones y estructuras relacionadas con el tiempo y la fecha.
#include <chrono> // Biblioteca para medir el tiempo y realizar calculos temporales de alta precision.


using namespace std;
using namespace chrono;

// Inicializamos nuestra variable globlal contador de trapecios, esta nos sirve para poder saber cuantos trapecios hemos necesitado paa realizar el calculo
int contadordetrapecios=1;

// Inicializamos nuestra variable global areatotalverdadera, esta nos sirve para retornar el area verdadera aproximada entre la funcion y los limites inferior y superior
double areatotalverdadera=0;

// Definimos nuestra clase trapecio, en POO es muy importante, ya que podemos tratar a este trapecio como objeto, ademas es facil de poder entenderlo
class Trapecio {
// Definimos los atributos privados para el trapecio : altura, base menor y base mayor
private:
    double altura;
    double basemayor;
    double basemenor;
// Creamos su constructor publico, Trapecio, ademas agregamos una funcion llamada calculararea, esta tiene el proposito de calcular el area de un trapecio
public:
    Trapecio(double _altura, double _basemayor, double _basemenor): altura(_altura), basemayor(_basemayor), basemenor(_basemenor) {}

// calculararea recibira basemayor, basemenor y altura, y hara el calculo matematico respectivo
    double calculararea() {return ((basemayor+basemenor)*altura)/2;}
};

// Funcion f(x)
double y(double x) {return 2*pow(x,2)+1;}

// Funcion generar archivo: posee parametros talez como: tiempos, areas
void generararchivo(vector<double> tiempos, vector<double> areas){
    ofstream myfile("TrapecioParalelo.dat"); // usando <fstream> creamos un archivo.dat 
    int sizet= tiempos.size(); // del vector tiempos, sacamos su tamaño usando la funcion .size()
    for(int i=0;i<sizet;i++) { // inicializamos un for que va desde 0 hasta el tamaño del vector tiempos, esto hace recorrer cada tiempo ya calculado
        cout<<"Con "<<i+1<<" trapecios, el area calculada es: "<<areas[i]<<endl; // imprimimos el numero de trapecio y su area calculada
        if(i!=sizet-1) { // si i es diferente del tamaño del vector entonces seteamos el .dat
            myfile<<i+1<<"\t"<<tiempos[i]<<endl;
        } else {
            myfile<<i+1<<"\t"<<tiempos[i]; // caso contrario  seteamos el ultimo elemento sin añadir un salto de linea
        }
    }
    myfile.close(); // cerramos el archivo
    cout<<endl; // agregamos un salto de linea
}


int main () {

    return 0;
}