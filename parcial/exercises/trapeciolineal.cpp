#include <iostream> 
#include <iomanip> 
#include <cmath> 
#include <vector> 
#include <fstream> 
#include <ctime> 
#include <chrono> 
#include <memory> 

using namespace std; 
using namespace chrono; 

string n_archivo_2 = "TrapecioSecuencial.csv";
int tolerancia_general = 5;
int precision_general = 5;
int contadordetrapecios = 1; 
string n_archivo = "TrapecioSecuencial.dat"; 

class Trapecio {
private:
    double altura; 
    double basemayor; 
    double basemenor; 
public:
    Trapecio(double _altura, double _basemayor, double _basemenor): 
        altura(_altura), basemayor(_basemayor), basemenor(_basemenor) {}

    double calculararea() {return ((basemayor + basemenor) * altura) / 2; }
};

double y(double x) { return 7 * sqrt(x);}

/*
void generararchivo(vector<double> tiempos, vector<double> areas) {
    ofstream myfile(n_archivo); 
    int sizet = tiempos.size(); 
    for(int i = 0; i < sizet; i++) { 
        cout << "Con " << i + 1 << " trapecios, el area calculada es: " << areas[i] << endl; 
        if(i != sizet - 1) {
            myfile << i + 1 << "\t" << tiempos[i] << endl; 
        } else {
            myfile << i + 1 << "\t" << tiempos[i]; 
        }
    }
    myfile.close(); 
    cout << endl;
}
*/

// En funcion es dificil escribir archivos
/*
double calculartrapecio_n(double contadordetrapecios, double altura, double temp, double sum_areas) {
    cout << static_cast<int>(contadordetrapecios);
    for(int i = 0; i < contadordetrapecios; i++) { 
        unique_ptr<Trapecio> trapecio(new Trapecio(altura, y(temp + altura), y(temp))); 
        double area_actual = trapecio->calculararea();
        cout << " " << area_actual << " ";
        sum_areas = sum_areas + area_actual; 
        temp = temp + altura; 
    }
    cout << sum_areas<<endl;
    return sum_areas; 
}
*/

void pusheardatos(vector<double>& tiempos, double tiempo, vector<double>& areas, double sum_areas) {
    tiempos.push_back(tiempo); 
    areas.push_back(sum_areas); 
}

void areatotal(double limiteinferior, double limitesuperior) {
    vector<double> areas; 
    vector<double> tiempos;
    double tolerancia = pow(10, -tolerancia_general); 
    ofstream myfile2(n_archivo_2);
    while(true) {
        double altura = 0; 
        double areatotal_n_trapecio = 0;
        double area_actual = 0; 
        double temp = limiteinferior; 
        altura = (limitesuperior - limiteinferior) / contadordetrapecios; 

        //auto start = chrono::steady_clock::now(); 
        //areatotal_n_trapecio = calculartrapecio_n(contadordetrapecios, altura, temp, areatotal_n_trapecio); 
        
        myfile2 << static_cast<int>(contadordetrapecios) << ";";
        
        //cout << static_cast<int>(contadordetrapecios);
        for(int i=0; i < contadordetrapecios; i++) {
            unique_ptr<Trapecio> trapecio(new Trapecio(altura, y(temp + altura), y(temp))); 
            area_actual = trapecio -> calculararea();
            myfile2 << area_actual << ";";
            //cout << " " << area_actual << " ";
            areatotal_n_trapecio = areatotal_n_trapecio + area_actual; 
            temp = temp + altura;
        }
        //cout << " " << areatotal_n_trapecio <<endl;
        
        //auto end = chrono::steady_clock::now();
        
        //auto duracion_ns = duration_cast<nanoseconds>(end - start).count(); 
        //pusheardatos(tiempos, duracion_ns, areas, areatotal_n_trapecio); 
        
        areas.push_back(areatotal_n_trapecio);

        if(areas.size() > 1 && abs(areas[contadordetrapecios - 1] - areas[contadordetrapecios - 2]) < tolerancia) { 
            //generararchivo(tiempos, areas); // Genera el archivo con los datos
            cout << endl;
            cout << "El area total calculada entre los intervalos " << limiteinferior << " a " << limitesuperior << " es aproximadamente: " << areas[contadordetrapecios - 1] << " unidades cuadradas" << endl; // Imprime el resultado final
            cout << "Trapecios maximos usados: " << contadordetrapecios << " trapecios" << endl; 
            cout << "Decimales trabajados: " << precision_general << endl; 
            cout << "Tolerancia usada: " << tolerancia << endl; 
            cout << endl;
            //cout << "Archivo " << n_archivo << " creado" << endl;
            myfile2 << areatotal_n_trapecio;
            myfile2.close(); 
            break; 
        }
        myfile2 << areatotal_n_trapecio << endl;
        contadordetrapecios++; 
    }
}

void saludarsegunhora() {
    time_t ahora = time(0); 
    tm *horaLocal = localtime(&ahora); 
    int hora = horaLocal->tm_hour; 
    if (hora >= 6 && hora < 12) { 
        cout << "Buenos dias, al sistema para hallar la integral definida aproximada con el metodo del trapecio" << endl; 
    } else if (hora >= 12 && hora < 18) {
        cout << "Buenas tardes, al sistema para hallar la integral definida aproximada con el metodo del trapecio" << endl; 
    } else {
        cout << "Buenas noches, al sistema para hallar la integral definida aproximada con el metodo del trapecio" << endl; 
    }
}

ostream& precision(ostream& os) {
    os << fixed << setprecision(precision_general); 
    return os; 
}

int main() {
    cout << precision; 
    saludarsegunhora();
    while(true) { 
        double limitesuperior; 
        double limiteinferior; 
        cout << "Digite el limite inferior: ";
        cin >> limiteinferior; 
        cout << "Digite el limite superior: ";
        cin >> limitesuperior; 
        cout << endl;
        if(limitesuperior == limiteinferior) { 
            cout << "El area total calculada entre los intervalos " << limiteinferior << " a " << limitesuperior << " es aproximadamente: " << 0 << " unidades cuadradas" << endl; // Imprime que el área es cero
            break; 
        }
        if(limitesuperior > limiteinferior) { 
            cout << "Calculando....." << endl; 
            areatotal(limiteinferior, limitesuperior); 
            cout << endl;
            break; 
        } else {
            cout << "Valores incorrectos o no logicos." << endl; 
            cout << "El limite superior debe ser mayor que el limite inferior." << endl; 
            cout << endl;
            cout << "Ingrese de nuevo los parametros correctos:" << endl; 
        }
    }
    return 0; 
}