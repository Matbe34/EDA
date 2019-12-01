#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int> > M;

M ID = {{1,0},{0,1}};

M mult(const M& a, const M& b, int m){
  M res(2,vector<int>(2,0));
  for(int i = 0; i < 2; ++i){
    for(int j = 0; j < 2; ++j){
      for(int k = 0; k < 2; ++k) res[i][j] += a[i][k] * b[k][j];
      res[i][j] = res[i][j]%m;
    }
  }
  return res;
}

M quick(M& mat, int n, int m){
    if(n == 0) return ID;
    M aux = quick(mat,n/2,m);
    if(n%2 == 0) return (mult(aux,aux,m));
    return mult((mult(aux,aux,m)),mat,m);
}

int main(){
  int m1, m2, m3, m4, n, m;
  while(cin >> m1 >> m2 >> m3 >> m4 >> n >> m){
    M mat(2,vector<int>(2,0));
    mat[0][0] = m1;
    mat[0][1] = m2;
    mat[1][0] = m3;
    mat[1][1] = m4;
    M res(2,vector<int>(2,0));
    res = quick(mat,n,m);
    cout << res[0][0] << " " << res[0][1] << endl;
    cout << res[1][0] << " " << res[1][1] << endl;
    cout << "----------" << endl;
  }
}
