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

double calcular_area_total(double n, double largo){
    double area_total = 0;
    Trapecio *trapecio;
    double temp = 0;
    double aumentar = largo/n;
    for(int i=0;i<n;i++){
        trapecio = new Trapecio((largo/n), y(temp+aumentar), y(temp));
        temp = temp + aumentar;
        area_total = area_total + trapecio->calculararea();
        cout<<area_total<<endl; 
        delete trapecio;
    }
    return area_total;
}
double area_total_funcion(double &limiteinferior, double  &limitesuperior) {
    bool llave =true;
    vector<double> areas;
    double areatotalverdadera = 0;
    while(llave) {
        if(limiteinferior==0 && limitesuperior > 0) {
            int c = 1;
            for(int i=0;i<c;i++){
                
                double area =1;
                areas.push_back(area);
                if(c>1 && areas[c]==areas[c-1]){
                    double areatotalverdadera =  areas[i];
                    llave = false;
                } 
            }
            c++;
        } else if(limiteinferior>0 && limitesuperior > 0) {
            int c = 1;
            for(int i=0;i<c;i++){
                
                double area =1;
                areas.push_back(area);
                if(c>1 && areas[c]==areas[c-1]){
                    areatotalverdadera =  areas[i];
                    llave = false;
                } 
            }
            c++;
        } else if(limiteinferior<0 && limitesuperior==0){
            int c = 1;
            for(int i=0;i<c;i++){
                
                double area =1;
                areas.push_back(area);
                if(c>1 && areas[c]==areas[c-1]){
                    double areatotalverdadera =  areas[i];
                    llave = false;
                } 
            }
            c++;
        } else if(limiteinferior<0 && limitesuperior<0){
            int c = 1;
            for(int i=0;i<c;i++){
                
                double area =1;
                areas.push_back(area);
                if(c>1 && areas[c]==areas[c-1]){
                    double areatotalverdadera =  areas[i];
                    llave = false;
                } 
            }
            c++;
        }
    }
    return areatotalverdadera;
}
void GenerarArchivo(int numDatos) {
    ofstream archivo("funcion.dat");
    for (int x = 0; x <= numDatos; x++){
        archivo << x << "\t" << y(x);
        if(x!=numDatos){
            archivo<<endl;
        }
    }
    archivo.close();
}
int main() {
    double largo = 50;
    double n_trapecios = 4;
    double area_total;
    //GenerarArchivo(largo);
    area_total = calcular_area_total(n_trapecios,largo);
    cout<<"el area final es: "<<area_total<<endl;
    return 0;
}