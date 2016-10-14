#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define numberToFit 6
#define min_Val .01
#define printDebug 1
int numberOfFlips = 0;
int curMaxLoc;
int curMinLoc;
char *StringOut;
bool forwardSearch;
int sortingArraySize;

 addintToStr(char * list, int inputVal){ 
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



int main(void)
{

	
	int array_to_Organize[] = {2, 5, 1, 4, 3 };
	//int array_to_Organize[] = {3, 5, 10, 4, 7, 2, 9, 1, 6, 8  };
	//int array_to_Organize[] = {1, 10, 9, 6, 11, 7, 12, 2, 8, 13, 4, 15, 14, 3, 5  };
	//int array_to_Organize[] = {4, 6, 3, 8, 2, 13, 10, 9, 5, 20, 7, 12, 11, 17, 14, 1, 19, 16, 15, 18  };
	//int array_to_Organize[] = {10, 1, 11, 18, 15, 21, 25, 14, 5, 13, 16, 22, 23, 20, 4, 7, 24, 17, 19, 12, 6, 8, 9, 3, 2,  };
	//int array_to_Organize[] = {37, 8, 30, 40, 6, 32, 38, 3, 17, 29, 34, 9, 1, 7, 31, 23, 25, 20, 39, 2, 35, 21, 24, 13, 36, 18, 14, 26, 12, 4, 22, 28, 16, 11, 10, 19, 5, 15, 27, 33,  };
	//int array_to_Organize[] = {36, 35, 18, 47, 6, 9, 34, 17, 40, 48, 13, 44, 42, 33, 25, 28, 1, 3, 4, 30, 20, 41, 46, 29, 38, 24, 31, 39, 37, 22, 10, 27, 8, 16, 21, 26, 11, 43, 49, 2, 12, 32, 45, 23, 19, 14, 7, 15, 5, 50,  };
	//int array_to_Organize[] = {25, 17, 54, 18, 49, 39, 9, 15, 57, 3, 32, 48, 50, 12, 55, 2, 11, 47, 45, 58, 36, 28, 34, 52, 44, 24, 29, 20, 27, 31, 56, 16, 33, 21, 53, 43, 10, 41, 7, 5, 14, 1, 60, 4, 23, 38, 59, 46, 8, 37, 51, 35, 19, 22, 26, 6, 13, 42, 40, 30,  };
	//int array_to_Organize[] = {32, 48, 13, 11, 35, 49, 61, 14, 34, 39, 67, 55, 25, 69, 7, 60, 28, 64, 5, 58, 46, 66, 41, 44, 53, 59, 33, 63, 62, 10, 54, 22, 17, 1, 4, 40, 31, 42, 38, 43, 47, 21, 16, 12, 20, 65, 52, 26, 51, 8, 56, 57, 37, 3, 23, 70, 27, 18, 45, 36, 2, 30, 15, 6, 24, 29, 50, 19, 68, 9,};
	//int array_to_Organize[] = {73, 46, 20, 17, 32, 43, 71, 53, 41, 59, 69, 39, 49, 63, 48, 37, 18, 29, 30, 56, 42, 7, 27, 14, 6, 10, 26, 8, 19, 24, 13, 50, 25, 79, 15, 3, 16, 57, 65, 52, 72, 28, 35, 78, 21, 77, 34, 33, 5, 45, 61, 76, 54, 4, 36, 74, 64, 40, 60, 80, 11, 12, 51, 75, 2, 9, 31, 67, 22, 66, 55, 1, 68, 47, 23, 58, 38, 70, 62, 44, };
	//int array_to_Organize[] = {20, 78, 82, 50, 2, 59, 79, 8, 21, 81, 33, 58, 3, 48, 42, 83, 74, 24, 23, 5, 44, 41, 9, 40, 38, 49, 37, 15, 11, 34, 18, 88, 47, 60, 25, 87, 77, 30, 35, 12, 31, 56, 89, 57, 29, 53, 13, 39, 73, 7, 51, 52, 17, 75, 26, 16, 28, 45, 55, 69, 14, 66, 6, 72, 61, 4, 1, 76, 64, 71, 46, 43, 54, 67, 86, 27, 80, 36, 32, 22, 90, 68, 19, 10, 85, 62, 70, 65, 84, 63, };
	//int array_to_Organize[] = {94, 93, 28, 55, 64, 100, 49, 5, 15, 19, 31, 33, 42, 8, 37, 68, 71, 69, 16, 51, 91, 89, 57, 79, 56, 24, 27, 47, 67, 58, 20, 82, 74, 4, 54, 14, 80, 60, 44, 18, 59, 83, 22, 25, 32, 98, 23, 87, 2, 86, 43, 9, 30, 46, 61, 29, 48, 26, 66, 81, 34, 38, 36, 12, 40, 92, 65, 41, 77, 78, 90, 84, 85, 96, 21, 35, 13, 72, 50, 45, 52, 6, 39, 99, 17, 62, 11, 88, 1, 76, 75, 73, 97, 70, 7, 3, 63, 53, 10, 95,};

	int n = (int)( sizeof(array_to_Organize) / sizeof(array_to_Organize[0]) );
	if(printDebug) printf("Length of array: %d\n", n);
	sortingArraySize = n;
	
	int sorted_array[n];
	int kk;
	for (kk =0; kk < n ; kk++)	{ sorted_array[kk] = array_to_Organize[kk];	}
	qsort(sorted_array, n, sizeof(int), cmpfunc);
	
	printf("Array Given:\n");
	printArray(array_to_Organize,n);
	
	if(printDebug) printf("Array Sorted:\n");
	if(printDebug) printArray(sorted_array,n);	
	if(printDebug)printf("\n ------ Starting Flipping -------\n");
	
	curMaxLoc = n-1;
	curMinLoc = 0;
	forwardSearch = false;
	char returnedString[100] = "";	
	
	findNextFlip(array_to_Organize, sorted_array ,n-1, returnedString);
	addintToStr(returnedString, 0);
	
	if(printDebug) printf("Finished Sorting\n");
	if(printDebug) printf("Finished in: %d\n",numberOfFlips);
	printf("%s(%d)",returnedString,numberOfFlips);
	

	
    return 0;
}