#include <iostream> // Incluye la librería de entrada y salida estándar
#include <iomanip> // Incluye la librería para manipulación de entrada/salida
#include <cmath> // Incluye la librería matemática
#include <vector> // Incluye la librería de vectores
#include <fstream> // Incluye la librería para manejo de archivos
#include <ctime> // Incluye la librería para funciones de tiempo
#include <chrono> // Incluye la librería para medición de tiempo
#include <memory> // Incluye la librería para manejo de punteros inteligentes

using namespace std; // Utiliza el espacio de nombres estándar
using namespace chrono; // Utiliza el espacio de nombres para funciones de tiempo

int contadordetrapecios = 1; // Contador global para el número de trapecios
string n_archivo = "TrapecioSecuencial.dat"; // Nombre del archivo de salida

// Definición de la clase Trapecio
class Trapecio {
private:
    double altura; // Altura del trapecio
    double basemayor; // Base mayor del trapecio
    double basemenor; // Base menor del trapecio
public:
    // Constructor que inicializa las dimensiones del trapecio
    Trapecio(double _altura, double _basemayor, double _basemenor): altura(_altura), basemayor(_basemayor), basemenor(_basemenor) {}

    // Método que calcula el área del trapecio
    double calculararea() {
        return ((basemayor + basemenor) * altura) / 2; // Fórmula para el área del trapecio
    }
};

// Función que define la ecuación a integrar
double y(double x) {
    return 2 * pow(x, 2) + 1; // Retorna el valor de la función en x
}

// Función para generar un archivo con los tiempos y áreas calculadas
void generararchivo(vector<double> tiempos, vector<double> areas) {
    ofstream myfile(n_archivo); // Abre el archivo para escribir
    int sizet = tiempos.size(); // Obtiene el tamaño del vector de tiempos
    for(int i = 0; i < sizet; i++) { // Itera sobre los elementos del vector
        cout << "Con " << i + 1 << " trapecios, el área calculada es: " << areas[i] << endl; // Imprime el área calculada
        if(i != sizet - 1) {
            myfile << i + 1 << "\t" << tiempos[i] << endl; // Escribe el número de trapecios y el tiempo en el archivo
        } else {
            myfile << i + 1 << "\t" << tiempos[i]; // Última línea sin salto de línea
        }
    }
    myfile.close(); // Cierra el archivo
    cout << endl;
}

// Función para calcular el área usando n trapecios
double calculartrapecio_n(double contadordetrapecios, double altura, double &temp, double sum_areas, double limiteinferior, double limitesuperior) {
    for (int i = 0; i < contadordetrapecios; i++) { // Itera sobre el número de trapecios
        unique_ptr<Trapecio> trapecio(new Trapecio(altura, y(temp + altura), y(temp))); // Crea un nuevo objeto Trapecio
        double area_actual = trapecio->calculararea(); // Calcula el área del trapecio actual
        sum_areas = sum_areas + area_actual; // Suma el área actual al total
        temp = temp + altura; // Incrementa el valor de temp
    }
    return sum_areas; // Retorna la suma de las áreas
}

// Función para agregar datos a los vectores de tiempos y áreas
void pusheardatos(vector<double>& tiempos, double tiempo, vector<double>& areas, double sum_areas) {
    tiempos.push_back(tiempo); // Agrega el tiempo al vector de tiempos
    areas.push_back(sum_areas); // Agrega el área al vector de áreas
}

// Función para calcular el área total bajo la curva
void areatotal(double limiteinferior, double limitesuperior) {
    vector<double> areas; // Vector para almacenar las áreas calculadas
    vector<double> tiempos; // Vector para almacenar los tiempos de cálculo
    double tolerancia = pow(10, -6); // Tolerancia para la comparación de áreas
    while(true) { // Bucle infinito hasta que se cumpla la condición de parada
        double altura = 0; // Inicializa la altura
        double sum_areas = 0; // Inicializa la suma de áreas
        double temp = limiteinferior; // Inicializa temp al límite inferior
        altura = (limitesuperior - limiteinferior) / contadordetrapecios; // Calcula la altura de cada trapecio

        auto start = chrono::steady_clock::now(); // Marca el inicio del tiempo
        sum_areas = calculartrapecio_n(contadordetrapecios, altura, temp, sum_areas, limiteinferior, limitesuperior); // Calcula la suma de las áreas
        auto end = chrono::steady_clock::now(); // Marca el fin del tiempo
        
        auto duracion_ns = duration_cast<nanoseconds>(end - start).count(); // Calcula la duración en nanosegundos
        pusheardatos(tiempos, duracion_ns, areas, sum_areas); // Agrega los datos a los vectores de tiempos y áreas
        
        if(areas.size() > 1 && abs(areas[contadordetrapecios - 1] - areas[contadordetrapecios - 2]) < tolerancia) { // Verifica la condición de tolerancia
            generararchivo(tiempos, areas); // Genera el archivo con los datos
            cout << "El área total calculada entre los intervalos " << limiteinferior << " a " << limitesuperior << " es aproximadamente: " << areas[contadordetrapecios - 1] << " unidades cuadradas" << endl; // Imprime el resultado final
            cout << "Trapecios máximos usados: " << contadordetrapecios << " trapecios" << endl; // Imprime el número de trapecios usados
            cout << "Decimales trabajados: " << 6 << endl; // Imprime la precisión en decimales
            cout << "Tolerancia usada: " << tolerancia << endl; // Imprime la tolerancia usada
            cout << endl;
            cout << "Archivo " << n_archivo << " creado" << endl; // Informa que el archivo fue creado
            break; // Rompe el bucle
        }
        
        contadordetrapecios++; // Incrementa el contador de trapecios
    }
}

// Función para mostrar un saludo según la hora del día
void saludarsegunhora() {
    time_t ahora = time(0); // Obtiene el tiempo actual
    tm *horaLocal = localtime(&ahora); // Convierte el tiempo a la hora local
    int hora = horaLocal->tm_hour; // Obtiene la hora actual
    if (hora >= 6 && hora < 12) { 
        cout << "Buenos días, al sistema para hallar la integral definida aproximada con el método del trapecio" << endl; // Saludo de buenos días
    } else if (hora >= 12 && hora < 18) {
        cout << "Buenas tardes, al sistema para hallar la integral definida aproximada con el método del trapecio" << endl; // Saludo de buenas tardes
    } else {
        cout << "Buenas noches, al sistema para hallar la integral definida aproximada con el método del trapecio" << endl; // Saludo de buenas noches
    }
}

// Manipulador de flujo para establecer la precisión a 6 decimales
ostream& precision_six(ostream& os) {
    os << fixed << setprecision(6); // Establece la precisión a 6 decimales
    return os; // Retorna el flujo
}

// Función principal
int main() {
    cout << precision_six; // Aplica el manipulador de flujo para precisión
    saludarsegunhora(); // Llama a la función para mostrar el saludo
    while(true) { // Bucle infinito hasta que se cumpla la condición de salida
        double limitesuperior; // Variable para el límite superior
        double limiteinferior; // Variable para el límite inferior
        cout << "Digite el límite inferior: ";
        cin >> limiteinferior; // Lee el límite inferior
        cout << "Digite el límite superior: ";
        cin >> limitesuperior; // Lee el límite superior
        cout << endl;
        if(limitesuperior == limiteinferior) { // Verifica si los límites son iguales
            cout << "El área total calculada entre los intervalos " << limiteinferior << " a " << limitesuperior << " es aproximadamente: " << 0 << " unidades cuadradas" << endl; // Imprime que el área es cero
            break; // Rompe el bucle
        }
        if(limitesuperior > limiteinferior) { // Verifica si el límite superior es mayor que el inferior
            cout << "Calculando....." << endl; // Imprime mensaje de cálculo
            areatotal(limiteinferior, limitesuperior); // Llama a la función para calcular el área total
            cout << endl;
            break; // Rompe el bucle
        } else {
            cout << "Valores incorrectos o no lógicos." << endl; // Imprime mensaje de error
            cout << "El límite superior debe ser mayor que el límite inferior." << endl; // Indica el error en los valores
            cout << endl;
            cout << "Ingrese de nuevo los parámetros correctos:" << endl; // Pide ingresar nuevamente los valores
        }
    }
    return 0; // Retorna 0 indicando que el programa terminó correctamente
}