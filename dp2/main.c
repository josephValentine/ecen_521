#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define numberToFit 6\
#define min_Val .01
#define printDebug 0
#define maxCharLength 1000
#define maxNumberOfLists 100
#define runAllLists 1 //if 0 it will only run the first list in the input file
//#define inputName "C:\\Workspace\\C_Workplace\\DesignProblem2\\manystacks.txt"
#define inputName "/Users/josephvalentine/Documents/code/c/ecen_521/dp2/manystacks.txt"

int numberOfFlips = 0;
//int curMaxLoc;
//int curMinLoc;
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

int findGrouping(int array_input[], int begining, int ending)
{
	int lengthleft = ending-begining;
	if(1) printf("Testing Grouping of length %d\n", lengthleft);
	int copy_array[begining];
	int kk;
	if (lengthleft < 1)
	{
	if(1)printf("Trivial Solution of %d \n", kk, array_input[begining]);
	return ending-begining;
	}
	
	for (kk = 0 ; kk < begining ; kk++)
	{
	copy_array[kk] = array_input[kk];
	}
	qsort(copy_array, begining, sizeof(int), cmpfunc);
	
	if(1) printArray(copy_array,begining);
	bool completeList = true;
	for (kk = 1 ; kk < begining-1 ; kk++)
	{
	if( (copy_array[kk]+1) != copy_array[kk+1])
	{
	if(1)printf("at %d, %d Doesn't Match %d\n", kk, (copy_array[kk]+1), copy_array[kk+1]);
	completeList = false;
	break;
	}
	}
	if (completeList)
	{
	if(1)printf("Found a Group up to %d\n", ending-begining);
	return begining;
	}
	else
	{
	if(1)printf("Didn't Find a Group up to %d\n", begining);
	return findGrouping(array_input, begining+1, ending);
	}
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



void findNextFlip(int array_input[], int array_sort[], int curSearchInt, char * returnString, int curMinLoc, int curMaxLoc)
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
	findNextFlip(array_input, array_sort, curSearchInt-1, returnString, curMinLoc, curMaxLoc);
	return;
	}
	if(array_input[0] == curMax && !forwardSearch)
	{
	if(printDebug) printf("-Option 2: Found Next Biggest in first Location\n");
	flipNumber(array_input, sortingArraySize-curSearchInt,sortingArraySize);
	addintToStr(returnString, sortingArraySize-curSearchInt);
	numberOfFlips++;
	curMaxLoc--;
	findNextFlip(array_input, array_sort, curSearchInt-1, returnString, curMinLoc, curMaxLoc);
	return;
	}
	if(curVar == curMax && forwardSearch)
	{
	if(printDebug) printf("-Option 3: Found Next Biggest in last Location, but we were going forward\n");
	curMaxLoc--;
	forwardSearch = false;
	findNextFlip(array_input, array_sort, curSearchInt-1, returnString, curMinLoc, curMaxLoc);
	flipNumber(array_input, sortingArraySize-curSearchInt,sortingArraySize);
	addintToStr(returnString, sortingArraySize-curSearchInt);
	numberOfFlips++;
	return;
	}
	/*
	if(array_input[0] == curMax && forwardSearch)
	{
	if(printDebug) printf("-Option 4: Found Next Biggest in first Location, but we were going forward\n");
	flipNumber(array_input, sortingArraySize-curSearchInt,sortingArraySize);
	addintToStr(returnString, sortingArraySize-curSearchInt);
	numberOfFlips++;
	curMaxLoc--;
	forwardSearch = false;
	findNextFlip(array_input, array_sort, curSearchInt-1, returnString, curMinLoc, curMaxLoc);
	flipNumber(array_input, sortingArraySize-curSearchInt,sortingArraySize);
	addintToStr(returnString, sortingArraySize-curSearchInt);
	numberOfFlips++;
	return;
	}
	*/
	
	
	// ---------------------- Take care of the forward Directions -----------------------------------------	
	if(curVar == curMin && forwardSearch)
	{
	if(printDebug) printf("-Option 5: Found Next Smallest in correct Location\n");
	curMinLoc++;
	findNextFlip(array_input, array_sort, curSearchInt-1, returnString, curMinLoc, curMaxLoc);
	return;
	}
	if(array_input[0] == curMin && forwardSearch)
	{
	if(printDebug) printf("-Option 6: Found Next Smallest in first Location\n");
	flipNumber(array_input, sortingArraySize-curSearchInt,sortingArraySize);
	addintToStr(returnString, sortingArraySize-curSearchInt);
	numberOfFlips++;
	curMinLoc++;
	findNextFlip(array_input, array_sort, curSearchInt-1, returnString, curMinLoc, curMaxLoc);
	return;
	}
	if(curVar == curMin && !forwardSearch)
	{
	if(printDebug) printf("-Option 7: Found Next Smallest in last Location, but we were going backward\n");
	curMinLoc++;
	forwardSearch = true;
	findNextFlip(array_input, array_sort, curSearchInt-1, returnString, curMinLoc, curMaxLoc);
	flipNumber(array_input, sortingArraySize-curSearchInt,sortingArraySize);
	addintToStr(returnString, sortingArraySize-curSearchInt);
	numberOfFlips++;
	return;
	}
	/*
	if(array_input[0] == curMin && !forwardSearch)
	{
	if(printDebug) printf("-Option 8: Found Next Smallest in first Location, but we were going backward\n");
	flipNumber(array_input, sortingArraySize-curSearchInt,sortingArraySize);
	addintToStr(returnString, sortingArraySize-curSearchInt);
	numberOfFlips++;
	curMinLoc++;
	forwardSearch = true;
	findNextFlip(array_input, array_sort, curSearchInt-1, returnString, curMinLoc, curMaxLoc);
	flipNumber(array_input, sortingArraySize-curSearchInt,sortingArraySize);
	addintToStr(returnString, sortingArraySize-curSearchInt);
	numberOfFlips++;
	return;
	}	
	 */ 
	
	if(printDebug) printf("Nothing of Worth, try getting something\n");
	
	
	
	//if (curMax > 200){return;}
	

//sudo code for chaining when there is no obvious answer
	
	int topVal = array_input[0];

	//search for chains

	//find the next highest val
	int i;
	int nextHighestPos = 0;
	
	for(i=2; i<curSearchInt+1; i++){
	if(array_input[i] == topVal + 1) //find the next biggest value (there should always be a bigger val because otherwise it would be one of the obvious solutions)
	{nextHighestPos = i;
	break;
	}
	}
	
	
	
	if(nextHighestPos > 0)
	{
	if(printDebug) printf("-Option ?: Found Next Smallest in first Location\n");
	flipNumber(array_input, sortingArraySize-nextHighestPos+1,sortingArraySize);
	addintToStr(returnString, sortingArraySize-nextHighestPos);
	numberOfFlips++;
	//curMinLoc++;
	findNextFlip(array_input, array_sort, curSearchInt, returnString, curMinLoc, curMaxLoc);
	return;
	}
	
	
	
	/*
	//see if there is a chain going forwards
	int prev = array_input[nextHighestPos];
	for(i=nextHighestPos+1; i<curSearchInt; i++){
	if(array_input[i] == prev + 1){ //chain continues?
	prev++;
	} else {
	break;
	}
	}
	int highestInChainPos = i-1;


	//search for lower vals
	for(i=0; i<curSearchInt; i++){
	if(array_input[i] == topVal - 1) //find the next biggest value (there should always be a bigger val because otherwise it would be one of the obvious solutions)
	break;
	}
	int nextLowestPos = i;
	
	//see if there is a chain going backwards
	prev = array_input[nextLowestPos];
	for(i=nextLowestPos-1; i>0; i--){
	if(array_input[i] == prev - 1){ //chain continues?
	prev--;
	} else {
	break;
	}
	}
	int lowestInChainPos = i+1;

	//now that we now where the chains are we can be smarter about our flips
	//important we need to update our pointers to lowest/highest so they are on the same val after flips
	//there are 8 cases:
	case 1: //4 ... 567 ... 23 ...
	//code above for finding chains must be modified for this case (not hard just havent yet)
	case 2:	//4 ... 567 ... 32 ...
	flip(nextLowestPos); // ...765 ... 432
	flip(nextHighestPos); //567...432
	flip(nextLowestPos + 1); //...765432 
	case 3:	//4 ... 765 ... 23 ...
	//code above for finding chains must be modified for this case (not hard just havent yet)
	case 4:	//4 ... 765 ... 32 ...
	//code above for finding chains must be modified for this case (not hard just havent yet)
	case 5:	//4 ... 23 ... 567 ...
	//code above for finding chains must be modified for this case (not hard just havent yet)
	case 6:	//4 ... 23 ... 765 ...
	//code above for finding chains must be modified for this case (not hard just havent yet)
	case 7:	//4 ... 32 ... 567 ...
	flip(nextHighestPos); // ...23 ... 4567
	flip(nextLowestPos); //32...4567
	flip(nextHIghestPos + 1); //...234567 
	case 8:	//4 ... 32 ... 765 ...
	//code above for finding chains must be modified for this case (not hard just havent yet)

	
	findNextFlip();

*/
	
	
	
	
	
	
	
	
	
	
	
	
	
	// // Unsure of what to do so we search out the beginning or end based on our direction.
	// printf("-Don't know what to do here, should not get to here\n");
	// printf("----------------------------------------------------------\n");
	// printf("----------------------------------------------------------\n");
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
	findNextFlip(array_input, array_sort, curSearchInt-1, returnString, curMinLoc, curMaxLoc);
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
	findNextFlip(array_input, array_sort, curSearchInt-1, returnString, curMinLoc, curMaxLoc);
	return;

	}	
	
	
}





int readInputFile(int arrays_to_organize[maxNumberOfLists][maxCharLength], char * filename){
	FILE *stream;
	stream = fopen(filename, "r");

  	//read file
   if (stream){

    int lineCount = 0;
    char line[maxCharLength];
    while(fgets(line, maxCharLength, stream)){
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

int main(void)
{
	//if (argc < 2)
    //{
    // printf("\nUsage: -name\n name.txt: the name of the textfile\n");
    // exit(0);
   //}
  	//init some vars
   	char * filename = inputName;
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
	
	int curMaxLoc = n-1;
	int curMinLoc = 0;
	forwardSearch = false;
	char returnedString[100] = "";	
	
	findNextFlip(arrays_to_organize[i], sorted_array[i] ,n-1, returnedString, curMinLoc, curMaxLoc);
	addintToStr(returnedString, 0);
	
	if(printDebug) printf("Finished Sorting\n");
	if(printDebug) printf("Finished in: %d\n", numberOfFlips);
	printf("%s(%d)\n",returnedString, numberOfFlips);
	
	printArray(arrays_to_organize[i], n);
	
	}
	
    return 0;
}