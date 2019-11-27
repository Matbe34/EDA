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
   //Bottom, BR, Right, RT, Top, TL, Left, LB, None,
   //   0     1    2     3   4   5    6     7   8
   typedef vector<vector<char> > Matrix;
   vector<int> W = wizards(me());
   vector<int> D = dwarves(me());
   Pos obj_dwarve;
   Pos obj_wizzard;

   //actualitza els vector d'id's de mags i dwarves
   void actualitza_w_i_d(){
     W = wizards(me());
     D = dwarves(me());
   }

   //Omple el tauler segons Moria. Amb punts, X i t's.
   void omple_Tes(Matrix& Tes){
     for(int i = 1; i < 61; ++i){
       for(int j = 1; j < 61; ++j){
         Pos a (i-1,j-1);
         if(cell(a).treasure)Tes[i][j] = 't';
         else if(cell(a).type != Granite and cell(a).type != Abyss)Tes[i][j] = '.';
       }
     }
   }
   //Retorna el tresor més proper a la posició a tenint en compte el granit i els abismes --> WORKING
   Pos bfs_tresors(Pos a, Matrix Tes){
     int x = a.i;
     int y = a.j;
     queue<pair<int,int> > q;
     q.push(make_pair(x,y));
     while(!q.empty()){
       if(Tes[(q.front().first)][(q.front().second)] == '.'){
         Tes[q.front().first][q.front().second] = 'X';
         q.push(make_pair(q.front().first,q.front().second+1));
         q.push(make_pair(q.front().first,q.front().second-1));
         q.push(make_pair(q.front().first-1,q.front().second));
         q.push(make_pair(q.front().first+1,q.front().second));
         q.pop();
       }
       else if(Tes[q.front().first][q.front().second] == 't'){
         Pos aux;
         aux.i = q.front().first;
         aux.j = q.front().second;
         return aux;
       }
       else q.pop();
     }
     return a;
   }

   //retorna true si el dwarf amb id id es meu
   bool mine(int id){
     int n = D.size();
     for(int i = 0; i < n; ++i)
       if(D[i] == id)return true;
     return false;
   }

   Pos bfs_dwarves(Pos a){
     queue<Pos> q;
     q.push(a);
     set<Pos> s;
     while(not q.empty()){
       int nid = cell(q.front()).id;
       if(nid != -1 and mine(nid)) return q.front();
       else {
         s.insert(q.front());
         if(s.find(Pos(q.front().i,q.front().j+1)) == s.end() and q.front().j+1 < 60)q.push(Pos(q.front().i,q.front().j+1));
         if(s.find(Pos(q.front().i,q.front().j-1)) == s.end() and q.front().j-1 >= 0)q.push(Pos(q.front().i,q.front().j-1));
         if(s.find(Pos(q.front().i-1,q.front().j)) == s.end() and q.front().i-1 >= 0)q.push(Pos(q.front().i-1,q.front().j));
         if(s.find(Pos(q.front().i+1,q.front().j)) == s.end() and q.front().i+1 < 60)q.push(Pos(q.front().i+1,q.front().j));
         q.pop();
       }
     }
     return a;
   }

   void check_enemics(Pos a){
     if(1){}
   }

   //mou dwarve cap a la posicio a
   void move_dwarve(int id, Pos a){
     Pos init = unit(id).pos;
     if(a.i < init.i and a.j < init.j) command(id,Dir(5));
     else if(a.i > init.i and a.j < init.j) command(id,Dir(7));
     else if(a.i < init.i and a.j > init.j) command(id,Dir(3));
     else if(a.i > init.i and a.j > init.j) command(id,Dir(1));
     else if(a.j < init.j) command(id,Dir(4));
     else if(a.j > init.j) command(id,Dir(2));
     else if(a.j < init.j) command(id,Dir(6));
     else if(a.i > init.i) command(id,Dir(0));
     else command(id,Dir(1));
   }

   //mou wizzard cap a la posicio a
   void move_wizzard(int id, Pos a){
     Pos init = unit(id).pos;
     if(a.i > init.i) command(id,Dir(0));
     else if(a.i < init.i) command(id,Dir(4));
     else if(a.j > init.j) command(id,Dir(2));
     else if(a.j < init.j) command(id,Dir(6));
     else command(id,Dir(0));
   }

   //Els dwarves es mouen cap als tresors mes propers tenint en compte parets i abismes nomes.
   void move_dwarves(Matrix& Tes){
     vector<int> D = dwarves(me());
     int n = D.size();
     for(int i = 0; i < n; ++i){
       int id = D[i];
       if(round()%5 == 0)obj_dwarve = bfs_tresors(unit(id).pos, Tes); //tresor més proper a id
       move_dwarve(id,obj_dwarve); //movem id cap a a
     }
   }

   void move_wizards(){
     vector<int> W = wizards(me());
     int n = W.size();
     //s'han de moure cap el dwarve mes proper per curar-lo
     for(int i = 0; i < n; ++i){
       int id = W[i];
       if(round()%15 == 0)obj_wizzard = bfs_dwarves(unit(id).pos);
       move_wizzard(id,obj_wizzard);
     }
   }

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    Matrix Tes(62, vector<char> (62,'X'));
    if(round() == 0){
      omple_Tes(Tes);
    }
    actualitza_w_i_d();
    move_dwarves(Tes);
    move_wizards();
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
