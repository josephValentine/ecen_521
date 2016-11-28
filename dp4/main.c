#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define NUMSETS 10
#define MAXSETVALUE 10

int setLengths[NUMSETS]; //store the length of each given set
bool setCoverMatrix[NUMSETS][MAXSETVALUE]; //store which values are included in each set
int valueMultiplicity[MAXSETVALUE]; //store how often a value occurs given each value in each subset
bool currSet[MAXSETVALUE]; //which values do we have in our concatenated set?

void printArray(char array[], int size){
  printf("array----------------\n");
  for(int j = 0; j < size; j++){
      printf("%c", array[j]);
  }
  printf("---------------------\n");
}

void printArray2(char array[][MAXSETVALUE]){
  printf("array2----------------\n");
  for(int j = 0; j < NUMSETS; j++){
    for(int i = 0; i < MAXSETVALUE; i++){
      printf("%c", array[j][i]);
    }
    printf("\n");
  }
  printf("---------------------\n");
}

/*-----------------------------------------------------
  print the solution etc.
------------------------------------------------------*/
void process_solution(int moves[], int k){

}

/*-----------------------------------------------------
  test whether the current solution is valid
------------------------------------------------------*/
bool is_a_solution(int moves[], int k, int state){
  return (k == state);
}

/*-----------------------------------------------------
  order the recursion. i think this is where we will 
  want to call our pruning "checker" functions.
------------------------------------------------------*/
void construct_candidates(int moves[], int k, int state, int c[], int *ncandidates){
  
}

/*-----------------------------------------------------
  main recursive function
------------------------------------------------------*/

bool finished = false; /* found all solutions yet? */
void backtrack(int moves[], int k, int state)
{

  int c[MAXCANDIDATES];/* candidates for next position */
  int ncandidates;/* next position candidate count */
  int i;/* counter */

  if (is_a_solution(moves,k,state)){
    process_solution(moves,k);
  } else {
      k = k+1;
      construct_candidates(moves, k, state, c, &ncandidates);
      for (i=0; i<ncandidates; i++) {
        moves[k] = c[i];//next move is next candidate
        backtrack(moves, k, state);
        
      }

  }
}

/*-----------------------------------------------------
  start the recursion
------------------------------------------------------*/
void set_cover(int state){
  int moves[NMAX]; //moves made to current state
  int k=0; //move iterator
  backtrack(moves, k, state);
}

int main()
{
  set_cover(N);
  return 0;
}