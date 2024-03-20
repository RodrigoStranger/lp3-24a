#include <iostream>
#include <vector>
using namespace std;
void ImprimirTablero() {
    char l1 = 'I', l2 = 'N', l3 = 'F', l4 = 'A', l5 = 'N', l6 = 'Z', l7 = 'O', l8 = 'N';
    char tablero[8][8] = {
        {l1, ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', l2, ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', l3, ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', l4, ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', l5, ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', l6, ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', l7, ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', l8}
    };
    cout << "---------------------------------" << endl;
    for (int i = 0; i < 8; i++) {
        cout << "| ";
    for (int j = 0; j < 8; j++) {
            cout << tablero[i][j] << " | ";
    }
        cout << endl << "---------------------------------" << endl;
}

}
int main() {
    ImprimirTablero();
    return 0;
}