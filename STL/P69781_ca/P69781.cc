#include <iostream>
#include <set>
using namespace std;

int collatz(int& x, int& y, int& n, set<int>& seq, bool& b){
    set<int>::iterator it = seq.find(n);
    if(n > 100000000) {
        b = true;
        return n;
    }
    else if(it != seq.end()) return n;
    else {
        seq.insert(n);
        if(n%2 == 0) n = n/2 + x;
        else n = n*3 + y;
        return collatz(x,y,n,seq,b);
    }
}

int collatz2(int& x, int& y, int& n, int& cicles, set<int>& seq){
    set<int>::iterator it = seq.find(n);
    if(it != seq.end()) return cicles;
    else {
        seq.insert(n);
        if(n%2 == 0) n = n/2 + x;
        else n = n*3 + y;
        ++cicles;
        return collatz2(x,y,n,cicles,seq);
    }
}

int main () {
    int x, y, n, cicles;
    set<int> seq;
    while(cin >> x >> y >> n){
        seq.clear();
        bool b = false;
        cicles = 0;
        int p = collatz(x,y,n,seq,b);
        if(not b){
            seq.clear();
            cout << collatz2(x,y,p,cicles,seq) << endl;
        }
        else cout << p << endl;
    }
}
