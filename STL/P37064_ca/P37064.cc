#include <iostream>
#include <set>
#include <string>
using namespace std;

int main(){
  set<string> set;
  string s;
  cin >> s;
  auto mediana = set.end();
  while(s != "END"){
    set.insert(s);
    auto it = set.find(s);
    if(mediana == set.end()) mediana = it;
    else if(set.size()%2 == 0 and s < *mediana) --mediana;
    else if(set.size()%2 != 0 and s > *mediana) ++mediana;
    cout << *mediana << endl;
    cin >> s;
  }
}
