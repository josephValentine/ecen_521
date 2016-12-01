#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>

#define MAXNUMSETS 200
#define MAXSETVALUE 100
#define PATH "/Users/josephvalentine/Documents/code/c/ecen_521/s-k-20-30.txt"
#define READFROMFILE 1
#define MAXCHARLENGTH 100

struct subsetSize{ 
  int size;
  int id;
};

int sizeOfBestSolution;
int numberOfSubsets;
int universeLength;
//struct subsetSizeId SizeOfEachSubset[MAXNUMSETS];//store the length of each given set
struct subsetSize sub[MAXNUMSETS];//store the length of each given set
int previousRandVal = 1;
int subsetArrays[MAXNUMSETS][MAXSETVALUE]={0};
bool subsetArrayMatrix[MAXNUMSETS][MAXSETVALUE]={false}; //store which values are included in each set
int totalFromAllSubsets[MAXSETVALUE]={0}; //store how often each integer occurs given each value in each subset this will be usefull for pruning

int cmpfunc(const void *a, const void *b){
  const struct subsetSize *p1 = (struct subsetSize *)a;
  const struct subsetSize *p2 = (struct subsetSize *)b;
  if(p1->size > p2->size) return -1;
  if(p1->size < p2->size) return 1;
  return 0;
}

int myRand(){
  struct timeval tv;
  gettimeofday(&tv,NULL);
  int seed = tv.tv_usec;
  srand(seed);
  int x = rand();
  previousRandVal = 104729*previousRandVal + x;
  x = previousRandVal % (100);
  return x;
}

void printArray(int array[], int size){
  printf("array----------------\n");
  for(int j = 0; j < size; j++){
      printf("%d ", array[j]+1);
  }
  printf("\n---------------------\n");
}

void printArrayStruct(struct subsetSize array[], int size){
  printf("array----------------\n");
  for(int j = 0; j < size; j++){
      printf("(id:%d ,size:%d) ", array[j].id,array[j].size);
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

void printArray2(bool array[][MAXSETVALUE],int size1){
  printf("array2----------------\n");
  for(int j = 0; j < size1; j++){
    for(int i = 1; i <= universeLength; i++){
      printf("%d", array[j][i]);
    }
    printf("\n");
  }
  printf("---------------------\n");
}

void intprintArray2(int array[][MAXSETVALUE],int size1){
  printf("array2----------------\n");
  for(int j = 0; j < size1; j++){
    for(int i = 0; i <= universeLength; i++){
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
  printf("solution found: these are the lists:\n");
  printArray(moves,k+1);

  sizeOfBestSolution=k;
}

/*-----------------------------------------------------
  test whether the current solution is valid. there may 
  be a more efficient way of doing this...
------------------------------------------------------*/
bool is_a_solution(int moves[], int k, int n){
  // printf("in is_a_solution, k is:%d\n",k);
  // printArray(moves,k+1);
  bool solution;
  for(int i=1; i <= universeLength; i++){ //for all values that may be needed in universal set
    solution = false;//guilty till proven otherwise
    for(int j=0; j <= k; j++){ //for each move we have made (each set we have chosen)
      int setId = moves[j];
      //printf("setID %d for move: %d\n", setId, j);
      if(subsetArrayMatrix[setId][i]){//we have the required value in a chosen set
        solution = true;
      }
    }
    if(!solution)
      return false;
    
  }
  return true;
}

/*-----------------------------------------------------
  order the recursion. i think this is where we will 
  want to call our pruning "checker" functions. right now
  it will just recurse down with any set that we havent
  already added yet
------------------------------------------------------*/
void construct_candidates(int moves[], int k, int n, int candidates[], int *numCandidates){
   // printf("in construct_candidates, k is:%d\n",k);

  int i;                  
  bool used[numberOfSubsets];          
  for (i=0; i<numberOfSubsets; i++){
    used[i] = false;
  } 
  for (i=0; i<k; i++){
     //printf("k:%d\n",k);
     used[ moves[i] ] = true;//mark the sets we have already used
  }

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
  main recursive function:
  moves[]: list of sets selected in current path
  k: depth
  n: max depth
------------------------------------------------------*/
bool finished = false; /* found all solutions yet? */
void backtrack(int moves[], int k, int n)
{
  // sleep(1);
  // printf("level/k: %d\n",k);
  int candidates[numberOfSubsets];/* candidates for next position */
  int numCandidates;
  int i;/* counter */

  if(k >= sizeOfBestSolution){
    //ignore it
  } else if (is_a_solution(moves,k,n)){
    process_solution(moves,k);
  } else {
      k = k+1;
      construct_candidates(moves, k, n, candidates, &numCandidates);
      // printf("candidates\n");
      // printArray(candidates,numCandidates);
      for (i=0; i<numCandidates; i++) { 
        moves[k] = candidates[i];//next move is ordered by construct_candidates
        // printf("new move is;%d\n",candidates[i]);
        backtrack(moves, k, n);
        
      }

  }
}

/*-----------------------------------------------------
  start the recursion.  we require an initial pick
  of our list of sets
------------------------------------------------------*/
void set_cover(int n){
  //n is the number of set # we have recursed through
  int moves[numberOfSubsets]; //moves made to get to the current state of our solution
  int k=-1; //move iterator
  //moves[0]=0; //pick the initial move
  
  //pick initial moves-------
  int count=0;
  for(int j = 0; j < numberOfSubsets; j++){
      if(totalFromAllSubsets[j]==1){
        
        moves[count]=j;//pick all the integers only represented in one place
        k++;
        count++;
      }
  }
  
  printf("ones that we have added\n");
  printArray(moves,k+1);
  backtrack(moves, k, n);
}


int readInputFile(int array[MAXNUMSETS][MAXSETVALUE], char * filename){
  FILE *stream;
  stream = fopen(filename, "r");

    //read file
   if (stream){

    int limiter = 0;
    int lineCount = 0;
    char line[MAXCHARLENGTH];
    while(fgets(line, MAXCHARLENGTH, stream)){
      char * pch;
      //printf ("Splitting string into tokens:\"%s", line);
      int rowCount = 0;
      pch = strtok (line," ");
      
      if (limiter < 1){
        universeLength = atoi(pch);
      }
      if (limiter == 1){
        numberOfSubsets = atoi(pch);
      }
      if(limiter >1){
        while (pch != NULL)
        {
          //printf ("%s\n",pch);
          //printf ("linecount:%i ,rowCount:%i\n",lineCount, rowCount);
          int num = atoi(pch);
          //if(printout) printf("opp there it is: %i\n", num);
          array[lineCount][rowCount] = num;
          subsetArrayMatrix[lineCount][num] = 1;
          //printf("worked\n");
          totalFromAllSubsets[num-1] = totalFromAllSubsets[num-1] +1;
          rowCount++;
          pch = strtok (NULL, " \r\n");
        //if(BiggestSubset < rowCount) {printf("newLongest:%d\n",rowCount); BiggestSubset = rowCount;}
        }
        sub[lineCount].size = rowCount;
        sub[lineCount].id= lineCount;
        lineCount++; 
      }
    
      limiter++;    
    }
    fclose(stream); 
    return 1;
  } else {
    printf("\nunable to open file\n");  
    return 0; 
  }
}


int main()
{
  if(READFROMFILE){
    char * filename = PATH;
    readInputFile(subsetArrays, filename);
    intprintArray2(subsetArrays,numberOfSubsets);
    
    //---------
    //needed:
    //function to create subsetarraymatrix from subset arrays
    //---------
  } else {
    universeLength=3;
    numberOfSubsets=3;
    // SizeOfEachSubset[0]=1;
    // SizeOfEachSubset[1]=1;
    // SizeOfEachSubset[2]=2;
    subsetArrayMatrix[0][1]=true;
    subsetArrayMatrix[1][3]=true;
    subsetArrayMatrix[2][1]=true;
    subsetArrayMatrix[2][2]=true;
    totalFromAllSubsets[1]=2;
    totalFromAllSubsets[2]=1;
    totalFromAllSubsets[3]=1;
  }
  printf("printing the subset array matrix (row represents the subset, col represents the integer, 1 means it exists . . .\n");
  printArray2(subsetArrayMatrix,numberOfSubsets);
  printf("sub 1 from these...\n");
  printArray(totalFromAllSubsets,universeLength);
  
  sizeOfBestSolution=numberOfSubsets;
  printArrayStruct(sub,numberOfSubsets);
  qsort(sub, numberOfSubsets, sizeof(struct subsetSize), cmpfunc);
  printArrayStruct(sub,numberOfSubsets);
  set_cover(numberOfSubsets);//pass in the max allowable depth
  
  return 0;
}