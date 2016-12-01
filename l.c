#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>

//#define inputName "C:\\Workspace\\C_Workplace\\DesignProblem4\\DataSets\\s-X-12-6.txt"
#define inputName "D:\\DPrograms\\CodeLite\\CWorkspace\\DesignProblem4\\datasets\\DataSets\\s-X-12-6.txt"
#define printout 1

int previousRandVal = 1;
int maxNumberOfLists = 50;
int maxCharLength = 50;
int characterListLength = 1;
int subsetListLength = 1;

int BestcurPath[60];

int SubsetArrays[50][50];
int SizeOfEachSubset[100];
int TotalOfAllSubsets[100];
int BiggestSubset = 8;

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


int readInputFile(int arrays_to_organize[maxNumberOfLists][maxCharLength], char * filename){
	FILE *stream;
	stream = fopen(filename, "r");

  	//read file
   if (stream){

	int limiter = 0;
    int lineCount = 0;
    char line[maxCharLength];
    while(fgets(line, maxCharLength, stream)){
	 	char * pch;
	 	//printf ("Splitting string into tokens:\"%s", line);
	 	int rowCount = 0;
		
		pch = strtok (line," ");
		
	if (limiter < 1){
		characterListLength = atoi(pch);
		//if(printout) printf("opp there it is: %i\n", characterListLength);
		}
	if (limiter == 1){
		subsetListLength = atoi(pch);
		//if(printout) printf("opp there it is: %i\n", subsetListLength);
	}
	
	if(limiter >1){
	while (pch != NULL)
	  	{
	    	//printf ("%s\n",pch);
	    	//printf ("linecount:%i ,rowCount:%i\n",lineCount, rowCount);
	   	int num = atoi(pch);
	   	  //if(printout) printf("opp there it is: %i\n", num);
	   	 arrays_to_organize[lineCount][rowCount] = num;
	    	//printf("worked\n");
			TotalOfAllSubsets[num-1] = TotalOfAllSubsets[num-1] +1;
	    	rowCount++;
	    	pch = strtok (NULL, " \r\n");
			//if(BiggestSubset < rowCount) {printf("newLongest:%d\n",rowCount); BiggestSubset = rowCount;}
	  	}
	SizeOfEachSubset[lineCount] = rowCount;
	lineCount++; 
	}
	
	
	limiter++;    
    }
    fclose(stream);	
    return 1;
  }
 else { 	printf("\nunable to open file\n");	return 0; }
}


int main(int argc, char **argv)
{

   	char * filename = inputName;

	//read input file
	if(!readInputFile(SubsetArrays, filename)) return 0;

	
	int readInputFile(int SubsetArrays[maxNumberOfLists][maxCharLength], char * filename);

	printf("Overall Array For Subsets\n");
	for (int kkk = 0 ; kkk < subsetListLength ;kkk++){
		for (int kk = 0 ; kk < BiggestSubset ;kk++){
			printf("%d ",SubsetArrays[kkk][kk]);
		}
		printf("\n\n");
	}

	printf("Array of Totals of Each Value (Note 0 position is value 1)\n");	
		for (int kk = 0 ; kk < characterListLength ;kk++){
			printf("%d ",TotalOfAllSubsets[kk]);
		}
		printf("\n\n");
		
	printf("Size of Each Array (Note 0 position is subset s1)\n");	
		for (int kk = 0 ; kk < subsetListLength ;kk++){
			printf("%d ",SizeOfEachSubset[kk]);
		}
		printf("\n\n");
		


	printf("List of Elements: %d\n",characterListLength);
	printf("List of Subsets: %d\n", subsetListLength);
	
	

	 return 0;
}