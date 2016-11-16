#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
// #include <math.h>

// #define numberToFit 6\
// #define min_Val .01
// #define printDebug 0
#define maxCharLength 10
#define maxNumberOfEdges 10
// #define runAllLists 1 //if 0 it will only run the first list in the input file
// //#define inputName "C:\\Workspace\\C_Workplace\\DesignProblem2\\manystacks.txt"
#define inputName "/Users/josephvalentine/Documents/code/c/ecen_521/graph1.txt"

int numEdges;
int numNodes;
//extract nodes
// void extractNodes(int arrayToBuild[numNodes],int arrayToSearch[numEdges][2]){
// 	int count = 0;
// 	for (int i = 0 ; i < numEdges ; i++){
// 		for(int j = 0; j < 2; j++){
// 			//printf("%d ",   arrayToSearch[i][j]);
// 			bool add = true;
// 			for(int k = 0; k < numNodes; k++){
// 				if(arrayToSearch[i][j] == arrayToBuild[k]){
// 					//printf(" dup ");
// 					add = false;
// 				}

// 			}
// 			if(add){
// 				//printf("adding\n");
// 				arrayToBuild[count] = arrayToSearch[i][j];
// 				count++;
// 			}
// 		}
// 	} 
// }

void top_dfs(int Gv[numNodes][2], int G[numEdges][2]){
	int P[maxNumberOfEdges]={0};
	int L[maxNumberOfEdges]={0};

	for(int i=0; i<numNodes; i++){
		if(Gv[i][0] == 0){//discovered == false
			P[i] = null;
			L[i] = 1;
			Gv[i][0]=1;//discovered = true
			dfs(G,i);
		}
	}
}

void dfs(int G[numEdges][2], node){
	preprocess(node);
	int adjacents[][];
	int numAdjacents;
	findAdjacentNodes(adjacents, node);
	for(int i=0; i< numAdjacents; i++){
		if(adjacents[i][0]==0){//discovered is false
			P[]
		}
	}


}

void initArray(int array[numNodes][2]){
	for (int i = 0 ; i < numNodes ; i++){
		for(int j = 0; j < 2; j++){
			array[i][j]=0;
		}
	} 
}
void printArray(int array[numNodes]){
	for(int j = 0; j < numNodes; j++){
			printf("%d\n", array[j]);
	}
}
void print2dArray(int array[maxNumberOfEdges][2], int dim1, int dim2){
	for (int i = 0 ; i < dim1 ; i++){
		printf("( ");
		for(int j = 0; j < dim2; j++){
			printf("%d ",   array[i][j]);
		}
		printf(")\n");
	} 
}

int readInputFile(int G[maxNumberOfEdges][2], char * filename){
	FILE *stream;
	stream = fopen(filename, "r");

  	//read file
   if (stream){

    int lineCount = 0;
    char line[maxCharLength];
    while(fgets(line, maxCharLength, stream)){
	 	char * pch;
	 	printf ("Splitting string \"%s\" into tokens:\n", line);
	 	int colCount = 0;
	 	pch = strtok (line," ");
	 	if(lineCount == 0){
	 		numEdges = atoi(pch);
	 	}
	 	else if(lineCount == 1){
	 		numNodes = atoi(pch);
	 	} else{
	 		while (pch != NULL){
		    	printf ("%s\n",pch);
		    	G[lineCount-2][colCount] = atoi(pch);
		    	colCount++;
		    	pch = strtok (NULL, " \r\n");
	  		}
	 	}

    	lineCount++; 
    }
    fclose(stream);
    return 1;
  } else {
  	printf("\nunable to open file\n");
  	return 0;
  }
}

int main(void)
{	
	char * filename = inputName;
	int G[maxNumberOfEdges][2];

	//read input file
	if(!readInputFile(G, filename)) return 0;
	print2dArray(G, maxNumberOfEdges, 2);
	int Gv[numEdges][2]; //index is node number, first in second dim is discoverd, second is processed
	int P[maxNumberOfEdges];
	int L[maxNumberOfEdges];
	initArray(Gv);
	print2dArray(Gv, numEdges, 2);
	
    return 0;
}