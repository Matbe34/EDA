#include<iostream>
#include<queue>
#include<vector>
#include<stack>
using namespace std;

typedef vector<vector<int> > graph;

vector<bool> visited;
queue<int> res;

void ordenaciotop(graph& G, int x){
  for(int i = 0; i < G[x].size(); ++i){
    if(not visited[G[x][i]]){
      ordenaciotop(G,G[x][i]);
    }
    visited[G[x][i]] = true;
  }
  res.push(x);
}

int main(){
  int n, m;
  while(cin >> n >> m){
    graph G(n);
    int x, y;
    visited = vector<bool> (n);
    for(int i = 0; i < m; ++i){
      cin >> x >> y;
      G[y].push_back(x);
    }
    for(int i = 0; i < n; ++i){
      if(not visited[i]) {
        visited[i] = true;
        ordenaciotop(G,i);
      }
    }
    if(not res.empty()){
      cout << res.front();
      res.pop();
    }
    while(not res.empty()){
      cout << " " << res.front();
      res.pop();
    }
    cout << endl;
  }
}
