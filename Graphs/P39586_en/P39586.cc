#include<iostream>
#include<queue>
#include<vector>
using namespace std;

typedef pair<int,int> arc;
typedef vector<vector<arc> > Mat;

const int MAXDIST = 1e9;
int ways = 0;

int dijkstra(const Mat& mat, int x, int y){
  priority_queue<arc> Q;
  ways = 0;
  int n = mat.size();
  vector<int> d(n,MAXDIST);
  d[x] = 0;
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
        }
        else if(distv == d[v])++ways;
      }
    }
  }
  ++ways;
  return d[y];
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
    int res = dijkstra(mat,x,y);
    if(res != MAXDIST)cout << "cost " << res << ", " << ways << " way(s)" << endl;
    else cout << "no path from " << x << " to " << y << endl;
  }

}
