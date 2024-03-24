#include <iostream>
using namespace std;

int factorial(int n){
    if(n==0 || n==1){
        return 1;
    } else {
        return n * factorial(n-1);
    }
}
int main() {
  int numero;
  cout << "Digite un numero: ";
  cin >> numero;
  cout << "El factorial de " << numero << " es: " << factorial(numero); 
  return 0;
}