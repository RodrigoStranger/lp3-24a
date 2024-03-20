#include <iostream>
#include <vector>
using namespace std;
void ImprimirTablero(int filas, int columnas) {
    vector<vector<char>> tablero(filas, vector<char>(columnas, ' '));
    for (int i = 0; i < filas; ++i) {
        for (int k = 0; k < columnas; ++k) {
            cout << "----";
        }
        cout << "-" << endl;
        for (int j = 0; j < columnas; ++j) {
            cout << "| " << tablero[i][j] << " ";
        }
        cout << "|" << endl;
    }
    for (int k = 0; k < columnas; ++k) {
        cout << "----";
    }
    cout << "-" << endl;
}
int main() {
    ImprimirTablero(10, 10);
    return 0;
}