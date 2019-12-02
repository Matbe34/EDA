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

   vector<int> W ;//= wizards(me());
   vector<int> D ;//= dwarves(me());
   vector<pair<int,Pos> > DwP; //vector amb parell de id i pos de cada dwarve
   vector<pair<int,Pos> > WiP; //vector amb parell de id i pos de cada wizard
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
     int m = W.size();
     WiP.clear();
     for(int i = 0; i < m; ++i)WiP.push_back(make_pair(W[i],unit(W[i]).pos));
   }

   List dijkstra(Pos a){
     priority_queue<pair<Pos,int> > q;
     q.push(make_pair(a,0));
     vector<Pos> came_from(3600);
     came_from[a.i*60+a.j] = Pos(-1,-1);
     vector<int> cost(3600,1e9);
     cost[a.i*60+a.j] = 0;
     while(not q.empty()){
       Pos current = q.front(); q.pop();

       if(current == target)break;
       for(int i = 0; i < 4; ++i){
         Pos aux = neighbour(current,i);
         int cost =
       }

     }

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

   //retorna la posicio del dwarf enemic mes proper a a
   Pos bfs_dw_enem(Pos a){
     queue<Pos> q;
     set<Pos> notvis;
     q.push(a);
     notvis.insert(a);
     while(not q.empty()){
       Pos aux = q.front();
       if(cell(aux).id != -1 and (unit(cell(aux).id).type == Dwarf or unit(cell(aux).id).type == Wizard)and not mine(cell(aux).id))return q.front();
       else{
         if(pos_ok(mou(q.front(),0)) and (cell(mou(q.front(),0)).type == Cave or cell(mou(q.front(),0)).type == Outside or cell(mou(q.front(),0)).type == Rock)) {
           if(notvis.find(mou(q.front(),0)) == notvis.end()) q.push(mou(q.front(),0));
           notvis.insert(mou(q.front(),0));
         }
         if(pos_ok(mou(q.front(),1)) and (cell(mou(q.front(),1)).type == Cave or cell(mou(q.front(),1)).type == Outside or cell(mou(q.front(),1)).type == Rock)) {
           if(notvis.find(mou(q.front(),1)) == notvis.end()) q.push(mou(q.front(),1));
           notvis.insert(mou(q.front(),1));
         }
         if(pos_ok(mou(q.front(),2)) and (cell(mou(q.front(),2)).type == Cave or cell(mou(q.front(),2)).type == Outside or cell(mou(q.front(),2)).type == Rock)) {
           if(notvis.find(mou(q.front(),2)) == notvis.end()) q.push(mou(q.front(),2));
           notvis.insert(mou(q.front(),2));
         }
         if(pos_ok(mou(q.front(),3)) and (cell(mou(q.front(),3)).type == Cave or cell(mou(q.front(),3)).type == Outside or cell(mou(q.front(),3)).type == Rock)) {
           if(notvis.find(mou(q.front(),3)) == notvis.end()) q.push(mou(q.front(),3));
           notvis.insert(mou(q.front(),3));
         }
         q.pop();
       }
     }
     return a;
   }

   Pos bfs_wizards(Pos a){
     int n = WiP.size();
     int min = dist_min(a,WiP[0].second);
     Pos fi = WiP[0].second;
     for(int i = 1; i < n; ++i){
       int aux = dist_min(a,WiP[i].second);
       if(aux < min) {
         min = aux;
         fi = WiP[i].second;
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

   //retorna la casella mes propera que no sigui meva
   Pos adj_nempty(Pos a){
     if(pos_ok(mou(a,0)) and cell(mou(a,0)).type == Cave and cell(mou(a,0)).owner != me())return mou(a,0);
     if(pos_ok(mou(a,2)) and cell(mou(a,1)).type == Cave and cell(mou(a,2)).owner != me())return mou(a,2);
     if(pos_ok(mou(a,3)) and cell(mou(a,1)).type == Cave and cell(mou(a,3)).owner != me())return mou(a,3);
     else return mou(a,1);
   }

   //posa b a true si tenim enemics a menys de 2 caselles i retorna la pos de l'enemic més proper o la propia
   Pos check_enemics(Pos a, bool& b, int n){
     int i,j,lim1,lim2;
     if(a.i > 1)i = a.i - n;
     else i = 0;
     if(a.j > 1)j = a.j - n;
     else j = 0;
     if(a.i < 59)lim1 = a.i + n;
     else lim1 = 60;
     if(a.j < 59)lim2 = a.j + n;
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
           if(unit(cell(a).id).type == Dwarf)run_dwarve(id,Pos(p,q));
           else run_wizzard(id,Pos(p,q));
         }
       }
     }
   }

   //retorna true si la pos a te un mag al voltant (1 2 3 4) maybe not working
   bool mag_aprop(Pos a){
     if(pos_ok(mou(a,1)) and mine(cell(mou(a,1)).id) and unit(cell(mou(a,1)).id).type == Wizard)return true;
     if(pos_ok(mou(a,2)) and mine(cell(mou(a,2)).id) and unit(cell(mou(a,2)).id).type == Wizard)return true;
     if(pos_ok(mou(a,3)) and mine(cell(mou(a,3)).id) and unit(cell(mou(a,3)).id).type == Wizard)return true;
     if(pos_ok(mou(a,4)) and mine(cell(mou(a,4)).id) and unit(cell(mou(a,4)).id).type == Wizard)return true;
     return false;
   }

   //mou dwarve cap a la posicio a CORRECTE
   void move_dwarve(int id, Pos a){
     Pos init = unit(id).pos;
     if(init.i < a.i and init.j < a.j){
       if(pos_ok(mou(init,5)) and cell(mou(init,5)).type != Granite and cell(mou(init,5)).type != Abyss) command(id,Dir(1));
       else if(init.i > a.i and init.j > a.j){
         if(pos_ok(mou(init,7)) and cell(mou(init,7)).type != Granite and cell(mou(init,7)).type != Abyss) command(id,Dir(5));
       }
       else if(init.i < a.i and init.j > a.j){
         if(pos_ok(mou(init,6)) and cell(mou(init,6)).type != Granite and cell(mou(init,6)).type != Abyss) command(id,Dir(7));
       }
       else if(init.i > a.i and init.j < a.j){
         if(pos_ok(mou(init,4)) and cell(mou(init,4)).type != Granite and cell(mou(init,4)).type != Abyss) command(id,Dir(3));
       }
       else if(init.i < a.i){
         if(pos_ok(mou(init,2)) and cell(mou(init,2)).type != Granite and cell(mou(init,2)).type != Abyss) command(id,Dir(0));
       }
       else if(init.i > a.i){
         if(pos_ok(mou(init,0)) and cell(mou(init,0)).type != Granite and cell(mou(init,0)).type != Abyss) command(id,Dir(4));
       }
       else if(init.j < a.j){
         if(pos_ok(mou(init,1)) and cell(mou(init,1)).type != Granite and cell(mou(init,1)).type != Abyss) command(id,Dir(2));
       }
       else if(init.j > a.j){
         if(pos_ok(mou(init,3)) and cell(mou(init,3)).type != Granite and cell(mou(init,3)).type != Abyss) command(id,Dir(6));
       }
     }

     if(init.i > a.i and init.j > a.j){
       if(pos_ok(mou(init,7)) and cell(mou(init,7)).type != Granite and cell(mou(init,7)).type != Abyss) command(id,Dir(5));
       else if(init.i < a.i and init.j < a.j){
         if(pos_ok(mou(init,5)) and cell(mou(init,5)).type != Granite and cell(mou(init,5)).type != Abyss) command(id,Dir(1));
       }
       else if(init.i < a.i and init.j > a.j){
         if(pos_ok(mou(init,6)) and cell(mou(init,6)).type != Granite and cell(mou(init,6)).type != Abyss) command(id,Dir(7));
       }
       else if(init.i > a.i and init.j < a.j){
         if(pos_ok(mou(init,4)) and cell(mou(init,4)).type != Granite and cell(mou(init,4)).type != Abyss) command(id,Dir(3));
       }
       else if(init.i < a.i){
         if(pos_ok(mou(init,2)) and cell(mou(init,2)).type != Granite and cell(mou(init,2)).type != Abyss) command(id,Dir(0));
       }
       else if(init.i > a.i){
         if(pos_ok(mou(init,0)) and cell(mou(init,0)).type != Granite and cell(mou(init,0)).type != Abyss) command(id,Dir(4));
       }
       else if(init.j < a.j){
         if(pos_ok(mou(init,1)) and cell(mou(init,1)).type != Granite and cell(mou(init,1)).type != Abyss) command(id,Dir(2));
       }
       else if(init.j > a.j){
         if(pos_ok(mou(init,3)) and cell(mou(init,3)).type != Granite and cell(mou(init,3)).type != Abyss) command(id,Dir(6));
       }
     }

     if(init.i < a.i and init.j > a.j){
       if(pos_ok(mou(init,6)) and cell(mou(init,6)).type != Granite and cell(mou(init,6)).type != Abyss) command(id,Dir(7));
       else if(init.i < a.i and init.j < a.j){
         if(pos_ok(mou(init,5)) and cell(mou(init,5)).type != Granite and cell(mou(init,5)).type != Abyss) command(id,Dir(1));
       }
       else if(init.i > a.i and init.j > a.j){
         if(pos_ok(mou(init,7)) and cell(mou(init,7)).type != Granite and cell(mou(init,7)).type != Abyss) command(id,Dir(5));
       }
       else if(init.i > a.i and init.j < a.j){
         if(pos_ok(mou(init,4)) and cell(mou(init,4)).type != Granite and cell(mou(init,4)).type != Abyss) command(id,Dir(3));
       }
       else if(init.i < a.i){
         if(pos_ok(mou(init,2)) and cell(mou(init,2)).type != Granite and cell(mou(init,2)).type != Abyss) command(id,Dir(0));
       }
       else if(init.i > a.i){
         if(pos_ok(mou(init,0)) and cell(mou(init,0)).type != Granite and cell(mou(init,0)).type != Abyss) command(id,Dir(4));
       }
       else if(init.j < a.j){
         if(pos_ok(mou(init,1)) and cell(mou(init,1)).type != Granite and cell(mou(init,1)).type != Abyss) command(id,Dir(2));
       }
       else if(init.j > a.j){
         if(pos_ok(mou(init,3)) and cell(mou(init,3)).type != Granite and cell(mou(init,3)).type != Abyss) command(id,Dir(6));
       }
     }

     if(init.i > a.i and init.j < a.j){
       if(pos_ok(mou(init,4)) and cell(mou(init,4)).type != Granite and cell(mou(init,4)).type != Abyss) command(id,Dir(3));
       else if(init.i < a.i and init.j < a.j){
         if(pos_ok(mou(init,5)) and cell(mou(init,5)).type != Granite and cell(mou(init,5)).type != Abyss) command(id,Dir(1));
       }
       else if(init.i > a.i and init.j > a.j){
         if(pos_ok(mou(init,7)) and cell(mou(init,7)).type != Granite and cell(mou(init,7)).type != Abyss) command(id,Dir(5));
       }
       else if(init.i < a.i and init.j > a.j){
         if(pos_ok(mou(init,6)) and cell(mou(init,6)).type != Granite and cell(mou(init,6)).type != Abyss) command(id,Dir(7));
       }
       else if(init.i < a.i){
         if(pos_ok(mou(init,2)) and cell(mou(init,2)).type != Granite and cell(mou(init,2)).type != Abyss) command(id,Dir(0));
       }
       else if(init.i > a.i){
         if(pos_ok(mou(init,0)) and cell(mou(init,0)).type != Granite and cell(mou(init,0)).type != Abyss) command(id,Dir(4));
       }
       else if(init.j < a.j){
         if(pos_ok(mou(init,1)) and cell(mou(init,1)).type != Granite and cell(mou(init,1)).type != Abyss) command(id,Dir(2));
       }
       else if(init.j > a.j){
         if(pos_ok(mou(init,3)) and cell(mou(init,3)).type != Granite and cell(mou(init,3)).type != Abyss) command(id,Dir(6));
       }
     }
     else if(init.i < a.i){
       if(pos_ok(mou(init,2)) and cell(mou(init,2)).type != Granite and cell(mou(init,2)).type != Abyss) command(id,Dir(0));
     }
     else if(init.i > a.i){
       if(pos_ok(mou(init,0)) and cell(mou(init,0)).type != Granite and cell(mou(init,0)).type != Abyss) command(id,Dir(4));
     }
     else if(init.j < a.j){
       if(pos_ok(mou(init,1)) and cell(mou(init,1)).type != Granite and cell(mou(init,1)).type != Abyss) command(id,Dir(2));
     }
     else if(init.j > a.j){
       if(pos_ok(mou(init,3)) and cell(mou(init,3)).type != Granite and cell(mou(init,3)).type != Abyss) command(id,Dir(6));
     }
     else command(id,Dir(0));
   }

   //mou wizzard cap a la posicio a CORRECTE
   void move_wizzard(int id, Pos a){
     Pos init = unit(id).pos;
     if(init.i < a.i){
       if(pos_ok(mou(init,2)) and cell(mou(init,2)).type != Granite and cell(mou(init,2)).type != Rock and cell(mou(init,2)).type != Abyss) command(id,Dir(0));
     }
     if(init.i > a.i){
       if(pos_ok(mou(init,0)) and cell(mou(init,0)).type != Granite and cell(mou(init,0)).type != Rock and cell(mou(init,0)).type != Abyss) command(id,Dir(4));
     }
     if(init.j < a.j){
       if(pos_ok(mou(init,1)) and cell(mou(init,1)).type != Granite and cell(mou(init,1)).type != Rock and cell(mou(init,1)).type != Abyss) command(id,Dir(2));
     }
     else {
       if(pos_ok(mou(init,3)) and cell(mou(init,3)).type != Granite and cell(mou(init,3)).type != Rock and cell(mou(init,3)).type != Abyss) command(id,Dir(6));
       else mou(init,2);
     }
   }

   //Dwarve s'allunya de la posicio a ja que hi ha un enemic
   void run_dwarve(int id, Pos a){// 4 2 0 6 3 1 7 5
     Pos init = unit(id).pos;
     if(init.i < a.i and init.j < a.j){
       if(pos_ok(mou(init,7)) and cell(mou(init,7)).type != Granite and cell(mou(init,7)).type != Rock and cell(mou(init,7)).type !=  Abyss) command(id,Dir(5));
     }
     if(init.i > a.i and init.j > a.j){
       if(pos_ok(mou(init,5)) and cell(mou(init,5)).type != Granite and cell(mou(init,5)).type != Rock and cell(mou(init,5)).type !=  Abyss) command(id,Dir(1));
     }
     if(init.i < a.i and init.j > a.j){
       if(pos_ok(mou(init,4)) and cell(mou(init,4)).type != Granite and cell(mou(init,4)).type != Rock and cell(mou(init,4)).type !=  Abyss) command(id,Dir(3));
     }
     if(init.i > a.i and init.j < a.j){
       if(pos_ok(mou(init,6)) and cell(mou(init,6)).type != Granite and cell(mou(init,6)).type != Rock and cell(mou(init,6)).type !=  Abyss) command(id,Dir(7));
     }
     if(init.i < a.i){
       if(pos_ok(mou(init,0)) and cell(mou(init,0)).type != Granite and cell(mou(init,0)).type != Rock and cell(mou(init,0)).type != Abyss) command(id,Dir(4));
     }
     if(init.i > a.i){
       if(pos_ok(mou(init,2)) and cell(mou(init,2)).type != Granite and cell(mou(init,2)).type != Rock and cell(mou(init,2)).type != Abyss) command(id,Dir(0));
     }
     if(init.j < a.j){
       if(pos_ok(mou(init,3)) and cell(mou(init,3)).type != Granite and cell(mou(init,3)).type != Rock and cell(mou(init,3)).type != Abyss) command(id,Dir(6));
     }
     if(init.j > a.j){
       if(pos_ok(mou(init,1)) and cell(mou(init,1)).type != Granite and cell(mou(init,1)).type != Rock and cell(mou(init,1)).type != Abyss) command(id,Dir(2));
     }
     else command(id,Dir(0));
   }

   //Wizzard s'allunya de la posicio a ja que hi ha un enemic
   void run_wizzard(int id, Pos a){
     Pos init = unit(id).pos;
     if(a.i > init.i) {
       if(pos_ok(mou(init,0)) and cell(mou(init,0)).type !=  Rock and cell(mou(init,0)).type !=  Granite and cell(mou(init,0)).type !=  Abyss) command(id,Dir(4));
     }
     if(a.i < init.i) {
       if(pos_ok(mou(init,2)) and cell(mou(init,2)).type !=  Rock and cell(mou(init,2)).type !=  Granite and cell(mou(init,2)).type !=  Abyss) command(id,Dir(0));
     }
     if(a.j > init.j) {
       if(pos_ok(mou(init,3)) and cell(mou(init,3)).type !=  Rock and cell(mou(init,3)).type !=  Granite and cell(mou(init,3)).type !=  Abyss) command(id,Dir(6));
     }
     if(a.j < init.j) {
       if(pos_ok(mou(init,1)) and cell(mou(init,1)).type !=  Rock and cell(mou(init,1)).type !=  Granite and cell(mou(init,1)).type !=  Abyss) command(id,Dir(2));
     }
     else command(id,Dir(6));
   }

   //Els dwarves es mouen cap als tresors mes propers tenint en compte parets i abismes nomes.
   //Volem que la 1ª tercera part siguin caçadors, la 2ª busquin tresors i la 3ª marquin cel·les
   void move_dwarves(){
     vector<int> K = dwarves(me());
     int n = K.size();
     if(n < 40){
       for(int i = 0; i < n; ++i){ //2ª tercera part dels dwarves busquen tresors. +3ª tercera pq no esta implementada encara
         int id = K[i];

         escape_balrog(unit(id).pos); //primer fugim del balrog si el tenim aprop

         bool b = false;
         Pos enem = check_enemics(unit(id).pos, b,2);
         if(b and unit(cell(enem).id).type != Dwarf and unit(cell(enem).id).type != Wizard /*and unit(cell(enem).id).type != Orc*/)run_dwarve(id,enem); //fugim de les unitats de Sauron
         // else if(unit(id).health <= 50){
         //   move_dwarve(id,bfs_wizards(unit(id).pos));
         // }
         else {
           move_dwarve(id,bfs_dw_enem(unit(id).pos));
         }
       }
     }
     else{
       for(int i = 0; i < n-5; ++i){ //2ª tercera part dels dwarves busquen tresors. +3ª tercera pq no esta implementada encara
         int id = K[i];

         escape_balrog(unit(id).pos); //primer fugim del balrog si el tenim aprop

         bool b = false;
         Pos enem = check_enemics(unit(id).pos, b,2);
         if(b and unit(cell(enem).id).type != Dwarf and unit(cell(enem).id).type != Wizard /*and unit(cell(enem).id).type != Orc*/)run_dwarve(id,enem); //fugim de les unitats de Sauron
         // else if(unit(id).health <= 50){
         //   move_dwarve(id,bfs_wizards(unit(id).pos));
         // }
         else {
           move_dwarve(id,bfs_dw_enem(unit(id).pos));
         }
       }
       for(int i = n-5; i < n; ++i){
         int id = K[i];

         escape_balrog(unit(id).pos); //primer fugim del balrog si el tenim aprop

         bool b = false;
         Pos enem = check_enemics(unit(id).pos, b,2);
         if(b and unit(cell(enem).id).type != Dwarf and unit(cell(enem).id).type != Wizard /*and unit(cell(enem).id).type != Orc*/)run_dwarve(id,enem); //fugim de les unitats de Sauron
         // else if(unit(id).health <= 50){
         //   move_dwarve(id,bfs_wizards(unit(id).pos));
         // }
         else {
           move_dwarve(id,tresor_proper(unit(id).pos));
         }
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
       Pos enem = check_enemics(unit(id).pos, b,2);
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
