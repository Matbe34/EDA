#include <iostream>
#include <map>
#include <utility>
using namespace std;

int main () {
  map<string,int> bossa;
  string s, word, min = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", max = "";
  while(cin >> s){
    if(s == "maximum?"){
      map<string,int>::iterator it = bossa.find(max);
      if(bossa.empty()) cout << "undefinite maximum" << endl;
      else cout << "maximum: " << max << ", " << it->second << " time(s)" << endl;
    }
    else if(s == "minimum?"){
      map<string,int>::iterator it2 = bossa.find(min);
      if(bossa.empty()) cout << "undefinite minimum" << endl;
      else cout << "minimum: " << min << ", " << it2->second << " time(s)" <<endl;
    }
    else if(s == "store"){
      cin >> word;
      map<string,int>::iterator it2 = bossa.find(word);
      if(it2 == bossa.end()) bossa.insert(make_pair(word,1));
      else ++it2->second;
    }
    else if(s == "delete"){
      cin >> word;
      map<string,int>::iterator it3 = bossa.find(word);
      if(it != bossa.end()){
        if(it->second != 1) --it->second;
        else bossa.erase(it);
      }
    }
  }
