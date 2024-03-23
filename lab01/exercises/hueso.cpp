#include <iostream>

using namespace std;

int main() {
    int l1,t1,l2,t2 = 0;
    cout<<"Digite el olor del hueso 1: ";
    cin>>l1;
    cout<<"Digite el tamaño del hueso 1: ";
    cin>>t1;
    cout<<"Digite el olor del hueso 2: ";
    cin>>l2;
    cout<<"Digite el tamaño del hueso 2: ";
    cin>>t2;
    if(l1>l2 && t1>t2) {
        cout<<"Hueso 1";
    } else if(l1<l2 && t1<t2) {
        cout<<"Hueso 2";
    } else {
        cout<<"Perrito confundido :(";
    }
    return 0;
}
