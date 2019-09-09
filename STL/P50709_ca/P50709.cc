#include <iostream>
#include <map>
#include <utility>
#include <queue>
using namespace std;

int main () {
    priority_queue<int> cua;
    char a;
    int x;
    while(cin >> a){
        if(a == 'A'){
            if(not cua.empty()) cout << cua.top() << endl;
            else cout << "error!" << endl;
        }
        else if(a == 'S'){
            cin >> x;
            cua.push(x);
        }
        else if(a == 'R'){
            if(cua.empty()) cout << "error!" << endl;
            else cua.pop();
        }
        else if(a == 'I'){
            cin >> x;
            if(cua.empty()) cout << "error!" << endl;
            else {
                x += cua.top();
                cua.pop();
                cua.push(x);
            }
        }
        else if(a == 'D'){
            cin >> x;
            if(cua.empty()) cout << "error!" << endl;
            else {
                x = cua.top() - x;
                cua.pop();
                cua.push(x);
            }
        }
    }
}
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
// void actualitzamax(const map<int, int>& llista, int& x){
//   map<int,int>::const_iterator it = llista.end();
//   --it;
//   x = it->first;
// }
// 
// int main (){
//   int x, max;
//   char a;
//   map<int,int> llista;
//   while(cin >> a){
//     if(llista.empty()){
//       if(a != 'S') {
//         cout << "error!" << endl;
//         if(a != 'A' and a != 'R')cin >> x;
//       }
//       else {
//         cin >> x;
//         llista.insert(make_pair(x,1));
//         max = x;
//       }
//     }
//     else {
//       if(a == 'S'){
//         cin >> x;
//         map<int, int>::iterator it = llista.find(x);
//         if(it != llista.end()) ++it->second;
//         else {
//             if(x > max or llista.empty())max = x;
//             llista.insert(make_pair(x,1));
//         }
//       }
//       else if(a == 'A'){
//         cout << max << endl;
//       }
//       else if(a == 'R'){
//         map<int, int>::iterator it = llista.find(max);
//         if(it->second != 1)--it->second;
//         else {
//           llista.erase(it);
//           if(not llista.empty()) actualitzamax(llista,max);
//         }
//       }
//       else if(a == 'I'){
//         cin >> x;
//         map<int, int>::iterator it = llista.find(max);
//         if(it->second != 1) {
//           --it->second;
//           x += it->first;
//           map<int, int>::iterator itr = llista.find(x);
//           if(itr == llista.end())llista.insert(make_pair(x,1));
//           else ++itr->second;
//           actualitzamax(llista,max);
//         }
//         else {
//           x += it->first;
//           llista.erase(it);
//           map<int, int>::iterator itr = llista.find(x);
//           if(itr == llista.end())llista.insert(make_pair(x,1));
//           else ++itr->second;
//           actualitzamax(llista,max);
//         }
//       }
//       else if(a == 'D'){
//         cin >> x;
//         map<int, int>::iterator it = llista.find(max);
//         if(it->second != 1) {
//           --it->second;
//           x -= it->first;
//           map<int, int>::iterator itr = llista.find(x);
//           if(itr == llista.end())llista.insert(make_pair(x,1));
//           else ++itr->second;
//         }
//         else {
//           llista.erase(it);
//           x = it->first - x;
//           map<int, int>::iterator itr = llista.find(x);
//           if(itr == llista.end())llista.insert(make_pair(x,1));
//           else ++itr->second;
//           actualitzamax(llista,max);
//         }
//       }
//       else cout << "error!" << endl;
//     }
//   }
// }
