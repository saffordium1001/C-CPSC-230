/*****************************************************************************
//CPSC 230TR       Fall 2021             HW # 7B
// Date: 11/07/2021
// Twymun Safford
//
// * Top Movies: Parallel Arrays, I/O File, Search, Function, Get-Line
//
// * Uses a random number generator to fill array with 20 2-digit numbers,
// * uses bubble sort to sort original into array sorted, and uses while loop
// * to find if numbers are within the sorted array.
****************************************************************************/

/**************************************
Headers
**************************************/
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <string>
#include <ctime>
using namespace std;

/**************************************
Constant Variable - Max Array Size
**************************************/
//maximum size of arrays 
const int MAX = 100;


/**************************************
Function Prototype  - RandomFill
**************************************/
//Fills the array with 20 random 2-digit numbers
//using the rand function
void RandomFill(int arr[], int n);

/**************************************
Function Prototype  - Swap
**************************************/
//swap the values of a and b in the array
void swap(int& a, int& b);


/**************************************
Function Prototype  - Sorting
**************************************/
//Use bubble sort algorithm to sort
//numbers in order - copy from 
//original to sorted
void sorting(int arr[], int n);


///**************************************
//Function Prototype  - Search
//**************************************/
////search the arrays for the integers
////of interest
int search(int arr[], int n, int key);

/**************************************
Function Prototype  - Average
**************************************/
//receives sum and quantity by value
double average(int summation, int value);


int main()
{
	//ensures that time will not be used for random seed
	//srand: will not use current time as seed for random generator
	srand(time(0));
	//variables
	int i; //counter variable
	int original[MAX], sorted[MAX]; //arrays original and sorted
	int index; //index
	int target[] = { 7,25,42,91 }; //numbers to be searched for
	int sum = 0; //sum of all elements in array
	double avg = 0.0; //average of all of the elements in the array
	//fill the original array first
	RandomFill(original, MAX);
	//copy the elements from the original array into the sorted array
	for (i = 0; i < MAX; i++)
	{
		//copy from original to sorted
		sorted[i] = original[i];
	}
	//sort the array original: copies original into sorted - uses bubble sort after call to function swap 
	sorting(sorted, MAX);
	//for loop - search the sorted array to determine if the elements in target can be found
	for (i = 0; i < 4; i++)
	{
		index = search(sorted, MAX, target[i]);
		//if the value of search is returned as -1
		if (index == -1)
		{
			cout << "The number " << target[i] << " is not found." << endl;
		}
		else
		{
			cout << "The number " << target[i] << " was found at index number " << index
				<< " (or at position " << (index + 1) << " ) in the sorted array." << endl;
		}
	}
	//print the arrays
	//the original array
	cout << "\nThe original array is: ";
	for (i = 0; i < MAX; i++)
	{
		cout << original[i] << " ";
	}
	//print the assorted array
	cout << "\n\nThe sorted array is: ";
	for (i = 0; i < MAX; i++)
	{
		cout << sorted[i] << " ";
	}

	//now, find the summation of all of the elements in the array
	for (i = 0; i < MAX; i++)
	{
		//add each element within the sorted array
		sum += sorted[i];
	}
	//pass by value the sum of these values and the number to the function average
	avg = average(sum, MAX);
	//display the sum of the elements
	cout << "\n\nThe sum of the elements in the array is: " << sum;
	//display averages to console
	cout << "\n\The average of the elements in the array is: " << avg << endl;
	//return
	return 0;
}


/**************************************
Function Definition  - RandomFill
**************************************/
void RandomFill(int arr[], int n)
{
	//Generates random two-digit numbers for each entry in an array and inserts them.
	//
	//Preconditions: The array size must be known and the array must be created.
	// 
	// Postconditions: The elements of the array will all be two-digit integer numbers( >9 or <100). 
	//counter
	int i;
	//for loop - from 0 to max size of array
	for (i = 0; i < n; i++)
	{
		//Generate a 2-digit random number between 10 and 99 (inclusive)
		arr[i] = (rand() % 90) + 10;
	}
	return;
}


/**************************************
Function Prototype  - Swap
**************************************/
void swap(int& a, int& b)
{
	//Swaps the value of two integer values in an array
	 //
	//Precondition: The integers a and b need to come in for an array. Needs to be passed by reference
	//because the values of integers a and b need to reference memory (array).

	//Postcondition: The integer numbers should swap these numbers. A temporary integer will need to be used
	//to swap these values 

	//swap temp with a
	int temp = a;
	//swap a with b
	a = b;
	//swap b with temp
	b = temp;
	//return
	return;
}

/**************************************
Function Prototype  - Sorting
**************************************/

void sorting(int arr[], int n)
{
	//Use bubble sort algorithm to sort numbers in order after copying from original into sorted
	//
	//Precondition: The array sorted needs to exist and the maximum value of n must be known.
	//
	//Postcondition: The array sorted will be sorted based on comparing if two numbers are different or equal.
	//The maximum value of index i will be n while the maximum index of j will be n-i-1.

	// counters - i and j
	int i, j;
	//now, implement the bubble sort algorithm to sort the elements in order
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < (n - i - 1); j++)
		{
			//if the value of the element in the array sorted is greater than
			//the right adjacent element, swap the two elements
			if (arr[j] > arr[j + 1])
			{
				//swap
				swap(arr[j], arr[j + 1]);
			}
		}
	}
	return;
}

/**************************************
Function Prototype  - Search
**************************************/

int search(int arr[], int n, int key)
{
	//Searches the array (sorted) for the integers of interest. Sets boolean variable
	//to true if found and false if not. Returns index if found or index set to -1 if not found.
	//
	//Precondition: The array sorted needs to be accessible, the size of the array needs to be known, and
	//the variable key is the value that needs to be
	//found by the user (integer).
	//
	//Postcondition: The function will search the array for the key value (integer). If it is found,
	//return inde. If it is not found, return -1.
	//counter i - for each element in the array
	int i = 0;
	//boolean variable found - false but set to true when found 
	bool Found = false;
	//boolean variable Found - true if found and false if not found
	//while loop - check to see for each key value if they are in the array
	while (i < n && (!Found))
	{
		//if the key value was found
		if (arr[i] == key)
		{
			//return true
			Found = true;
		}
		//set position to length if arr[i] greater than key
		/*else if (arr[i] > key)
		{
			i = n;
		}*/
		//else, increment position by one
		else
		{
			i++;
		}
	}
	//if not found, return -1
	if (Found == false)
	{
		return -1;
	}
	else
	{
		return i;
	}

}

/**************************************
Function Definition  - Average
**************************************/
double average(int summation, int value)
{
	//Receives the values of sum and quantity,calculates the average, and 
	//rounds it to the nearest tenth
	//
	//Preconditions: Both quantity and sum need to be integer values.
	// **If quantity is zero, then we have divide by zero error. Notify
	// user with error message and then close the program if this is the case.
	// 
	// Postconditions: If both quantity and sum are non-zero, the average of all of
	// the selected number of scores will be calculated to nearest tenth and
	// then returned to main. 
	if (value == 0)
	{
		cout << "\nYour array is empty."
			<< "\nDivision by zero error! Closing program now." << endl;
		return 0;
	}
	//Variables
	double avg1, sumFunction, numFunction;
	int avg2;

	//Turning into doubles
	sumFunction = static_cast<double>(summation);
	numFunction = static_cast<double>(value);

	avg1 = sumFunction / numFunction;

	//Rounding to one decimal place
	avg1 = avg1 * 10.0;
	avg1 = avg1 + 0.5;
	avg2 = static_cast<int>(avg1);
	avg1 = static_cast<double>(avg2);
	avg1 = avg1 / 10.0;

	//Return avg1 to main
	return avg1;
}  