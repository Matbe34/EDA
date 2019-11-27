#include "Player.hh"


/**
 * Write the name of your player and save this file
 * with the same name and .cc extension.
 */
#define PLAYER_NAME Mat34


struct PLAYER_NAME : public Player {

  /**
   * Factory: returns a new instance of this class.
   * Do not modify this function.
   */
  static Player* factory () {
    return new PLAYER_NAME;
  }

  /**
   * Types and attributes for your player can be defined here.
   */
   typedef vector<vector<bool> > Matrix;
   queue<Pos> q;
   vector<pair<int,Pos> > v_T;

   void buida(){
     for(int i = 0; i < q.size(); ++i)q.pop();
   }

   int calcdir(Pos init, Pos final){
     // cout << init.i << "," << init.j << " " << final.i << "," << final.j << endl;
     // getchar();
     if(init.i > final.i) return 0;
     else if(init.i < final.i)return 4;
     else if(init.j > final.j)return 6;
     else if(init.j < final.j)return 2;
     return random(0, 7);
   }

   int calcdirdw(Pos init, Pos final){
     // cout << init.i << "," << init.j << " " << final.i << "," << final.j << endl;
     // getchar();
     if(init.i > final.i and init.j > final.j) return 5;
     if(init.i < final.i and init.j < final.j) return 1;
     if(init.i < final.i and init.j > final.j) return 7;
     if(init.i > final.i and init.j < final.j) return 3;
     else if(init.i < final.i)return 4;
     else if(init.j > final.j)return 6;
     else if(init.j < final.j)return 2;
     return random(0, 7);
   }

   Pos bfs(Matrix& M, Pos pos){
     q.push(pos);
     while(not q.empty()){
        if(!M[q.front().i][q.front().j]){
          M[q.front().i][q.front().j] = true;
          if(q.front().operator+(Top).i >= 0) q.push(q.front().operator+(Top));
          if(q.front().operator+(Bottom).i < 60) q.push(q.front().operator+(Bottom));
          if(q.front().operator+(Left).j >= 0) q.push(q.front().operator+(Left));
          if(q.front().operator+(Right).j < 60) q.push(q.front().operator+(Right));
          if(cell(q.front()).treasure)return q.front();
          q.pop();
        }
        else q.pop();
     }
     return pos;
   }

   void move_dwarves(){
     vector<int> D = dwarves(me());
     int n = D.size();
     vector<Pos> found (n);
     for(int i = 0; i < n; ++i){
       int id = D[i];
       Pos pos = unit(id).pos;
       Pos aux;
       if(operator==(found[i],aux)){
         Matrix M(60, vector<bool>(60,false));
         buida();
         aux = bfs(M,pos);
         found[i] = aux;
       }
       if(found[i] == pos){
         Matrix M(60, vector<bool>(60,false));
         buida();
         aux = bfs(M,pos);
         found[i] = aux;
       }
       aux = found[i];
       int move = calcdirdw(pos,aux);
       command(id, Dir(move));
     }
   }

   void move_wizards(){
     vector<int> W = wizards(me());
     int n = W.size();
     vector<Pos> found (n);
     for(int i = 0; i < n; ++i){
       int id = W[i];
       Pos pos = unit(id).pos;
       Pos aux;
       if(operator==(found[i],aux)){
         Matrix M(60, vector<bool>(60,false));
         buida();
         aux = bfs(M,pos);
         found[i] = aux;
       }
       if(found[i] == pos){
         Matrix M(60, vector<bool>(60,false));
         buida();
         aux = bfs(M,pos);
         found[i] = aux;
       }
       aux = found[i];
       int move = calcdir(pos,aux);
       command(id, Dir(move));
     }
   }

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    move_dwarves();
    move_wizards();
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
