#include <iostream>
#include <map>
#include <utility>
using namespace std;

int main (){
    string nom, accio;
    map<string,int> llista;
    int x;
    while(cin >> nom >> accio){
        map<string,int>::iterator it = llista.find(nom);
        if(it == llista.end()){
            if(accio == "enters") llista.insert(make_pair(nom,0));
            else if(accio == "leaves") cout << nom << " is not in the casino" << endl;
            else {
                cout << nom << " is not in the casino" << endl;
                cin >> x;
            }
        }
        else {
            if(accio == "enters") cout << nom << " is already in the casino" << endl;
            else if(accio == "leaves") {
                cout << nom << " has won " << it->second << endl;
                llista.erase(it);
            }
            else if(accio == "wins") {
                cin >> x;
                it->second += x;
            }
        }
    }
    map<string,int>::iterator itr;
    cout << "----------" << endl;
    for(itr = llista.begin(); itr != llista.end(); ++itr) cout << itr->first << " is winning " << itr->second << endl;
}
    
