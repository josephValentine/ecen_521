#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define NMAX 100
#define MAXCANDIDATES 100
#define N 3
#define MAXSOLUTIONS 10

char string[5]={'\0','d','a','d','t'};
char solutionset[MAXSOLUTIONS][N]={0};
int ssCount=0;

int cmpfunc (const void * a, const void * b)
{
   return ( *(char*)a - *(char*)b );
}

void printArray(char array[]){
  printf("array----------------\n");
  for(int j = 0; j < N; j++){
      printf("%c", array[j]);
  }
  printf("---------------------\n");
}

void printArray2(char array[][N]){
  printf("array2----------------\n");
  for(int j = 0; j < MAXSOLUTIONS; j++){
    for(int i = 0; i < N; i++){
      printf("%c", array[j][i]);
    }
    printf("\n");
  }
  printf("---------------------\n");
}

void process_solution(int a[], int k){

  char solution[N];
  int i;  /* counter */
  int j;
  for (i=1; i<=k; i++){
    solution[i-1]=string[a[i]];
  } 

  int included=0;
  bool print=true;
  for(i=0;i<MAXSOLUTIONS;i++){
    for(j=0;j<N;j++){
      if(solutionset[i][j] == solution[j])
        included++;
    }
    if(included>=N){
      print=false;
      break;
    }
    included=0;//reset
  }

  if(print){
    for(i=0;i<N;i++){
      printf("%c",solution[i]);
      solutionset[ssCount][i]=solution[i];
    }
    ssCount++;
     printf("\n");
  }
 
}

bool is_a_solution(int a[], int k, int n){
  return (k == n);
}

void construct_candidates(int a[], int k, int n, int c[], int *ncandidates){
  //printf("in construct_candidates\n");
  int i;                       /* counter */
  bool in_perm[NMAX];          /* who is in the permutation? */
  for (i=1; i<NMAX; i++){
    in_perm[i] = false;
  } 
  //printf("here1\n");
  for (i=0; i<k; i++){
     //printf("k:%d\n",k);
     in_perm[ a[i] ] = true;
  }

  //printf("here\n");
  *ncandidates = 0;
  for (i=1; i<=n; i++){
    if (in_perm[i] == false) {
     // printf("i:%d, *ncandidates:%d\n", i,*ncandidates);
      c[ *ncandidates] = i;
      *ncandidates = *ncandidates + 1;
    }
  }

}


void make_move(int a[], int k, int n){
  }

void unmake_move(int a[], int k, int n){
 }

bool finished = false; /* found all solutions yet? */
char temp = '#';
void backtrack(int a[], int k, int input)
{

  int c[MAXCANDIDATES];/* candidates for next position */
  int ncandidates;/* next position candidate count */
  int i;/* counter */

  if (is_a_solution(a,k,input)){
    process_solution(a,k);
  } else {
      k = k+1;
      construct_candidates(a,k,input,c,&ncandidates);
      for (i=0; i<ncandidates; i++) {
        a[k] = c[i];
        backtrack(a,k,input);
        
      }

  }
}

void generate_permutations(int n){
  int a[NMAX]; //moves made to current state
  //k is move index
  backtrack(a,0,n);
}

  int main()
  {
    qsort(string, 4, sizeof(char), cmpfunc);
   // printf("%c%c%c%c\n", string[0],string[1],string[2],string[3]);
    generate_permutations(N);

    return 0;
  }