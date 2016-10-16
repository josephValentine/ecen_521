#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define numberToFit 6
#define min_Val .01
#define printDebug 1
#define maxCharLength 1000
#define maxNumberOfLists 100
#define runAllLists 1 //if 0 it will only run the first list in the input file

int numberOfFlips = 0;
int curMaxLoc;
int curMinLoc;
char *StringOut;
bool forwardSearch;
int sortingArraySize;

char * addintToStr(char * list, int inputVal){ 
	char buffer[10]; 
	snprintf(buffer,10,"%d ", inputVal); 
	strcat(list, buffer);
	return list;}

int cmpfunc (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

void printArray(int array_to_Print[], int length)
{
	for (int kk = 0 ; kk < length ; kk++) printf("%d ",   array_to_Print[kk]);
	printf("\n");
}

int* flipNumber(int array_input[], int location, int ending)
{
	int arraylocation = ending - location +1;
	if(printDebug) printArray(array_input,ending);
	if(printDebug)printf("Commanded to Flip at location: %d \n", location);
	if(printDebug)printf("Location in array is: %d \n", arraylocation);
	if(printDebug)printf("Going to flip with value: %d \n", array_input[arraylocation-1]);
	
	int TempToFlip[arraylocation];
	int kk;
	for (kk =0; kk < arraylocation ; kk++)	{	TempToFlip[kk] = array_input[kk];	} 
	for (kk =0; kk < arraylocation ; kk++)	{	array_input[kk] = TempToFlip[arraylocation - kk -1]; }
 
 	if(printDebug) printArray(array_input,ending);
	if(printDebug) printf("Done Flipping \n\n");
	return array_input;
}



void findNextFlip(int array_input[], int array_sort[], int curSearchInt, char * returnString)
{
	if(curSearchInt == 0) { return;}
	int curVar = array_input[curSearchInt];
	int curMax = array_sort[curMaxLoc];
	int curMin = array_sort[curMinLoc];
	if(printDebug) printf("Start Searching for %d=%d with Minedge %d, Maxedge %d\n", curSearchInt, curVar, curMin, curMax);
	
	// ---------------------- Take care of the reverse Directions -----------------------------------------
	if(curVar == curMax && !forwardSearch)
	{
		if(printDebug) printf("-Option 1: Found Next Biggest in correct Location\n");
		curMaxLoc--;
		findNextFlip(array_input, array_sort, curSearchInt-1, returnString);
		return;
	}
	if(array_input[0] == curMax && !forwardSearch)
	{
		if(printDebug) printf("-Option 2: Found Next Biggest in first Location\n");
		flipNumber(array_input, sortingArraySize-curSearchInt,sortingArraySize);
		addintToStr(returnString, sortingArraySize-curSearchInt);
		numberOfFlips++;
		curMaxLoc--;
		findNextFlip(array_input, array_sort, curSearchInt-1, returnString);
		return;
	}
	if(curVar == curMax && forwardSearch)
	{
		if(printDebug) printf("-Option 3: Found Next Biggest in last Location, but we were going forward\n");
		curMaxLoc--;
		forwardSearch = false;
		findNextFlip(array_input, array_sort, curSearchInt-1, returnString);
		flipNumber(array_input, sortingArraySize-curSearchInt,sortingArraySize);
		addintToStr(returnString, sortingArraySize-curSearchInt);
		numberOfFlips++;
		return;
	}
	if(array_input[0] == curMax && forwardSearch)
	{
		if(printDebug) printf("-Option 4: Found Next Biggest in first Location, but we were going forward\n");
		flipNumber(array_input, sortingArraySize-curSearchInt,sortingArraySize);
		addintToStr(returnString, sortingArraySize-curSearchInt);
		numberOfFlips++;
		curMaxLoc--;
		forwardSearch = false;
		findNextFlip(array_input, array_sort, curSearchInt-1, returnString);
		flipNumber(array_input, sortingArraySize-curSearchInt,sortingArraySize);
		addintToStr(returnString, sortingArraySize-curSearchInt);
		numberOfFlips++;
		return;
	}	
	
	
	// ---------------------- Take care of the forward Directions -----------------------------------------	
	if(curVar == curMin && forwardSearch)
	{
		if(printDebug) printf("-Option 5: Found Next Smallest in correct Location\n");
		curMinLoc++;
		findNextFlip(array_input, array_sort, curSearchInt-1, returnString);
		return;
	}
	if(array_input[0] == curMin && forwardSearch)
	{
		if(printDebug) printf("-Option 6: Found Next Smallest in first Location\n");
		flipNumber(array_input, sortingArraySize-curSearchInt,sortingArraySize);
		addintToStr(returnString, sortingArraySize-curSearchInt);
		numberOfFlips++;
		curMinLoc++;
		findNextFlip(array_input, array_sort, curSearchInt-1, returnString);
		return;
	}
	if(curVar == curMin && !forwardSearch)
	{
		if(printDebug) printf("-Option 7: Found Next Smallest in last Location, but we were going backward\n");
		curMinLoc++;
		forwardSearch = true;
		findNextFlip(array_input, array_sort, curSearchInt-1, returnString);
		flipNumber(array_input, sortingArraySize-curSearchInt,sortingArraySize);
		addintToStr(returnString, sortingArraySize-curSearchInt);
		numberOfFlips++;
		return;
	}
	if(array_input[0] == curMin && !forwardSearch)
	{
		if(printDebug) printf("-Option 8: Found Next Smallest in first Location, but we were going backward\n");
		flipNumber(array_input, sortingArraySize-curSearchInt,sortingArraySize);
		addintToStr(returnString, sortingArraySize-curSearchInt);
		numberOfFlips++;
		curMinLoc++;
		forwardSearch = true;
		findNextFlip(array_input, array_sort, curSearchInt-1, returnString);
		flipNumber(array_input, sortingArraySize-curSearchInt,sortingArraySize);
		addintToStr(returnString, sortingArraySize-curSearchInt);
		numberOfFlips++;
		return;
	}	
	
	if(printDebug) printf("Nothing of Worth, try getting something\n");
	
	
	// Unsure of what to do so we search out the beginning or end based on our direction.
	if(forwardSearch)
	{
		if(printDebug) printf("-Option 9: No obvious answer, Going Forward so search for the next Min\n");
		int kk;
		for( kk = 1 ; kk < curSearchInt; kk++)
		{
			if(array_input[kk] == curMin)
			{
				break;
			}
		}
		flipNumber(array_input, sortingArraySize-kk, sortingArraySize);
		addintToStr(returnString, sortingArraySize-kk);
		numberOfFlips++;
		flipNumber(array_input, sortingArraySize-curSearchInt, sortingArraySize);
		addintToStr(returnString, sortingArraySize-curSearchInt);
		numberOfFlips++;
		curMinLoc++;
		findNextFlip(array_input, array_sort, curSearchInt-1, returnString);
		return;
	}
	if(!forwardSearch)
	{
		if(printDebug) printf("-Option 10: No obvious answer, Going Backward so search for the next Min\n");
		int kk;
		for( kk = 1 ; kk < curSearchInt; kk++)
		{
			if(array_input[kk] == curMax)
			{
				break;
			}
		}
		flipNumber(array_input, sortingArraySize-kk, sortingArraySize);
		addintToStr(returnString, sortingArraySize-kk);
		numberOfFlips++;
		flipNumber(array_input, sortingArraySize-curSearchInt, sortingArraySize);
		addintToStr(returnString, sortingArraySize-curSearchInt);
		numberOfFlips++;
		curMaxLoc--;
		findNextFlip(array_input, array_sort, curSearchInt-1, returnString);
		return;
	}		
	printf("-Don't know what to do here, should not get to here\n");
	
}

int readInputFile(int arrays_to_organize[maxNumberOfLists][maxCharLength], char * filename){
	FILE *stream;
	stream = fopen(filename, "r");

  	//read file
   if (stream){

    int lineCount = 0;
    char line[32];
    while(fgets(line, 32, stream)){
	 	char * pch;
	 	//printf ("Splitting string \"%s\" into tokens:\n", line);
	 	int rowCount = 0;
	 	pch = strtok (line," ");

		while (pch != NULL)
	  	{
	    	//printf ("%s\n",pch);
	    	//printf ("linecount:%i ,rowCount:%i\n",lineCount, rowCount);
	   		int num = atoi(pch);
	   		// printf("opp there it is: %i\n", thing);
	   		 arrays_to_organize[lineCount][rowCount] = num;
	    	//printf("worked\n");
	    
	    	rowCount++;
	    	pch = strtok (NULL, " \r\n");
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

int numberOfPancakeStacks(int arrays_to_organize[maxNumberOfLists][maxCharLength]){
	int i = 0;
	while(arrays_to_organize[i][1] != 0){
		i++;
	}
	return i;
}

int sizeOfPancakeStack(int arrays_to_organize[maxNumberOfLists][maxCharLength], int stackNum){
	int i = 0;
	while(arrays_to_organize[stackNum][i] != 0){
		i++;
	}
	return i;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
    {
     printf("\nUsage: -name\n name.txt: the name of the textfile\n");
     exit(0);
   }
  	//init some vars
   	char * filename = argv[1];
	int arrays_to_organize[maxNumberOfLists][maxCharLength];
	int sorted_array[maxNumberOfLists][maxCharLength];

	//read input file
	if(!readInputFile(arrays_to_organize, filename)) return 0;
	int stacks;
	
	//determine how many stacks to run
	if(runAllLists)
		stacks = numberOfPancakeStacks(arrays_to_organize);
	else
		stacks = 1;
	
	//run the algorithm
	int i;
	for(i = 0; i < stacks; i++){
		numberOfFlips = 0;
		
		int n =sizeOfPancakeStack(arrays_to_organize, i);
		sortingArraySize = n;

		memcpy(sorted_array, arrays_to_organize, sizeof(arrays_to_organize));
		qsort(sorted_array[i], n, sizeof(int), cmpfunc);
		
		printf("Array Given:\n");
		printArray(arrays_to_organize[i],n);
		
		if(printDebug) printf("Array Sorted:\n");
		if(printDebug) printArray(sorted_array[i], n);	
		if(printDebug)printf("\n ------ Starting Flipping -------\n");
		
		curMaxLoc = n-1;
		curMinLoc = 0;
		forwardSearch = false;
		char returnedString[100] = "";	
		
		findNextFlip(arrays_to_organize[i], sorted_array[i] ,n-1, returnedString);
		addintToStr(returnedString, 0);
		
		if(printDebug) printf("Finished Sorting\n");
		if(printDebug) printf("Finished in: %d\n", numberOfFlips);
		printf("%s(%d)",returnedString, numberOfFlips);
	}
	
    return 0;
}