#include<iostream>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include <typeinfo>
#include <vector>
using namespace std;
#define MAXCHARLEN 10
#define GSIZE 101
#define INPUTNAME "/Users/josephvalentine/Documents/code/c/ecen_521/graph1.txt"

// Graph class represents a undirected graph
// using adjacency list representation
class Graph
{
    int numVertices; 
    vector <char> moves; //array of moves made to get to state city or edge???
    vector <char> state; //state of solution (cities that have been visited at least once)
    bool finished;
    // adj matrix
    map<char, map<char, int> > vertices;
    // backtrack dfs
    //void backtrack(move[], int k, vector <char> state);
    bool isASolution(int k);
    void processSolution(int k);
    // void constructCandidates(move[], int k, stateCandidates[], int numCandidates);
    // void makeMove(move[], int k, vector <char> state);
    // void unmakeMove(move[], int k, vector <char> state);
    void printState();


public:
    Graph(int numVertices);   // Constructor
    void addEdge(char city1, char city2, int dist);
    void backTrackTop();
   
};

Graph::Graph(int numVertices)
{
    this->numVertices = numVertices;
    this->finished = false;
}
 
// method to add an undirected edge using adjacency list
void Graph::addEdge(char city1, char city2, int dist)
{
    vertices[city1][city2] = dist;
    vertices[city2][city1] = dist;
    cout << city1 << city2 << vertices[city1][city2] << std::endl;
}

//method to start a backtrack search of the graph
void Graph::backTrackTop(){
    this->vertices.push_back('A'); //init the state
    backtrack(-1);
}

void Graph::printState(){
    cout << "solution:" << endl;
    for(int i=0; i < this->state.size(); i++){
      cout << this->state[i] << " ";
    }
    cout << endl;
  }

void Graph::backtrack(int k){
    vector <char> stateCandidates;
    int numCandidates;

    if(isASolution(k)){
        processSolution(k);
    } else {
        k++;
        stateCandidates = constructCandidates(k, numCandidates);
        for(int i=0; i<numCandidates; i++){
            //move[k] = candidate[i];
            move.push_back(candidate[i]);
            makeMove(k);
            backtrack(k);
            unmakeMove(k);
            if(this->finished)
                return;
        }
    }
};
    
bool Graph::isASolution(int k){
    if (this->state.size() == this->numVertices){
        return true;
    } else {
        return false;
    }
};

void Graph::processSolution(int k){
    printState();
    //if this is the only solution you want finished = true;
};

void Graph::constructCandidates(int k, int numCandidates){};

void Graph::makeMove(int k{

};

void Graph::unmakeMove(int k){};


// void fillGraphFromFile(Graph g, std::string value, int count, int size){
// 	string cityName;
    
// 	std::string delimiter = " ";

//     // size_t pos = 0;
//     std::string token;

//     for( int i=0; i++; i<count+2){
//         if(i==0){
//             token = value.substr(0, value.find(delimiter));
//             cityName = token;
//             value.erase(0, value.find(delimiter) + delimiter.length()); 
//         }
       
//         token = value.substr(0, value.find(delimiter));
//         v = stoi(token);
//         value.erase(0, value.find(delimiter) + delimiter.length());

//         g.addEdge(v1,v2);
//     }
	    
//   }



int main()
{
  
  //   string filename = INPUTNAME;
  //  	ifstream myfile (filename);
  //  	std::string value;
  //   int gSize;

  // //read file
  //  if (myfile.is_open()){

  //   //get 1st 3 lines
  //   getline(myfile, value);
  //   gSize = stoi(value);
  //   Graph g(gSize); //init the graph

  //   getline(myfile, value); //throw away
  //   getline(myfile, value); //throw away

  //   //get the rest
  //   int count = 0;
  //   while(getline(myfile, value)){

  //     fillGraphFromFile(g, value, count, gSize);
  //     count++; 
  //   }
  //   myfile.close();
  // } else {
  // 	std::cout << "Unable to open file ";
  // }

    // 8
    //   A B C D E F G H
    // A 0
    // B 6 0
    // C 5 4 0
    // D - - 2 0
    // E 7 - - 8 0
    // F 9 - - - 3 0
    // G - - 9 - - - 0
    // H - - - 7 - - - 0

    Graph g(8);
    g.addEdge('A','B',6);
    g.addEdge('A','C',5);
    g.addEdge('A','E',7);
    g.addEdge('A','F',9);
    g.addEdge('B','C',4);
    g.addEdge('C','D',2);
    g.addEdge('C','G',9);
    g.addEdge('D','E',8);
    g.addEdge('D','H',7);
    g.addEdge('E','F',3);

    
    return 0;
}