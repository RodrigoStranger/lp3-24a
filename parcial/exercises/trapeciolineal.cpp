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

// limiteinferior==0 && limitesuperior > 0  || limiteinferior<0 && limitesuperior==0
double areatotal1(double limiteinferior, double limitesuperior, int precision) {
    vector<double> areas;
    double areatotalverdadera=0;
    int c=1;
    cout<<fixed<<setprecision(precision); // Establecer precisión de salida
    double tolerancia=pow(10,-precision); // Calcular tolerancia basada en la precisión
    while(true) {  
        double altura=0;
        double sum_areas=0;
        double temp=0;
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

// limiteinferior>0 && limitesuperior > 0 || limiteinferior<0 && limitesuperior<0
/* double areatotal2(double limiteinferior, double  limitesuperior){
    bool llave =true;
    vector<double> areas;
    double areatotalverdadera = 0;
    int c = 1;
    while(llave) {
        for(int i=0;i<c;i++){
        /// implementacion
        double area =1;
        areas.push_back(area);
        if(c>1 && areas[c]==areas[c-1]){
            areatotalverdadera =  areas[i];
            llave = false;
        } 
        }
    c++;
    }
    return areatotalverdadera;
} */

int main() {
    double limitesuperior = 50;
    double limiteinferior = 0;
    double precision = 5; 
    cout << areatotal1(limiteinferior, limitesuperior, precision);
    return 0;
}