#include<iostream>
#include<vector>
#include<queue>
using namespace std;

typedef vector<vector<int> > graph;
vector<bool> visited;

bool bfs(graph& G){
  int n = G.size();
  visited = vector<bool> (n,false);
  queue<int> p;
  p.push(0);
  while(not p.empty()){
    int x = p.front();
    if(not visited[x]){
      for(int i = 0; i < G[x].size(); ++i){
        p.push(G[x][i]);
      }
      if(G[x].size() != 0)visited[x] = true;
      p.pop();
    }
    else return true;
  }
  return false;
}

int main(){
  int n, m;
  while(cin >> n >> m){
    graph G(n);
    int u, v;
    for(int i = 0; i < m; ++i){
      cin >> u >> v;
      G[u].push_back(v);
    }
    if(bfs(G))cout << "yes" << endl;
    else cout << "no" << endl;
  }
}
