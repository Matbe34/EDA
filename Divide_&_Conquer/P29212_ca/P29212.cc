#include <iostream>
using namespace std;

int quick(int n, int k, int m){
    if(k == 0) return 1;
    int aux = quick(n,k/2,m)%m;
    if(k%2 == 0) return (aux*aux)%m;
    return (((aux*aux)%m)*n)%m;
}

int main(){
}
