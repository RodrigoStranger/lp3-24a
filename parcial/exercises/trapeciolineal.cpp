#include <iostream>
#include <memory>
#include <iomanip>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

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


double areatotal1(double limiteinferior, double limitesuperior, int precision) {
    vector<double> areas;
    double areatotalverdadera=0;
    int c=1;
    cout<<fixed<<setprecision(precision); // Establecer precisión de salida
    double tolerancia=pow(10,-precision); // Calcular tolerancia basada en la precisión
    while(true) {  
        double altura=0;
        double sum_areas=0;
        double temp;
        if( (limiteinferior>0 && limiteinferior>limitesuperior) || (limiteinferior>0 && limiteinferior<limitesuperior)|| (limitesuperior>0 && limiteinferior<0)){
            temp=limiteinferior;
        }else if(limiteinferior==0 && limitesuperior>0 || (limitesuperior==0 && limiteinferior<0) ){
            temp=0;
        }
        int c2=1;
        while(c2<=c) {
            altura=(limitesuperior-limiteinferior)/c;
            unique_ptr<Trapecio> trapecio(new Trapecio(altura, y(temp+altura), y(temp)));
            temp=temp+altura;
            sum_areas=sum_areas+trapecio->calculararea();
            c2++;
        }
        areas.push_back(sum_areas);
        if (areas.size()>1 && abs(areas[c-1]-areas[c-2])<tolerancia) {
            areatotalverdadera=areas[c-1];
            return areatotalverdadera;
            break;
        }    
        c++;
    }
} 

void saludarsegunhora() {
    time_t ahora = time(0); 
    tm *horaLocal = localtime(&ahora); 
    int hora = horaLocal->tm_hour;
    if (hora>=6 && hora<12) {
        cout<<"Buenos días, al sistema para hallar la integral definida aproximada con el metodo del trapecio"<<endl;
    } else if (hora>=12 && hora<18) {
        cout<<"Buenas tardes, al sistema para hallar la integral definida aproximada con el metodo del trapecio"<<endl;
    } else { cout<<"Buenas noches, al sistema para hallar la integral definida aproximada con el metodo del trapecio"<<endl;}
}

int main() {
    double limitesuperior = 50;
    double limiteinferior = 0;
    double precision = 5; 
    cout << areatotal1(limiteinferior, limitesuperior, precision);
    return 0;
}