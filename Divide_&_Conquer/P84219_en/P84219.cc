#include <iostream>
#include <vector>
using namespace std;

int immersio(double x, const vector<double>& v, int in, int fi){
    if(in > fi) return -1;
    int p = (fi + in)/2;
//     if(fi = in and x != v[in]) return -1;
    /*else*/ if(v[p] > x) return immersio(x,v,in,p-1);
    else if(v[p] < x) return immersio(x,v,p+1,fi);
    if(p == 0 or v[p-1] != x) return p;
    return immersio(x,v,in,p-1);
}

int first_occurrence(double x, vector<double>& v){
    return immersio(x,v,0,v.size()-1);
}

int main() {
    vector<double> v (15);
    double a;
    int i;
    while(cin >> a) {
        v[i] = a;
        ++i;
    }
    cout << first_occurrence(2.5,v) << endl;;
    
}
