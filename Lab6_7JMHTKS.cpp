
/*****************************************************************************
//CPSC 230TR       Fall 2021             Lab # 6-7
// Date: 10/28/2021
// Justin Hutmacher
// Twymun Safford
//
// * Average of List of Numbers
//
// * Calculates the average of a list of numbers created in an array
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
using namespace std;

/**************************************
Constant Variable - Max Array Size
**************************************/
const int MAX = 100;

/**************************************
Function Prototype  - Avergae
**************************************/
double average(int sum1, int numPram1);

/**************************************
Main
**************************************/
int main()
{
	//introduce user to the program
	cout << "**********************************************************************" << endl;
	//use a new line to separate the border line above from the program name below
	cout << "*                                                                    *" << endl;
	//describe what the program does 
	cout << "*                    'Calculated Average'                            *" << endl;
	cout << "*  This program calculates the average of a list of numbers. After   *" << endl;
	cout << "*  finding the average the program ranks the scores as below average *" << endl;
	cout << "*  or above average based on each of the scores relative to the      *" << endl;
	cout << "*  the average.                                                      *" << endl;
	//don't forget tp include a new line here
	cout << "*                                                                    *" << endl;
	//finish here by enclosing the initials inside another border 
	cout << "**********************************************************************" << endl;

	/**************************************
	Variables
	**************************************/
	//file streaming
	ifstream inData;
	ofstream outData;
	//names of the output and input files
	string input_file = "data.txt";
	string output_file = "Results.txt";
	//sum for sum of numbers
	//numPram for index of number inarray
	int sum, numPram;
	//average of all values
	double avg;
	//numArray - for array
	//i- counter variable
	//wid - width
	int numArray[MAX], i, wid;
	//open input file
	inData.open(input_file, ios::in);
	//Failed to open file
	if (inData.fail())
	{
		cout << "Failed to open the text file! Please check where it is located!\n";
		exit(1);
	}
	//initialize to zero
	numPram = 0;
	sum = 0;
	avg = 0;
	//print statement to tell user list is being printed
	cout << "Now printing out the list of numbers from " << input_file << endl;
	//Displays list of numbers
	while (!inData.eof())
	{
		//numPram = numPram + 1;
		//check if file is still processing valid input
		if (inData.good())
		{
			//grab that number in that row and store in associated index
			inData >> numArray[numPram];
			//get total sum of all numbers
			sum += numArray[numPram];
			//print out the list
			cout << "\n" << numArray[numPram];
			//iterate by 1 until end of file (grabs last line)
			numPram++;

		}

	}
	//calculate the average of all of the values
	avg = average(sum, numPram);

	//Output
	cout << "\n\nThe average is " << avg;
	//tell user that the scores will not be compared
	cout << "\n\nNow, time to compare these scores to the average." << endl;
	//close the input file since contents have been stored in array
	inData.close();
	//open the output file for writing
	outData.open(output_file, ios::out);
	//print a header to the file for score above and score below
	cout << "\n"<< endl;
	outData.setf(ios::showpoint) << "The average was: " << avg << endl;
	outData << "\n" << endl;
	cout <<  "Score" << "   " << "Above/Below average" << endl;
	cout << "------" << "  " << "----------------" << endl;
	outData  << "Score" << "   "  << "Above/Below average" << endl;
	outData << "------" << "  " << "----------------" << endl;
	//Gives diffrent widths for Results.txt depending on number places 
	for (i = 0; i < numPram; i++)
	{
		if (numArray[i] < 10)
		{
			wid = 21;
		}
		else
		{
			wid = 20;
		}
		if (numArray[i] > avg)
		{
			cout << numArray[i] << setw(wid) << "Above Average\n";
			outData << numArray[i] << setw(wid) << "Above Average\n";
		}
		else if (numArray[i] < avg)
		{
			cout << numArray[i] << setw(wid) << "Below Average\n";
			outData << numArray[i] << setw(wid) << "Below Average\n";
		}
		else
		{
			cout << numArray[i] << setw(wid) << "Equal to the average\n";
			outData << numArray[i] << setw(wid) << "Equal to the Average\n";
		}
	}
	//tell user the results are being written to file
	cout << "\n\nThese results are being printed to file..." << endl;
//close the output file
	outData.close();
//tell user results have been printed to file 
	cout << "\n\nThe results have been printed to the file " << output_file << endl;
	return 0;
}

/**************************************
Function Definition
**************************************/
double average(int sum1, int numPram1)
{
//Precondition(s): 
// * This function needs to be pass by value - returning average to main
// * If numPram1 is zero (indicating that there are no elements) there is a 
//   divide by zero issue - need warning message for user; numPram1 should be
// 	 greater than zero
// 
//  
//Postcondition(s): 
// *The average (sum of all numbers in the array divided by number
//of elements in the array) must be calculated and then rounded to 1 decimal point
	
	//first, check if numPram1 is zero
	if (numPram1 == 0)
	{
		cout << "Your data file has no elements. Division by zero error! Closing program now." << endl;
		return 0;
	}
    //Variables
	double avg1, sum2, numPram2;
	int avg2;

	//Turning into doubles
	sum2 = static_cast<double>(sum1);
	numPram2 = static_cast<double>(numPram1);

	avg1 = sum2 / numPram2;

	//Rounding to one decimal place
	avg1 = avg1 * 10.0;
	avg1 = avg1 + 0.5;
	avg2 = static_cast<int>(avg1);
	avg1 = static_cast<double>(avg2);
	avg1 = avg1 / 10.0;

	//Return avg1 to main
	return avg1;
}
