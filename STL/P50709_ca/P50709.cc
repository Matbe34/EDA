//time limit per utilitzar maps
#include <iostream>
#include <map>
#include <utility>
using namespace std;

int cercamax(const map<int, int>& llista, int& x){
  map<int,int>::const_iterator it = llista.begin();
  x = it->first;
  for(it = llista.begin(); it != llista.end(); ++it){
    if(it->first > x)x = it->first;
  }
  return x;
}

int main (){
  int x, max;
  char a;
  map<int,int> llista;
  while(cin >> a){
    if(llista.empty()){
      if(a != 'S') {
        cout << "error!" << endl;
        if(a != 'A' and a != 'R')cin >> x;
      }
      else {
        cin >> x;
        llista.insert(make_pair(x,1));
        max = x;
      }
    }
    else {
      if(a == 'S'){
        cin >> x;
        map<int, int>::iterator it = llista.find(x);
        if(it != llista.end()) ++it->second;
        else {
          llista.insert(make_pair(x,1));
          if(x > max)max = x;
        }
      }
      else if(a == 'A'){
        cout << max << endl;
      }
      else if(a == 'R'){
        map<int, int>::iterator it = llista.find(max);
        if(it->second != 1)--it->second;
        else {
          llista.erase(it);
          if(not llista.empty()) max = cercamax(llista,x);
        }
      }
      else if(a == 'I'){
        cin >> x;
        map<int, int>::iterator it = llista.find(max);
        if(it->second != 1) {
          --it->second;
          x += it->first;
          map<int, int>::iterator itr = llista.find(x);
          if(itr == llista.end())llista.insert(make_pair(x,1));
          else ++itr->second;
          max = x;
        }
        else {
          x += it->first;
          llista.erase(it);
          map<int, int>::iterator itr = llista.find(x);
          if(itr == llista.end())llista.insert(make_pair(x,1));
          else ++itr->second;
          max = x;
        }
      }
      else if(a == 'D'){
        cin >> x;
        map<int, int>::iterator it = llista.find(max);
        if(it->second != 1) {
          --it->second;
          x -= it->first;
          map<int, int>::iterator itr = llista.find(x);
          if(itr == llista.end())llista.insert(make_pair(x,1));
          else ++itr->second;
        }
        else {
          llista.erase(it);
          x = it->first - x;
          map<int, int>::iterator itr = llista.find(x);
          if(itr == llista.end())llista.insert(make_pair(x,1));
          else ++itr->second;
          max = cercamax(llista,x);
        }
      }
    }
  }
}
