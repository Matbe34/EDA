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
   typedef vector<vector<bool> > Moria;
   queue<Pos> q;
   vector<pair<int,Pos> > v_T;

   static bool mesp(pair<int,Pos> a, pair<int,Pos> b){
     return a.first < b.first;
   }

   int calcdir(Pos init, Pos final){
     if(init.j > final.j) return 4;
     else if(init.j < final.j)return 0;
     else if(init.i > final.i)return 6;
     else if(init.i < final.i)return 2;
     return 0;
   }

   Pos cerca_dicot(vector<pair<int,Pos> > v_T, int id, int l, int r){
     if(l>r)return unit(id).pos;
     else {
       int m = (l+r)/2;
       if(id < v_T[m].first)return cerca_dicot(v_T, id, l, m);
       else if(id > v_T[m].first)return cerca_dicot(v_T, id, m+1, r);
       else return v_T[m].second;
     }
   }

   void bfs(Pos pos, int id){
     q.push(pos);
     Moria M(60, vector<bool> (60, false));
     while(not q.empty()){
       if(/*cell(q.front()).type == Cave and */!M[q.front().operator+(Top).i][q.front().operator+(Top).j]){
         M[q.front().i][q.front().j] = 1;
         if(q.front().operator+(Top).i >= 0 and cell(q.front().operator+(Top)).owner != me() and !M[q.front().operator+(Top).i][q.front().operator+(Top).j])q.push(q.front().operator+(Top));
         if(q.front().operator+(Bottom).i < 60  and cell(q.front().operator+(Bottom)).owner != me() and !M[q.front().operator+(Top).i][q.front().operator+(Top).j])q.push(q.front().operator+(Bottom));
         if(q.front().operator+(Left).j >= 0 and cell(q.front().operator+(Left)).owner != me() and !M[q.front().operator+(Top).i][q.front().operator+(Top).j])q.push(q.front().operator+(Left));
         if(q.front().operator+(Top).j < 60  and cell(q.front().operator+(Right)).owner != me() and !M[q.front().operator+(Top).i][q.front().operator+(Top).j])q.push(q.front().operator+(Right));
         q.pop();
       }
       else if(cell(q.front()).type == Cave and cell(q.front()).treasure){
         v_T.push_back(make_pair(id,q.front()));
         break;
       }
       else q.pop();
     }
   }

   Pos tresor_mes_proper(int id){
     Pos pos = unit(id).pos;
     bfs(pos,id);
     Pos aux = q.front();
     q.pop();
     return aux;
   }

   void move_dwarves(){
     vector<int> D = dwarves(me());
     int n = D.size();
     for(int i = 0; i < n; ++i){
       int id = D[i];
       Pos pos = unit(id).pos;
       bfs(pos,id);
       sort(v_T.begin(),v_T.end()-1, mesp);
       Pos aux = cerca_dicot(v_T, id, 0, 0);
       int move = calcdir(pos,aux);
       command(id, Dir(move));


      /* Pos aux = q.front();
       int move = 0;
       if(not q_T.empty()){
         move = calcdir(pos,q_T.top().second); //calcdir de pos i cercadicot de id en q_T
       }
       else {
         move = calcdir(pos, aux);
         tresor_mes_proper(id);
       }
       command(id, Dir(move));*/
     }
   }

   void move_wizards(){
     vector<int> W = wizards(me());
     int n = W.size();
     for(int i = 0; i < n; ++i){
       command(W[i], Dir(0));
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
