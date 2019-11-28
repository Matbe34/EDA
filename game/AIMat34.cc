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
   vector<pair<int,Pos> > DwP; //vector amb parell de id i pos de cada dwarve
   vector<Pos> tresors; //vector on estan les posicions dels tresors
   Pos obj_dwarve; //objectiu dels dwarves
   Pos obj_wizzard; //objectiu dels mags

   //retorna una posicio fet el moviment indicat: 0 = UP, 1 = RIGHT, 2 = DOWN, 3 = LEFT
   Pos mou(Pos a, int s){
     switch (s){
       case 0: --a.i; break;
       case 2: ++a.i; break;
       case 3: --a.j; break;
       case 1: ++a.j; break;
       case 4: ++a.j; --a.i; break;
       case 5: ++a.j; ++a.i; break;
       case 6: --a.j; ++a.i; break;
       case 7: --a.j; --a.i; break;
       default: ;
     }
     return a;
   }

   //actualitza els vector d'id's de mags i dwarves
   void actualitza_w_i_d(){
     W = wizards(me());
     D = dwarves(me());
     int n = D.size();
     DwP.clear();
     for(int i = 0; i < n; ++i)DwP.push_back(make_pair(D[i],unit(D[i]).pos));
   }

   void printset(const set<Pos>& s){
     set<Pos>::iterator it;
     for(it = s.begin(); it != s.end(); ++it)cout << (*it).i << "," << (*it).j << " ";
     cout << endl;
   }

   //Troba tots els tresors inicials i els posa la seva posició al vector tresors --> eficient
   void bfs_tresors(Pos a){
     int cont =0;
     queue<Pos> q;
     q.push(a);
     set<Pos> s;
     s.insert(q.front());
     while(not q.empty() and tresors.size() < 80){
       Pos aux = q.front();
       if(cell(aux).treasure)tresors.push_back(aux);

       else {
         if(s.find(mou(aux,1)) == s.end() and pos_ok(mou(aux,1))) {q.push(mou(aux,1)); s.insert(mou(aux,1));}
         if(s.find(mou(aux,2)) == s.end() and pos_ok(mou(aux,2))) {q.push(mou(aux,2)); s.insert(mou(aux,2));}
         if(s.find(mou(aux,3)) == s.end() and pos_ok(mou(aux,3))) {q.push(mou(aux,3)); s.insert(mou(aux,3));}
         if(s.find(mou(aux,4)) == s.end() and pos_ok(mou(aux,4))) {q.push(mou(aux,4)); s.insert(mou(aux,4));}
       }
       q.pop();
     }
   }

   //retorna true si el dwarf amb id id es meu
   bool mine(int id){
     int n = D.size();
     int m = W.size();
     for(int i = 0; i < n; ++i)
       if(D[i] == id)return true;
     for(int i = 0; i < m; ++i)
       if(W[i] == id)return true;
     return false;
   }

   //retorna la distancia entre a i b
   int dist_min(Pos a, Pos b){
     return abs(a.i - b.i) + abs(a.j - b.j);
   }

   //retorna la posicio del tresor mes proper a a
   Pos tresor_proper(Pos a){
     int n = tresors.size();
     Pos fi = tresors[0];
     int min = dist_min(a,tresors[0]);
     for(int i = 1; i < n; ++i){
       int aux = dist_min(a,tresors[i]);
       if(aux < min){
         min = aux;
         fi = tresors[i];
       }
     }
     return fi;
   }

   //retorna la posicio del dwarve mes proper a a
   Pos bfs_dwarves(Pos a){
     int n = DwP.size();
     int min = dist_min(a,DwP[0].second);
     Pos fi = DwP[0].second;
     for(int i = 1; i < n; ++i){
       int aux = dist_min(a,DwP[i].second);
       if(aux < min) {
         min = aux;
         fi = DwP[i].second;
       }
     }
     return fi;
   }

   //posa b a true si tenim enemics a menys de 2 caselles i retorna la pos de l'enemic més proper o la propia
   Pos check_enemics(Pos a, bool& b){
     int i,j,lim1,lim2;
     if(a.i > 1)i = a.i - 2;
     else i = 0;
     if(a.j > 1)j = a.j - 2;
     else j = 0;
     if(a.i < 59)lim1 = a.i + 2;
     else lim1 = 60;
     if(a.j < 59)lim2 = a.j + 2;
     else lim2 = 60;
     for(int p = i; p < lim1; ++p){
       for(int q = j; q < lim2; ++q){
         if(cell(Pos(p,q)).id != -1 and not mine(cell(Pos(p,q)).id)){
           b = true;
           return Pos(p,q);
         }
       }
     }
     return a;
   }

   //ens allunyem del balrog si el tenim aprop
   void escape_balrog(Pos a){
     int i,j,lim1,lim2;
     if(a.i > 1)i = a.i - 2;
     else i = 0;
     if(a.j > 1)j = a.j - 2;
     else j = 0;
     if(a.i < 59)lim1 = a.i + 2;
     else lim1 = 60;
     if(a.j < 59)lim2 = a.j + 2;
     else lim2 = 60;
     int id = cell(a).id;
     for(int p = i; p < lim1; ++p){
       for(int q = j; q < lim2; ++q){
         if(cell(Pos(p,q)).id == balrog_id()){
           cout << 1111111111 << " " << id << " (" << p << "," << q << ")" << endl;
           if(unit(cell(a).id).type == Dwarf)run_dwarve(id,Pos(p,q));
           else run_wizzard(id,Pos(p,q));
         }
       }
     }
   }

   //mou dwarve cap a la posicio a (falta evitar granit i abismes)
   void move_dwarve(int id, Pos a){
     Pos init = unit(id).pos;
     if(a.i < init.i and a.j < init.j) command(id,Dir(5));
     else if(a.i > init.i and a.j < init.j) command(id,Dir(7));
     else if(a.i < init.i and a.j > init.j) command(id,Dir(3));
     else if(a.i > init.i and a.j > init.j) command(id,Dir(1));
     else if(a.j < init.j) command(id,Dir(6));
     else if(a.j > init.j) command(id,Dir(2));
     else if(a.i < init.i) command(id,Dir(4));
     else if(a.i > init.i) command(id,Dir(0));
     else command(id,Dir(1));
   }

   //mou wizzard cap a la posicio a (falta evitar granit i abismes)
   void move_wizzard(int id, Pos a){
     Pos init = unit(id).pos;
     if(a.i > init.i) command(id,Dir(0));
     else if(a.i < init.i) command(id,Dir(4));
     else if(a.j > init.j) command(id,Dir(2));
     else if(a.j < init.j) command(id,Dir(6));
     else command(id,Dir(0));
   }

   //Dwarve s'allunya de la posicio a ja que hi ha un enemic (falta evitar roca, granit i abismes)
   void run_dwarve(int id, Pos a){
     Pos init = unit(id).pos;
     if(a.i < init.i and a.j < init.j) {
       if(cell(mou(init,5)).type !=  Rock or cell(mou(init,5)).type !=  Granite or cell(mou(init,5)).type !=  Abyss)command(id,Dir(1));
     }
     else if(a.i > init.i and a.j < init.j) {
       if(cell(mou(init,5)).type !=  Rock or cell(mou(init,5)).type !=  Granite or cell(mou(init,5)).type !=  Abyss) command(id,Dir(3));
     }
     else if(a.i < init.i and a.j > init.j){
       if(cell(mou(init,5)).type !=  Rock or cell(mou(init,5)).type !=  Granite or cell(mou(init,5)).type !=  Abyss) command(id,Dir(7));
     }
     else if(a.i > init.i and a.j > init.j) {
       if(cell(mou(init,5)).type !=  Rock or cell(mou(init,5)).type !=  Granite or cell(mou(init,5)).type !=  Abyss) command(id,Dir(5));
     }
     else if(a.j < init.j) {
       if(cell(mou(init,5)).type !=  Rock or cell(mou(init,5)).type !=  Granite or cell(mou(init,5)).type !=  Abyss) command(id,Dir(2));
     }
     else if(a.j > init.j) {
       if(cell(mou(init,5)).type !=  Rock or cell(mou(init,5)).type !=  Granite or cell(mou(init,5)).type !=  Abyss) command(id,Dir(6));
     }
     else if(a.i < init.i) {
       if(cell(mou(init,5)).type !=  Rock or cell(mou(init,5)).type !=  Granite or cell(mou(init,5)).type !=  Abyss) command(id,Dir(0));
     }
     else if(a.i > init.i) {
       if(cell(mou(init,5)).type !=  Rock or cell(mou(init,5)).type !=  Granite or cell(mou(init,5)).type !=  Abyss) command(id,Dir(4));// 4 2 0 6 3 1 7 5
     }
     else command(id,Dir(3));
   }

   //Wizzard s'allunya de la posicio a ja que hi ha un enemic (falta evitar roca, granit i abismes)
   void run_wizzard(int id, Pos a){
     Pos init = unit(id).pos;
     if(a.i > init.i) command(id,Dir(4));
     else if(a.i < init.i) {
       if(cell(mou(init,5)).type !=  Rock or cell(mou(init,5)).type !=  Granite or cell(mou(init,5)).type !=  Abyss) command(id,Dir(0));
     }
     else if(a.j > init.j) {
       if(cell(mou(init,5)).type !=  Rock or cell(mou(init,5)).type !=  Granite or cell(mou(init,5)).type !=  Abyss) command(id,Dir(6));
     }
     else if(a.j < init.j) {
       if(cell(mou(init,5)).type !=  Rock or cell(mou(init,5)).type !=  Granite or cell(mou(init,5)).type !=  Abyss) command(id,Dir(2));
     }
     else command(id,Dir(4));
   }

   //Els dwarves es mouen cap als tresors mes propers tenint en compte parets i abismes nomes.
   void move_dwarves(){
     vector<int> D = dwarves(me());
     int n = D.size();
     for(int i = 0; i < n; ++i){
       int id = D[i];

       escape_balrog(unit(id).pos); //primer fugim del balrog si el tenim aprop

       bool b = false;
       Pos enem = check_enemics(unit(id).pos, b);
       if(b and unit(cell(enem).id).type != Dwarf and unit(cell(enem).id).type != Wizard)run_dwarve(id,enem); //fugim de les unitats de Sauron
       else if(b)move_dwarve(id,enem);
       else{
         obj_dwarve = tresor_proper(unit(id).pos); //tresor més proper a id
         move_dwarve(id,obj_dwarve); //movem id cap a a
       }
     }
   }

   //els wizzards es mouen cap al dwarve mes proper. (maybe xoquen amb parets i/o roques?)
   void move_wizards(){
     vector<int> W = wizards(me());
     int n = W.size();
     //s'han de moure cap el dwarve mes proper per curar-lo
     for(int i = 0; i < n; ++i){
       int id = W[i];

       escape_balrog(unit(id).pos); //primer fugim del balrog si el tenim aprop

       bool b = false;
       Pos enem = check_enemics(unit(id).pos, b);
       if(b)run_wizzard(id,enem); //fugim de l'enemic

       else {
         obj_wizzard = bfs_dwarves(unit(id).pos); //dwarve mes proper
         move_wizzard(id,obj_wizzard); //no hi ha enemics aprop
       }
     }
   }

  /**
   * Play method, invoked once per each round.
   */
  virtual void play () {
    if(round() == 0)bfs_tresors(Pos(28,28)); //inicialitzem vector tresors
    actualitza_w_i_d(); //actualitzem cantitat de dwarves i wizzards
    move_dwarves();
    move_wizards();
  }

};


/**
 * Do not modify the following line.
 */
RegisterPlayer(PLAYER_NAME);
