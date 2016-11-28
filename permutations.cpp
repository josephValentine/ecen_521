/*	permutations.cpp
    	Generate all permutations of a string, using generic backtracking algorithm
	begun: March 27, 2002
        by: Steven Skiena (C++ version adapted by Bob Kasper, October 2010 and 2013)
*/

/*
Copyright 2003 by Steven S. Skiena; all rights reserved. 
Permission is granted for use in non-commerical applications
provided this copyright notice remains intact and unchanged.

This program appears in my book:
"Programming Challenges: The Programming Contest Training Manual"
by Steven Skiena and Miguel Revilla, Springer-Verlag, New York 2003.

See our website www.programming-challenges.com for additional information.
This book can be ordered from Amazon.com at
http://www.amazon.com/exec/obidos/ASIN/0387001638/thealgorithmrepo/
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define MAXCANDIDATES   100		/* max possible next extensions */
#define NMAX            100		/* maximum solution size */
typedef int data;				/* type to pass data to backtrack */

bool is_a_solution(int[], int, int);
void process_solution(int[], int);
void construct_candidates(int[], int, int, int[], int *);

bool finished = false;                  /* found all solutions yet? */

/* backtrack 
 * starts from a given partial solution vector a[] with k elements
 * and attempts to extend it by adding another element at the end.
 * The solution vector can represent any sequence of objects/events,
 * as long as each object/event can be encoded by a unique integer.
 */
void backtrack(int a[], int k, data input)
{
        int c[MAXCANDIDATES];           /* candidates for next position */
        int ncandidates;                /* next position candidate count */
        int i;                          /* counter */

        if (is_a_solution(a,k,input))
                process_solution(a,k);
        else {
                k = k+1;
                construct_candidates(a,k,input,c,&ncandidates);
                for (i=0; i<ncandidates; i++) {
                    a[k] = c[i];
                    backtrack(a,k,input);
					if (finished) return;	/* terminate early */
                }
        }
}







/* Example: Construct all permutations of a string via backtracking. 
 *
 * uses a vector of characters to output corresponding to
 * integers in the solution vector;
 * illustrates an easy way to use simple integers as the internal encoding
 * of any vector of data elements that represents the set of possible values.
 */
vector<char> output;

void process_solution(int a[], int k)
{
	int i;				/* counter */

	for (i=1; i<=k; i++) {
		// cout << " " << a[i] << " ";	// output result as list of integers
		cout << output[a[i]];	// output result as string of characters
	}
	cout << endl;
}

bool is_a_solution(int a[], int k, int n)
{
	return (k == n);
}

/*	What are possible elements of the next slot in the permutation?  */

void construct_candidates(int a[], int k, int n, int c[], int *ncandidates)
{
	int i;					/* counter */
	bool in_perm[NMAX];		/* what is now in the permutation? */

	for (i=1; i<NMAX; i++) in_perm[i] = false;
	for (i=1; i<k; i++) in_perm[ a[i] ] = true;

	*ncandidates = 0;
	for (i=1; i<=n; i++) 
		if (in_perm[i] == false) {
			c[ *ncandidates ] = i;
			*ncandidates = *ncandidates + 1;
		}
}

int main() {
	int a[NMAX];			/* solution vector: initially empty */
	int size;
	string base, item;
	output.push_back(' ');	/* we don't use index 0 */
	cout << "Enter string to permute:" << endl;
	getline(cin, base);
	size = base.length();
	if (size > NMAX) {
		cout << "Input string is too long, truncating to first " << NMAX << " characters." << endl;
		size = NMAX;
	}
	for (int i=0; i<size; i++)
		output.push_back(base[i]);  // initialize output vector

	// show all permutations of the first N characters for several values of N
	backtrack(a,0,2);
	system("PAUSE");
	backtrack(a,0,3);
	system("PAUSE");
	backtrack(a,0,5);
	system("PAUSE");
}