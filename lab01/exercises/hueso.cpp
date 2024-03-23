#include <iostream>

using namespace std;

string decisionPerrito(int o1, int t1, int o2, int t2) {
	if (o1>o2 && t1>t2) {
		return "Hueso 1";
	} else if (o1<o2 && t1<t2) {
		return "Hueso 2";
	} else {
		return "Perrito confundido :(";
	}
}

int main() {
	int l1, t1, l2, t2;
	cout<<"Digite el olor del hueso 1: ";
	cin>>l1;
	cout<<"Digite el tamaño del hueso 1: ";
	cin>>t1;
	cout<<"Digite el olor del hueso 2: ";
	cin>>l2;
	cout<<"Digite el tamaño del hueso 2: ";
	cin>>t2;
	cout<<"El perrito eligió: "<<decisionPerrito(l1, t1, l2, t2)<<endl;
	return 0;
}
