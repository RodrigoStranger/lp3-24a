#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

double y(double x) {
    return 2*pow(x,2)+1;
}

class Trapecio {
    private:
        double altura;
        double basemayor;
        double basemenor;
        double area = 0;
    public:
        Trapecio(double _altura, double _basemayor, double _basemenor): 
            altura(_altura), basemayor(_basemayor), basemenor(_basemenor) {}
        ~Trapecio() {}

        double calculararea() {return area=((basemayor+basemenor)*altura)/2;}
};

// limiteinferior==0 && limitesuperior > 0  || limiteinferior<0 && limitesuperior==0
double areatotal1(double &limiteinferior, double  &limitesuperior){
    bool llave =true;
    vector<double> areas;
    double areatotalverdadera = 0;
    int c = 1;
    while(llave) {  
        double altura = 0;
        double sum_areas = 0;
        double temp = 0;
        altura = (limitesuperior-limiteinferior)/c;
        for(int i=0;i<c;i++){
            Trapecio *trapecio = new Trapecio(altura, y(temp+altura), y(temp));
            temp = temp + altura;
            sum_areas = sum_areas + trapecio->calculararea();
            delete trapecio;
        }
        areas.push_back(sum_areas);
        if(areas[c]==areas[c-1]){
            areatotalverdadera =  areas[c];
            llave = false;
        }    
    c++;
    }
    return areatotalverdadera;
}

// limiteinferior>0 && limitesuperior > 0 || limiteinferior<0 && limitesuperior<0
double areatotal2(double &limiteinferior, double  &limitesuperior){
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
}

int main() {
    
    return 0;
}