#include <iostream> // Incluye la librería de entrada y salida estándar
#include <iomanip> // Incluye la librería para manipulación de entrada/salida
#include <cmath> // Incluye la librería matemática
#include <vector> // Incluye la librería de vectores
#include <fstream> // Incluye la librería para manejo de archivos
#include <ctime> // Incluye la librería para funciones de tiempo
#include <chrono> // Incluye la librería para medición de tiempo
#include <memory> // Incluye la librería para manejo de punteros inteligentes
#include <thread> // Incluye la librería para manejo de hilos
#include <mutex> // Incluye la librería para manejo de mutex

int n_threads = 2; // Número de hilos a usar

using namespace std; // Utiliza el espacio de nombres estándar
using namespace chrono; // Utiliza el espacio de nombres para funciones de tiempo

mutex mtx; // Define un mutex para proteger secciones críticas
int contadordetrapecios = 1; // Contador global para el número de trapecios
string n_archivo = "TrapecioParalelo.dat"; // Nombre del archivo de salida
int decimales = 6; // Número de decimales a usar

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
    double calculararea() { return ((basemayor + basemenor) * altura) / 2; // Fórmula para el área del trapecio
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
    for (int i = 0; i < sizet; i++) { // Itera sobre los elementos del vector
        cout << "Con " << i + 1 << " trapecios, el area calculada es: " << areas[i] << endl; // Imprime el área calculada
        if (i != sizet - 1) {
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
    thread threads[n_threads]; // Crea un array de hilos
    vector<double> areas; // Vector para almacenar las áreas calculadas
    vector<double> tiempos; // Vector para almacenar los tiempos de cálculo
    double tolerancia = pow(10, -decimales); // Tolerancia para la comparación de áreas

    while (true) { // Bucle infinito hasta que se cumpla la condición de parada
        double sum_areas = 0.0; // Inicializa la suma de áreas
        double intervalo_por_hilo = (limitesuperior - limiteinferior) / n_threads; // Calcula el intervalo que cada hilo procesará
        double sum_areas_hilos[n_threads] = {0.0}; // Array para almacenar las áreas calculadas por cada hilo
        
        // Iniciar cronómetro antes de que los hilos comiencen
        auto start = chrono::steady_clock::now();
        
        // Iniciar hilos
        for (int i = 0; i < n_threads; ++i) {
            double inicio_hilo = limiteinferior + i * intervalo_por_hilo; // Calcula el inicio del intervalo del hilo
            double fin_hilo = inicio_hilo + intervalo_por_hilo; // Calcula el fin del intervalo del hilo
            if (i == n_threads - 1) fin_hilo = limitesuperior; // Ajustar el último hilo
            
            threads[i] = thread([&sum_areas_hilos, i, inicio_hilo, fin_hilo]() { // Lambda para ejecutar en cada hilo
                double sum_areas_local = 0.0; // Inicializa la suma de áreas local
                int contadordetrapecios_local = contadordetrapecios; // Copia local del contador de trapecios
                double altura_local = (fin_hilo - inicio_hilo) / contadordetrapecios_local; // Calcula la altura local de cada trapecio
                for (int j = 0; j < contadordetrapecios_local; ++j) { // Itera sobre el número de trapecios
                    double temp_local = inicio_hilo + j * altura_local; // Calcula el valor temporal local
                    double base_mayor = y(temp_local + altura_local); // Calcula la base mayor
                    double base_menor = y(temp_local); // Calcula la base menor
                    double area_actual = (base_mayor + base_menor) * altura_local / 2.0; // Calcula el área del trapecio actual
                    sum_areas_local += area_actual; // Suma el área local al total local
                }
                // Actualizar la suma total de áreas con mutex
                mtx.lock();
                sum_areas_hilos[i] = sum_areas_local; // Guarda el resultado local en el array compartido
                mtx.unlock();
            });
        }
        
        // Esperar a que todos los hilos terminen
        for (int i = 0; i < n_threads; ++i) {
            threads[i].join();
        }
        
        // Detener el cronómetro después de que todos los hilos hayan terminado
        auto end = chrono::steady_clock::now();
        
        // Calcular la suma total de las áreas de los trapecios
        for (int i = 0; i < n_threads; ++i) {
            sum_areas += sum_areas_hilos[i]; // Suma las áreas calculadas por cada hilo
        }
        
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