#include<iostream>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include <typeinfo>
#include <vector>
#include <math.h>
using namespace std;

#define INPUTNAME "/Users/josephvalentine/Documents/code/c/ecen_521/dp3/map25.txt"
#define NUMCITIES 25
#define BOUNDARY 100
#define HIGH_TEMP 1000
#define BPENALTY 10*HIGH_TEMP
#define LOW_TEMP 1
#define EMIN 10
#define ITERATE_NUM 10000
#define K 0.09
#define COOLING_FACTOR 0.999
#define DEBUG 0

  //init the global vars
 int vertices[NUMCITIES][NUMCITIES];
 int fNext[NUMCITIES][NUMCITIES];
 int choseWorse=0;
 
// method to add an undirected edge using adjacency list
void addEdge(int city1, int city2, int dist)
{
    vertices[city1][city2] = dist;
    vertices[city2][city1] = dist;
    if(DEBUG)
      cout <<"adding " <<city1 << "to "<<city2 << "with weight "<< vertices[city1][city2] << std::endl;
}

void printVertices(){
  cout << vertices[0][1] << std::endl;
  cout << vertices[1][0] << std::endl;
    cout << "matrix:" << endl;
    for(int i=0; i < NUMCITIES; i++){
      for(int j=0; j < NUMCITIES; j++){
       cout << vertices[j][i] << " ";
      }
      cout << endl;
    }
    cout << endl;
}

void printVec(vector<int> vec){
  for(int i=0; i<vec.size(); i++){
    cout << vec[i] << " ";
  }
  //cout << endl;
}

void initMatrix(){
    for(int i=0; i < NUMCITIES; i++){
      for(int j=0; j < NUMCITIES; j++){
       vertices[i][j] = BOUNDARY;
      }
    }

    for(int i=0; i < NUMCITIES; i++){
      for(int j=0; j < NUMCITIES; j++){
       fNext[i][j] = j;
      }
    }
}
/*---------------------------------------------------------------------------
  use floyd warshall to compute shortest path between any 2 cities
 ---------------------------------------------------------------------------*/
void floyd(){
 int throughK; //dist through vertex k

 for(int k=0; k<NUMCITIES; k++){
    for(int i=0; i<NUMCITIES; i++){
      for(int j=0; j<NUMCITIES; j++){
        throughK = vertices[i][k] + vertices[k][j];
        if(throughK < vertices[i][j]){
          vertices[i][j] = throughK;
          fNext[i][j] = fNext[i][k];
        }
      }
    }
 }
}
/*---------------------------------------------------------------------------
what is the shortest path from i to j?
 ---------------------------------------------------------------------------*/
vector <int> floydPath(int i, int j){
  vector <int> path;
  //path.push_back(i);
  while(i != j){
    i = fNext[i][j];
    path.push_back(i);
  }
  return path;
}

int findEnergy(vector<int> state){
  int energy = 0;
  int cost=0;
  for(int i = 0; i < state.size()-1; ++i){
    int city1 = state[i];
    int city2 = state[i+1];
    cost = vertices[city1][city2];
    energy += cost;
  }
  return energy;
}

// int tempDependentCost(vector<int> state, double temp){
// int energy = 0;
// int cost = 0;
//   for(int i = 0; i < state.size()-1; ++i){
//     int city1 = state[i];
//     int city2 = state[i+1];
//     //cout << "adding:" << city1 << city2 << vertices[city1][city2] << endl;
//     cost = vertices[city1][city2];
//     if(cost == -1){
//       cost = BPENALTY/temp;
//     }
//     energy += cost;
//   }
//   //cout << "energy:" << energy;
//   return energy;
// }


vector<int> findNeighbor(vector<int> state){//dumb version allows invalid solutions and only swaps neighbors
  int limit = state.size() - 2;
  int city1 = rand() % limit + 1;
  if(DEBUG > 1){
    cout<<"before state"<<endl;
    printVec(state);
  }
  int temp = state[city1];
  state[city1]=state[city1+1];
  state[city1+1]=temp;
  if(DEBUG > 1){
    cout<<"after swap"<<endl;
    printVec(state);
  }
  return state;
  }


vector<int> initialState(){
  vector<int> initState;
  for(int i=0; i<NUMCITIES; i++){
    initState.push_back(i);
  }
  if(DEBUG){
    cout << "initial State" <<endl;
    printVec(initState);
  }
  return initState;
}

void printEntireState(vector <int> state){
  cout<<"0 ";//initial city
  for(int i=0; i<state.size()-1; i++){
    printVec(floydPath(state[i],state[i+1]));
  }
}

void simulatedAnealing(){
  double temp = HIGH_TEMP;
  vector<int> state = initialState();
  int energy = findEnergy(state);

  int relEnergy ;
  vector<int> S_new;
  int E_new;

  vector<int> S_best = state;
  int E_best = energy;
  int iterCount = 0;

  while( temp > LOW_TEMP && energy > EMIN){
    for(int i = 0; i < ITERATE_NUM; i++){
      S_new = findNeighbor(state); 
      E_new = findEnergy(S_new);

      if( E_new < energy || exp((double)(energy - E_new)/(K*temp)) >= ((double) rand() / (RAND_MAX))){
        if(E_new > energy){
          choseWorse++;
        }
        state = S_new;
        energy = E_new;
        if(DEBUG > 1){
          cout<<"we have been accepted---------------------------"<<endl;
          cout << "energy " << energy << " E_best" << E_best<<endl;
        }
        if(energy < E_best){
          S_best = state;
          E_best = energy;
          if(DEBUG){
            cout << "better solution found --------------------------------------------------"<<endl;
            cout<<endl<<endl;
            printEntireState(state);
            cout<<" ("<<E_best<<") "<<endl;
          }
        }

      }
      iterCount++;
    }
    temp = temp*COOLING_FACTOR;
  }
  if(DEBUG)
    cout << "chose worse: " << choseWorse <<"times out of "<<iterCount<<"iterations"<<endl;
  cout<<E_best<<endl;
}

//input format-------------------------------------


//   10
//   A B C D E F G H I J
// A 0
// B 6 0
// C 5 4 0
// D - - 2 0
// E 7 - - 8 0
// F 9 - - - 3 0
// G - - 9 - - - 0
// H - - - 7 - - 6 0
// I - - - - 8 - 7 - 0
// J - - 4 - - - - - 8 0

void fillGraphFromFile(std::string value, int count){
	string cityName;
	std::string delimiter = " ";
  int v;

  // size_t pos = 0;
  std::string token;

  for( int i=0; i<count+2; i++){
      if(i==0){
          token = value.substr(0, value.find(delimiter));
          cityName = token;
          value.erase(0, value.find(delimiter) + delimiter.length()); 
      }else{
      token = value.substr(0, value.find(delimiter));
      if(token != "-")
        v = stoi(token);
      else
        v = BOUNDARY;
      value.erase(0, value.find(delimiter) + delimiter.length());
    
      addEdge(count,i-1,v);
      }
      
  }
	    
}

int main()
{

    initMatrix();

    string filename = INPUTNAME;
   	ifstream myfile (filename);
   	std::string value;

  //read file
   if (myfile.is_open()){

    //get 1st 3 lines
    getline(myfile, value);
    getline(myfile, value); //throw away
   // getline(myfile, value); //throw away

    //get the rest
    int count = 0;
    while(getline(myfile, value)){

      fillGraphFromFile(value, count);
      count++; 
    }
    myfile.close();
  } else {
  	std::cout << "Unable to open file ";
  }
  if(DEBUG)
    printVertices();
  floyd();
  if(DEBUG)
    printVertices();
  simulatedAnealing();

    return 0;
}