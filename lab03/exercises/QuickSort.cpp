#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

// Definimos nuestra Particion
int Partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for(int j = low; j <= high; j++) {
        if(arr[j]<pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
  swap(arr[i+1],arr[high]);
  return (i+1);
}

// Definimos nuestro algoritmo QuickSort       
void QuickSort(vector<int>& arr, int low, int high) {
    if(low < high) {
        int pi = Partition(arr, low, high);
        QuickSort(arr,low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}  
int main() {

}