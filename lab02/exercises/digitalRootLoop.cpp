#include <iostream>
using namespace std;

int DigitalRoot (int n) {
	int entrada = n;
	bool seguir = true;
	while (seguir == true) {
		int ent = 0;
		int res = 0;
		ent = entrada % 10;
		res = entrada / 10;
		if((ent + res) > 9){
			seguir = true;
		} else {
			seguir = false;
		}
		entrada = ent + res;
	}
	return entrada;
}

int main () {
	cout << DigitalRoot(39);
	return 0;
}
