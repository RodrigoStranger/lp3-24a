#include <iostream>
#include <vector>

using namespace std;

void InsertionSort(vector<int>& arr) { 
    for (int i=1;i<arr.size();++i) { 
        int key=arr[i];
        int j=i-1;
        while (j>-1 && arr[j]>key) {
            arr[j + 1]=arr[j];
            j=j-1;
        }
        arr[j+1]=key;
        cout<<"Iteracion "<<i<<": ";
        for (int k=0;k<arr.size();++k) {
            cout<<arr[k]<<" ";
        }
        cout<<endl;
    }
}

void PrintArray(vector<int>& arr) {
    for (int i=0;i<arr.size();++i) {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

int main() {
    vector<int> caso1={5,2,4,6,1,3};
    cout<<"Array Inicial: ";
    PrintArray(caso1);
    cout<<endl;
    cout<<"Ordenando el Array:"<<endl;
    InsertionSort(caso1);
    cout<<endl;
    cout<<"Resultado Final: ";
    PrintArray(caso1);
    return 0;
}
