#include <iostream>
using namespace std;

int DigitalRootRecursive(int n) {
	if (n < 10) {return n;}
	
	int ent = n % 10;
	int res = n / 10;
	int suma = ent + res;
	
	if (suma > 9) {
		return DigitalRootRecursive(suma);
	} else {
		return suma;
	}
}
int main () {
	int n;
	cout<<"Ingrese un numero: ";
	cin>>n;
	if(n!=0) {
		cout<<"El numero digital de "<<n<<" es: "<<DigitalRootRecursive(n);
	}
	return 0;
}
