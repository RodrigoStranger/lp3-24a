#include <iostream>
using namespace std;
int main() {
	int factorial = 1 , numero;
	cout<<"Digite un numero: ";
	cin>>numero;
	for(int i=2;i<=numero;i++){
		factorial = factorial * i;
	}
	cout<<"El factorial de "<<numero<<" es: "<<factorial<<endl;
	return 0;
}
