#include <iostream>
using namespace std;

int DigitalRoot(int n) {
    int entrada = n;
    while(true) {
        int entero = entrada / 10;
        int residuo = entrada % 10;
        if (entero == 0 && residuo < 9) {
            return residuo;
        }
        entrada = entero + residuo;
    }
}

int main() {
    cout << DigitalRoot(154);
    return 0;
}