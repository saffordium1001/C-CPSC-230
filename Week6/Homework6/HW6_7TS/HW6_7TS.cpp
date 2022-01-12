/*****************************************************************************
//CPSC 230TR       Fall 2021             HW # 6-7
// Date: 11/02/2021
// Twymun Safford
//
// * Average of Student Grades
//
// * Assigns from file (end-of-file) to an array of strings a name, to an array 
// * of numbers the scores/grades(whole numbers), and calculates the average
// * grade based upon a function and user input.
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
//maximum size of arrays 
const int MAX = 600;

/**************************************
Function Prototype  - Average
**************************************/
//receives sum and quantity by value
double average(int summation, int value);


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
	cout << "*                    'Average from Arrays'                           *" << endl;
	cout << "*  This program calculates the average grade (nearest tenth)         *" << endl;
	cout << "*  from students (name) and their respective grades from file.       *" << endl;
	cout << "*  The program ranks the scores as below average or above            *" << endl;
	cout << "*  average based on each of the scores relative to the average.      *" << endl;
	//don't forget tp include a new line here
	cout << "*                                                                    *" << endl;
	//finish here by enclosing the initials inside another border 
	cout << "**********************************************************************" << endl;
	//variables - input and output
	ifstream inFile;
	ofstream outFile;
	// string array 'name' - holds up to MAX elements
	string name[MAX];
	//integer array 'grade - holds up to MAX whole number elements
	int grade[MAX];
	//variable x- counter for each element
	int x;
	//counter for for loop
	int i;
	//variable quantity - number of elements
	int quantity;
	//variable sum - 
	int sum;
	//variable avg. - mean of scores
	double avg;
	//(optional) assign file names for input and output to string
	string input_file = "data7.txt";
	string output_file = "results.txt";
	//open the text file
	inFile.open(input_file, ios::in);
	//check if the file was opened properly
	if (inFile.fail())
	{
		cout << "\nFailed to open the text file! Please check your spelling or check your file location!\n";
		return 0;
	}
	//if the file opened properly, initialize values to zero
	x = 0;
	quantity = 0;
	sum = 0;
	avg = 0.0;
	//check if not end of file and not greater than maximum size of arrays
	while (!inFile.eof() && quantity < MAX)
		//read through the file and assign a name and a grade respectively
		//to each aray name[x] and grade[x]
	{
		inFile >> name[x] >> grade[x];
		//increment x by one
		x++;
	}
	//close the input file - all contents read into arrays
	inFile.close();
	//open the output file for writing
	outFile.open(output_file, ios::out);
	//check to see if the output file failed to open
	if (outFile.fail())
	{
		cout << "Failed to open the output file!\n";
		return 0;
	}
	//prompt user to enter the quantity of grades to be processed
	cout << "\nEnter quantity of grades to be processed (0-" << x << "): ";
	//assign the user value to quantity
	cin >> quantity;
	//for loop to add sum 
	for (i = 0; i < quantity; i++)
	{
		//accumulate the grades in grade[x] for sum
		sum += grade[i];
	}
	//pass by value both sum and quantity to the function avg
	avg = average(sum, quantity);
	//print the average grade
	cout << "\nThe average grade is " << avg << "." << endl;
	//column headers name, grade, and comment - use tabs
	cout << "\n" << right << setw(5) << "#" << right << setw(16) << "Name" << right << setw(7)
		<< "Grade" << right << setw(17) << "Comment" << endl;
	outFile << "\n" << right << setw(5) << "#" << right << setw(16) << "Name" << right << setw(7)
		<< "Grade" << right << setw(17) << "Comment" << endl;
	//for loop to determine 
	for (i = 0; i < quantity; i++)
	{
		//print number, followed by name, followed by grade
		cout << right << setw(5) << (i + 1) << ") " << right  << setw(14) << name[i] << right
			<< setw(7) << grade[i] << right << setw(17);
		outFile << right << setw(5) << (i + 1) << ") " << right << setw(14) << name[i] << right
			<< setw(7) << grade[i] << right << setw(17);
		//if the value of grade[i] is less than the average
		if (grade[i] < avg)
		{
			//print above average
			cout << "Below average" << endl;
			outFile << "Below average" << endl;
		}
		//else, if the value of grade[i] is higher than the average
		else
		{
			cout << "Above average" << endl;
			outFile << "Above average" << endl;
		}
	}
	//close the file
	outFile.close();
	//tell the user the file is now ready
	cout << "\nYour results are now ready! They have been printed to file " << output_file << "." << endl;
	//end program
	return 0;
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
		cout << "\nYour data file has no numerical elements or is empty."
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

