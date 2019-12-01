#include<iostream>
#include<queue>
#include<vector>
#include<map>
#include<stack>
using namespace std;

typedef pair<int,int> arc;
typedef vector<vector<arc> > Mat;

const int MAXDIST = 1e9;
vector<int> pare;
vector<int> d;

void printmap(stack<int> m){
  cout << "#################" << endl;
  while(not m.empty()){
    cout << m.top() << " ";
    m.pop();
  }
  cout << endl;
  cout << "#################" << endl;
}

void write(int d, int x){
  if(d == x) cout << d;
  else{
    write(pare[d],x);
    cout << " " << d;
  }
}

void dijkstra(const Mat& mat, int x, int y){
  map<int,int> ant;
  priority_queue<arc> Q;
  int n = mat.size();
  pare = vector<int> (n);
  d = vector<int> (n,MAXDIST);
  d[x] = 0;
  ant.insert(arc(x,x));
  Q.push(make_pair(0,x));
  while(not Q.empty()){
    arc w = Q.top(); Q.pop();
    int dist = -w.first;
    int u = w.second;
    if(dist == d[u]){
      for(int i = 0; i < mat[u].size(); ++i){
        int v = mat[u][i].second;
        int distv = dist + mat[u][i].first;
        if(distv < d[v]){
          d[v] = distv;
          Q.push(arc(-distv,v));
          pare[v] = u;
        }
      }
    }
  }
}

int main(){
  int n, m, x, y, u, v, c;
  while(cin >> n >> m){
    Mat mat(n);
    for(int i = 0; i < m; ++i){
      cin >> u >> v >> c;
      mat[u].push_back(arc(c,v));
    }
    cin >> x >> y;
    dijkstra(mat,x,y);
    if(d[y] != MAXDIST){
      write(y,x);
      cout << endl;
    }
    else cout << "no path from " << x << " to " << y << endl;
  }
}
