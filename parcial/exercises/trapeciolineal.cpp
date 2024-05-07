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
    ofstream myfile("TrapecioSecuencial.dat"); // usando <fstream> creamos un archivo.dat 
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

// Funcion areatotal: posee parametros talez como limiteinferior, limitesuperior, y el nivel de presicion del calculo general
void areatotal(double limiteinferior, double limitesuperior, int precision) {
    vector<double> areas; // inicalizamos un vector areas, esta nos servira para almacenar todas las areas calculadas con n= 1,2,3,4,5,6... etc. trapecios
    vector<double> tiempos; // inicializamos nuestro vector tiempos, esta nos servira 
    cout<<fixed<<setprecision(precision); // esto indica cuántos dígitos se deben imprimir después del punto decimal.
    double tolerancia=pow(10,-precision);  // calcular la tolerancia a partir de la precisión establecida
    while(true) {  
        double altura=0; // inicializamos nuestra altura en 0
        double sum_areas=0; // inicializamos nuestra suma de areas, esta nos sirve para almacenar la suma total de areas de cada trapecio pequeño calculado
        double temp=limiteinferior; // inicializamos temp que sera igualado a nuestro limite inferior
        double tiempo=0; // inicializamos tiempo, esto nos sirve para calcular el tiempo que despues sera almacenado en nuestro vector tiempos
        altura=(limitesuperior-limiteinferior)/contadordetrapecios; // la altura sera calculada con la resta de los limites dividido entre el actual numero de trapcios, esto nos ayuda a saber la altura total de cada pequeño trapecio
        auto start = chrono::steady_clock::now(); // inicalizamos la toma de tiempo (start) osea inicio
        for(int i=0;i<contadordetrapecios;i++) { // inicalizamos nuestro for, que va desde i=0 hasta el valor actual del contador de trapecios
            unique_ptr<Trapecio> trapecio(new Trapecio(altura, y(temp+altura), y(temp))); // creamos un puntero inteligente trapecio, esto nos ayuda a que despues este sea utilizado, libere la memoria automaticmente
            temp=temp+altura; // se hace un nuevo calculo del temporal para usarlo en el siguiente trapecio
            sum_areas=sum_areas+trapecio->calculararea(); // usamos la funcion calculararea, para hallar el area del trapecio actual de la iteracion y lo sumamos al sum_areas
        }
        auto end = chrono::steady_clock::now(); // acabamos la toma de tiempo (end) osea final
        auto duracion_ns = duration_cast<nanoseconds>(end - start); // restamos el tiempo final - el tiempo inicial (en nanosegundos)
        tiempo = duracion_ns.count(); // count para devolver el numero de periodos
        tiempos.push_back(tiempo); // agregamos el tiempo calculado al vector de tiempos
        areas.push_back(sum_areas); // agregamos el area calculada al vector de areas
        if (areas.size()>1 && abs(areas[contadordetrapecios-1]-areas[contadordetrapecios-2])<tolerancia) { // si el tamaño del vector areas es mayor que 1 y el valor absoluto de la resta entre el actual calculo de area menos el anterior es menor que la tolerancia entonces se termina el calculo
            areatotalverdadera=areas[contadordetrapecios-1]; // seteamos el calculo actual a areatotalverdadera
            generararchivo(tiempos, areas); // llamamos a la funcion generar archivo
            // Imprimimos los valores para la consola
            cout<<"El area total calculada entre los intervalos "<<limiteinferior<<" a "<<limitesuperior<<" es: "<<areatotalverdadera<<" unidades cuadradas"<<endl; // area total calculada
            cout<<"Precision usada: "<<precision<<endl; // precision usada
            cout<<"Trapecios maximos usados: "<<contadordetrapecios<<" trapecios"<<endl; // trapecios usados
            break; // rompemos el bucle
        } else {contadordetrapecios++;} // en caso el calculo sea mayor que la tolerancia, el contador se incrementa en 1 pasando denuevo por el bucle
    }
} 

// Funcion para saludar segun la hora ejecutada por el usuario
void saludarsegunhora() {
    time_t ahora=time(0); // usamos la libreria <ctime> 
    tm *horaLocal=localtime(&ahora); // convertimos el tiempo actual en una estructura tm que representa la hora local, localtime() convierte la representación de tiempo en el sistema local
    int hora=horaLocal->tm_hour; // extraer la hora del objeto tm obtenido anteriormente
    // Verificamos en qué rango horario está la hora actual y mostrar un mensaje correspondiente
    if (hora>=6 && hora<12) { 
        cout<<"Buenos días, al sistema para hallar la integral definida aproximada con el metodo del trapecio"<<endl;
    } else if (hora>=12 && hora<18) {
        cout<<"Buenas tardes, al sistema para hallar la integral definida aproximada con el metodo del trapecio"<<endl;
    } else { cout<<"Buenas noches, al sistema para hallar la integral definida aproximada con el metodo del trapecio"<<endl;}
}

int main() {
    saludarsegunhora(); // saludamos segun la hora en que se ejecuta el programa
    while (true) {
        double limitesuperior; // inicializamos limitesuperior
        double limiteinferior; // inicializamos limiteinferior
        double precision; // inicializamos presicion
        cout<<"Digite el limite inferior: ";
        cin>>limiteinferior; // leemos limiteinferior
        cout<<"Digite el limite superior: ";
        cin>>limitesuperior; // leemos limitesuperior
        cout<<endl;
        // Hacemos una comparacion para determinar que los datos esten correctamente establecidos
        if (limitesuperior>limiteinferior) {
            while(true) {
                cout<<"Digite el nivel de precision"<<endl;
                cout<<"Entre mas alto sea el nivel de precision, se incrementara el numero de trapecios a calcular y"<<endl;
                cout<<"por ende el tiempo"<<endl;
                cout<<"Nivel de precision: ";
                cin>>precision; // leemos la presicion 
                // Determinamos que la presicion este correctamente establecida
                if (precision>0) {
                    cout<<endl;
                    cout<<"Calculando....."<<endl;
                    areatotal(limiteinferior, limitesuperior, precision);
                    cout<<endl;
                    break; // caso en que la presicion este correctamente establecida, se rompe el bucle y se inician los calculos
                } else {
                    cout<<"Precision no valida, por favor ingrese un valor positivo."<<endl; // caso no este correcta se debe de volver a establecer o leer
                }
            }
        } else {
            cout<<"Valores incorrectos o no lógicos."<<endl;
            cout<<"El limite superior debe ser mayor que el limite inferior."<<endl;
            cout<<endl;
            cout<<"Ingrese denuevo los parametros correctos:"<<endl; // caso los limites no esten correctamente establecidos, se deben de volver a leer
        }
        break; // caso todo este correcto, se inicia los calculos y se termina el programa
    }
    return 0; 
}