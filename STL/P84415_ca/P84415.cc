#include <iostream>
#include <map>
#include <utility>
using namespace std;

int main () {
  map<string,int> bossa;
  string s, word;
  while(cin >> s){
    if(s == "maximum?"){
      if(bossa.empty()) cout << "indefinite maximum" << endl;
      else {
        auto it = bossa.end(); --it;
        cout << "maximum: " << it->first << ", " << it->second << " time(s)" << endl;
      }
    }
    else if(s == "minimum?"){
      if(bossa.empty()) cout << "indefinite minimum" << endl;
      else cout << "minimum: " << bossa.begin()->first << ", " << bossa.begin()->second << " time(s)" <<endl;
    }
    else if(s == "store"){
      cin >> word;
      map<string,int>::iterator it2 = bossa.find(word);
      if(it2 == bossa.end()){
        bossa.insert(make_pair(word,1));
      }
      else ++it2->second;
    }
    else if(s == "delete"){
      cin >> word;
      map<string,int>::iterator it3 = bossa.find(word);
      if(it3 != bossa.end()){
        if(it3->second != 1) --it3->second;
        else bossa.erase(it3);
      }
    }
  }
}
