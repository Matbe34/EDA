#include <iostream>
#include <vector>
using namespace std;

bool f(double x, const vector<double>& v, int esq, int dre){
    if(esq + 1 >= dre){
        if(esq == dre and v[esq] == x) return true;
        else if(esq + 1 == dre) return (v[esq] == x or v[dre] == x);
        return false;
    }
    int a = (esq + dre)/2;
    if(v[a] < x){
        if(v[a+1] < v[a] and v[a+1] < v[a-1])
    
}

bool resistant_search(double x, const vector<double>& v){
    return f(x,v,0,v.size()-1);
}
