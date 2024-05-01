#include <iostream>
#include <memory>
#include <iomanip>
#include <cmath>
#include <vector>
#include <fstream>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

class Trapecio {
private:
    double altura;
    double basemayor;
    double basemenor;
public:
    Trapecio(double _altura, double _basemayor, double _basemenor): altura(_altura), basemayor(_basemayor), basemenor(_basemenor) {}
    double calculararea() {return ((basemayor+basemenor)*altura)/2;}
};

double y(double x) { return 2*pow(x,2)+1;}


void areatotal(double limiteinferior, double limitesuperior, int precision) {
    vector<double> areas;
    vector<double> tiempos;
    double areatotalverdadera=0;
    int c=1;
    cout<<fixed<<setprecision(precision); // Establecer precisión de salida
    double tolerancia=pow(10,-precision); // Calcular tolerancia basada en la precisión
    while(true) {  
        double altura=0;
        double sum_areas=0;
        double temp;
        double tiempo=0;
        if((limiteinferior>0 && limitesuperior>limiteinferior) || (limitesuperior<0 && limitesuperior>limiteinferior) || (limiteinferior<0 && limitesuperior>0)){
            temp=limiteinferior;
        }else if((limiteinferior==0 && limitesuperior>limiteinferior) || (limitesuperior==0 && limiteinferior<limitesuperior)){
            temp=0;
        }
        altura=(limitesuperior-limiteinferior)/c;
        auto start = chrono::steady_clock::now();
        for(int i=0;i<c;i++) {
            unique_ptr<Trapecio> trapecio(new Trapecio(altura, y(temp+altura), y(temp)));
            temp=temp+altura;
            sum_areas=sum_areas+trapecio->calculararea();
        }
        auto end = chrono::steady_clock::now();
        auto duracion_ns = duration_cast<nanoseconds>(end - start);
        tiempo = duracion_ns.count(); 
        tiempos.push_back(tiempo);
        areas.push_back(sum_areas);
        if (areas.size()>1 && abs(areas[c-1]-areas[c-2])<tolerancia) {
            areatotalverdadera=areas[c-1];
            ofstream myfile("Trapeciolineal2.dat");
            int sizet= tiempos.size();
            for(int i=0;i<sizet;i++) {
                cout<<"Con "<<i+1<<" trapecios, el area calculada es: "<<areas[i]<<endl;
                if (i!=sizet-1) { // Evitar imprimir una línea vacía después del ultimo elemento
                    myfile<<i+1<<"\t"<<tiempos[i]<<endl;
                } else {
                    myfile<<i+1<<"\t"<<tiempos[i]; // No agregar un salto de línea despues del último elemento
                }
            }
            myfile.close();
            cout<<endl;
            cout<<"El area total calculada entre los intervalos "<<limiteinferior<<" a "<<limitesuperior<<" es: "<<areatotalverdadera<<" unidades cuadradas"<<endl;
            cout<<"Precision usada: "<<precision<<endl;
            cout<<"Trapecios maximos usados: "<<c<<" trapecios"<<endl;
            break;
        }    
        c++;
    }
} 

void saludarsegunhora() {
    time_t ahora=time(0); 
    tm *horaLocal=localtime(&ahora); 
    int hora=horaLocal->tm_hour;
    if (hora>=6 && hora<12) {
        cout<<"Buenos días, al sistema para hallar la integral definida aproximada con el metodo del trapecio"<<endl;
    } else if (hora>=12 && hora<18) {
        cout<<"Buenas tardes, al sistema para hallar la integral definida aproximada con el metodo del trapecio"<<endl;
    } else { cout<<"Buenas noches, al sistema para hallar la integral definida aproximada con el metodo del trapecio"<<endl;}
}

int main() {
    saludarsegunhora();
    while (true) {
        double limitesuperior;
        double limiteinferior;
        double precision;
        cout<<"Digite el limite inferior: ";
        cin>>limiteinferior;
        cout<<"Digite el limite superior: ";
        cin>>limitesuperior;
        cout<<endl;
        if (limitesuperior>limiteinferior) {
            while(true) {
                cout<<"Digite el nivel de precision"<<endl;
                cout<<"Entre mas alto sea el nivel de precision, se incrementara el numero de trapecios a calcular y"<<endl;
                cout<<"por ende el tiempo"<<endl;
                cout<<"Nivel de precision: ";
                cin>>precision;
                if (precision>0) {
                    cout<<endl;
                    cout<<"Calculando....."<<endl;
                    areatotal(limiteinferior, limitesuperior, precision);
                    cout<<endl;
                    break;
                } else {
                    cout<<"Precision no valida, por favor ingrese un valor positivo."<<endl;
                }
            }
        } else {
            cout<<"Valores incorrectos o no lógicos."<<endl;
            cout<<"El limite superior debe ser mayor que el limite inferior."<<endl;
            cout<<endl;
            cout<<"Ingrese denuevo los parametros correctos:"<<endl;
        }
        break;
    }
    return 0;
}