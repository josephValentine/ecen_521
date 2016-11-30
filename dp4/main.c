#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define NUMSETS 3
#define MAXSETVALUE 4

int setLengths[NUMSETS]={0}; //store the length of each given set
bool setCoverMatrix[NUMSETS][MAXSETVALUE]={false}; //store which values are included in each set
int valueMultiplicity[MAXSETVALUE]={0}; //store how often a value occurs given each value in each subset
bool currSet[MAXSETVALUE]={0}; //which values do we have in our concatenated set?
bool universe[4]={false, true, true, true}; //which values (represented by their indexes) do we need

void printArray(int array[], int size){
  printf("array----------------\n");
  for(int j = 0; j < size; j++){
      printf("%d", array[j]);
  }
  printf("\n---------------------\n");
}

void boolprintArray(bool array[], int size){
  printf("array----------------\n");
  for(int j = 0; j < size; j++){
      printf("%d", array[j]);
  }
  printf("\n---------------------\n");
}

void printArray2(bool array[][MAXSETVALUE]){
  printf("array2----------------\n");
  for(int j = 0; j < NUMSETS; j++){
    for(int i = 0; i < MAXSETVALUE; i++){
      printf("%d", array[j][i]);
    }
    printf("\n");
  }
  printf("---------------------\n");
}

/*-----------------------------------------------------
  print the solution etc.
------------------------------------------------------*/
void process_solution(int moves[], int k){
  printf("these are the lists:\n");
  printArray(moves,NUMSETS);
}

/*-----------------------------------------------------
  test whether the current solution is valid
------------------------------------------------------*/
bool is_a_solution(int moves[], int k, int n){
  printf("in is_a_solution, k is:%d\n",k);
  printArray(moves,k+1);
  boolprintArray(universe,4);
  bool solution;
  for(int i=0; i < MAXSETVALUE; i++){ //for all values that may be needed in universal set
    if(universe[i]){//we need this value in our list of sets
      solution = false;//guilty till proven otherwise
      for(int j=0; j < k; j++){ //for each move we have made (each set we have chosen)
        int setId = moves[j];
        //printf("setID %d\n", setId);
        if(setCoverMatrix[setId][i]){//we have the required value in a chosen set
          solution = true;
        }
      }
      if(!solution)
        return false;
    }
  }
  return true;
}

/*-----------------------------------------------------
  order the recursion. i think this is where we will 
  want to call our pruning "checker" functions.
------------------------------------------------------*/
void construct_candidates(int moves[], int k, int n, int candidates[], int *numCandidates){
    printf("in construct_candidates, k is:%d\n",k);

  // printf("in construct_candidates\n");
  // *numCandidates = 0;
  // for (int i=1; i<=n; i++){
  //     candidates[ *numCandidates] = i;
  //     *numCandidates = *numCandidates + 1;
  //}

  int i;                  
  bool used[NUMSETS];          
  for (i=0; i<NUMSETS; i++){
    used[i] = false;
  } 
  printf("here1\n");
  for (i=0; i<k; i++){
     //printf("k:%d\n",k);
     used[ moves[i] ] = true;//mark the sets we have already used
  }

  printf("here\n");
  *numCandidates = 0;
  for (i=0; i<n; i++){
    if (used[i] == false) {
     // printf("i:%d, *ncandidates:%d\n", i,*ncandidates);
      candidates[ *numCandidates] = i;
      *numCandidates = *numCandidates + 1;
    }
  }
}

/*-----------------------------------------------------
  main recursive function
------------------------------------------------------*/

bool finished = false; /* found all solutions yet? */
void backtrack(int moves[], int k, int n)
{
  printf("level/k: %d\n",k);
  int candidates[NUMSETS];/* candidates for next position */
  int numCandidates;
  int i;/* counter */

  if (is_a_solution(moves,k,n) || k > 4){
    process_solution(moves,k);
  } else {
      k = k+1;
      construct_candidates(moves, k, n, candidates, &numCandidates);
      for (i=0; i<numCandidates; i++) {
        moves[k] = candidates[i];//next move is next candidate
        printf("new move is;%d\n",candidates[i]);
        backtrack(moves, k, n);
        
      }

  }
}

/*-----------------------------------------------------
  start the recursion
------------------------------------------------------*/
void set_cover(int n){
  //n is the number of set # we have recursed through
  int moves[NUMSETS]; //moves made to current state
  int k=0; //move iterator
  moves[0]=0; //pick the initial move
  backtrack(moves, k, n);
}

int main()
{
  setLengths[0]=1;
  setLengths[1]=1;
  setLengths[2]=2;
  setCoverMatrix[0][1]=true;
  setCoverMatrix[1][3]=true;
  setCoverMatrix[2][1]=true;
  setCoverMatrix[2][2]=true;
  valueMultiplicity[1]=2;
  valueMultiplicity[2]=1;
  valueMultiplicity[3]=1;

  bool currSet[MAXSETVALUE]; //which values do we have in our concatenated set?
printArray2(setCoverMatrix);
  set_cover(5);//3 cause max num of sets...
  
  return 0;
}