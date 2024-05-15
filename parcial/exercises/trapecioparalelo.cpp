#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <fstream>
#include <ctime>
#include <chrono>
#include <memory>
#include <thread>
#include <mutex>

int n_threads=2;

using namespace std;
using namespace chrono;

mutex mtx;
int contadordetrapecios = 1;
string n_archivo = "TrapecioParalelo.dat";
int decimales = 6;

class Trapecio {
private:
    double altura;
    double basemayor;
    double basemenor;
public:
    Trapecio(double _altura, double _basemayor, double _basemenor): altura(_altura), basemayor(_basemayor), basemenor(_basemenor) {}
    double calculararea() {return ((basemayor+basemenor)*altura)/2;}
};

double y(double x) {return 2*pow(x,2)+1;}

void generararchivo(vector<double> tiempos, vector<double> areas){
    ofstream myfile(n_archivo);
    int sizet= tiempos.size();
    for(int i=0;i<sizet;i++) {
        cout<<"Con "<<i+1<<" trapecios, el area calculada es: "<<areas[i]<<endl;
        if(i!=sizet-1) {
            myfile<<i+1<<"\t"<<tiempos[i]<<endl;
        } else {
            myfile<<i+1<<"\t"<<tiempos[i];
        }
    }
    myfile.close();
    cout<<endl;
}

double calculartrapecio_n(double contadordetrapecios, double altura, double &temp, double sum_areas, double limiteinferior, double limitesuperior) {
    for (int i=0;i<contadordetrapecios;i++) {
        unique_ptr<Trapecio>trapecio(new Trapecio(altura,y(temp+altura),y(temp)));
        double area_actual=trapecio->calculararea(); 
        sum_areas=sum_areas+area_actual;
        temp=temp+altura;
    }
    return sum_areas;
}

void pusheardatos(vector<double>& tiempos, double tiempo, vector<double>& areas, double sum_areas) {
    tiempos.push_back(tiempo);
    areas.push_back(sum_areas);
}

void areatotal(double limiteinferior, double limitesuperior) {
    thread threads[n_threads];
    vector<double> areas;
    vector<double> tiempos;
    double tolerancia = pow(10, -decimales);

    while (true) {
        double sum_areas = 0.0;
        double intervalo_por_hilo = (limitesuperior - limiteinferior) / n_threads;
        double sum_areas_hilos[n_threads] = {0.0};
        // Iniciar cronómetro antes de que los hilos comiencen
        auto start = chrono::steady_clock::now();
        // Iniciar hilos
        for (int i = 0; i < n_threads; ++i) {
            double inicio_hilo = limiteinferior + i * intervalo_por_hilo;
            double fin_hilo = inicio_hilo + intervalo_por_hilo;
            if (i == n_threads - 1) fin_hilo = limitesuperior; // Ajustar el último hilo
            threads[i] = thread([&sum_areas_hilos, i, inicio_hilo, fin_hilo]() {
                double sum_areas_local = 0.0;
                int contadordetrapecios_local = contadordetrapecios;
                double altura_local = (fin_hilo - inicio_hilo) / contadordetrapecios_local;
                for (int j = 0; j < contadordetrapecios_local; ++j) {
                    double temp_local = inicio_hilo + j * altura_local;
                    double base_mayor = y(temp_local + altura_local);
                    double base_menor = y(temp_local);
                    double area_actual = (base_mayor + base_menor) * altura_local / 2.0;
                    sum_areas_local += area_actual;
                }
                // Actualizar la suma total de áreas con mutex
                mtx.lock();
                sum_areas_hilos[i] = sum_areas_local;
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
            sum_areas += sum_areas_hilos[i];
        }
        auto duracion_ns = duration_cast<nanoseconds>(end - start).count();
        pusheardatos(tiempos, duracion_ns, areas, sum_areas);
        if (areas.size() > 1 && abs(areas[areas.size() - 1] - areas[areas.size() - 2]) < tolerancia) {
            generararchivo(tiempos, areas);
            cout << "El area total calculada entre los intervalos " << limiteinferior << " a " << limitesuperior << " es aproximadamente: " << areas[areas.size() - 1] << " unidades cuadradas" << endl;
            cout << "Trapecios maximos usados: " << contadordetrapecios << " trapecios" << endl;
            cout << "Decimales trabajados: " << decimales << endl;
            cout << "Tolerancia usada: " << tolerancia << endl;
            cout << endl;
            cout << "Archivo " << n_archivo << " creado" << endl;
            break;
        }
        contadordetrapecios++;
    }
}


void saludarsegunhora() {
    time_t ahora=time(0);
    tm *horaLocal=localtime(&ahora);
    int hora=horaLocal->tm_hour;
    if (hora>=6 && hora<12) { 
        cout<<"Buenos días, al sistema para hallar la integral definida aproximada con el método del trapecio"<<endl;
    } else if (hora>=12 && hora<18) {
        cout<<"Buenas tardes, al sistema para hallar la integral definida aproximada con el método del trapecio"<<endl;
    } else {
        cout<<"Buenas noches, al sistema para hallar la integral definida aproximada con el método del trapecio"<<endl;
    }
}

ostream& precision_six(ostream& os) {
    os<<fixed<<setprecision(6);
    return os;
}

int main() {
    cout<<precision_six;
    saludarsegunhora();
    while(true) {
        double limitesuperior;
        double limiteinferior;
        cout<<"Digite el limite inferior: ";
        cin>>limiteinferior;
        cout<<"Digite el limite superior: ";
        cin>>limitesuperior;
        cout<<endl;
        if(limitesuperior==limiteinferior) {
            cout<<"El area total calculada entre los intervalos "<<limiteinferior<<" a "<<limitesuperior<<" es aproximadamente: "<<0<<" unidades cuadradas"<<endl;
            break;
        }
        if(limitesuperior > limiteinferior) {
            cout<<"Calculando....."<<endl;
            areatotal(limiteinferior, limitesuperior);
            cout<<endl;
            break;
        } else {
            cout<<"Valores incorrectos o no lógicos."<<endl;
            cout<<"El limite superior debe ser mayor que el limite inferior."<<endl;
            cout<<endl;
            cout<<"Ingrese denuevo los parametros correctos:"<<endl;
        }
    }
    return 0; 
}