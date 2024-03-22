#include <iostream>
using namespace std;

int DigitalRootRecursivo(int n){
    if (n < 10) { return n;}
    int suma = 0;
    while (n != 0) {
        suma += n % 10;
        n /= 10;
    }
    return DigitalRoot(suma);
}

int main() {
    cout << DigitalRootRecursivo(154);
    return 0;
}
