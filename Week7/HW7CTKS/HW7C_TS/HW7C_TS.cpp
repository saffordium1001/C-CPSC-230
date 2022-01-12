/*****************************************************************************
// CPSC 230TR			Fall 2021			HW # 7C
// Twymun Safford
// Date: 11/12/2021
//
// * Top Movies: Parallel Arrays, I/O File, Search, Function, Get-Line
//
// * Uses parallel arrays to construct a text file containing movies that
// * have made at least 300 million or more. Processes the number of movies
// * that are user selected and renders an average of those values.
****************************************************************************/


/**************************************
Headers
**************************************/
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <ctime>
using namespace std;

/**************************************
Constant Variable - Max Array Size
**************************************/
//maximum size of arrays 
const int MAX = 100;


/*******************************************
Function Prototype  - Minimum (300 million)
********************************************/
//prints to screen the films that have made at least 300 million
void at_least300(int revenue[], string titles[], int n);

/*******************************************
Function Prototype  - User Choice
********************************************/
//processes the user choice for movies
void user_choice(int rev[], string titular[], int num, long long int& sum, long double& mean, ofstream& outMovie);

/**************************************
Function Prototype  - Average
**************************************/
double average(long long int sum1, int numPram1);


int main()
{
	//introduce user to the program
	cout << "**********************************************************************" << endl;
	//use a new line to separate the border line above from the program name below
	cout << "*                                                                    *" << endl;
	//describe what the program does 
	cout << "*                    'Best of Movies'                                *" << endl;
	cout << "*  This program prints to screen the movies from text file that have *" << endl;
	cout << "*  made at least 300 million dollars or more at the box office.      *" << endl;
	cout << "*  The user can then select the quantity of movies and this program  *" << endl;
	cout << "*  will calculate the average earnings of the movies that were       *" << endl;
	cout << "*  selected.                                                         *" << endl;
	//don't forget tp include a new line here
	cout << "*                                                                    *" << endl;
	//finish here by enclosing the initials inside another border 
	cout << "**********************************************************************" << endl;
	/**************************************
	Variables
	**************************************/
	//file streaming
	ifstream inMovie;
	ofstream outMovie;
	//names of the output and input files
	string input_file = "TopMovies.txt";
	string output_file = "TheBest.txt";
	//quantity - number of movies
	int quantity = 0;
	//x - counter for number read
	int x = 0;
	//sum of movies - needs to be a long long integer since movie income is in millions (-(2^63) to (2^63)-1)
	long long int sum = 0;
	//average of all values - also needs to be long as well (possibly)
	long double avg=0;
	//create string array title and set size equal to MAX
	string title[MAX];
	//create int array income to hold movie income
	int income[MAX];
	//open input file
	inMovie.open(input_file, ios::in);
	//if the file failed to open
	if (inMovie.fail())
	{
		cout << "Failed to open the text file! Please check where it is located!\n";
		exit(1);
	}
	//while loop combined with eof to read title and income from file -> assign to title and income respectively
	while (!inMovie.eof())
	{
		//for loop - loop over file lines until all lines are grabbed 
		for (x = 0; x < MAX; x++)
		{
			//get each line of the file first into the title of each movie
			getline(inMovie, title[x]);
			//then read out to income
			inMovie >> income[x];
			//ignore the rest of the line once we have title and income (1024 characters more than sufficient)
			inMovie.ignore(1024, '\n');
			//then increment x by one
		}
	}
	//close the file since we have read to file
	//close the input file - all contents read into arrays
	inMovie.close();
	//now, call the function to print the movies from the list that grossed at least 300 million
	at_least300(income, title, MAX);   //calling function for printing movies that made atleast 300 million
	//open the output file
	outMovie.open(output_file, ios::out);
	//check to see if the output file failed to open
	if (outMovie.fail())
	{
		cout << "Failed to open the output file!\n";
		return 0;
	}
	//Now, from the user_choice function ask user for movie choices
	user_choice(income, title, x, sum, avg, outMovie);
	return 0;
}
//


/**************************************
Function Definitions - Minimum 300
**************************************/
void at_least300(int revenue[], string titles[], int n)  //to print movie that made atleast 300 million
{
//Receives the values of the string and integer arrays and prints to screen
//which movies are greater than 300
//
//Preconditions: Both arrays must be created and initialized
// 
// Postconditions: Print the movie titles to console. 
	//tell user movies that made at least 300 million
	cout << "\nMovies that made at least 300 million are :\n";
	int i = 0;
	//while loop - print 
	for (i = 0; i < n; i++)
	{
		if (revenue[i] >= 3e8)
		{
			cout << titles[i] << "\n";
		}
	}
	//then return
	return;
}


/*******************************************
Function Definitions  - User Choice
********************************************/
//processes the user choice for movies
//Receives the two arrays(titles and income), the current value of x, the sum and average (set to zero),
// and the variable for output stream to file.
//
//Preconditions: aLL VARIABLES NEED TO BE INITIALIZED AND NEED TO EXIST!
// 
// Postconditions: Receives user input and prints to file the best out of all of the movies. 
void user_choice(int rev[], string titular[], int num, long long int& sum, long double& mean, ofstream& outMovie)
{
	//counter integer
	int i;
	int quantity = 0;
	//prompt user to enter the quantity of movies to be processed
	cout << "\nNow we will give you a list of top movies. Enter the quantity of movies to be processed (0-" << num << "): ";
	//assign the user value to quantity
	cin >> quantity;
	//error checking - check if quantity is negative or above MAX and prompt user for valid response
	//once the correct quantity is input,for loop for the sum
	for (i = 0; i < quantity; i++)
	{
		//get the sum of all of the movie choices
		sum += rev[i];
	}
	//now, call to average function and calculate but with restrictions in place
	if (sum > 0)
	{
		//if the number of movies selected were greater than 0
		mean = average(sum, quantity);
	}
	//now, print out the average income:
	cout << "\nThe average income is: " << mean << endl; 
	outMovie << "The best " << quantity << " of movies\n";
	outMovie << "\n" << setw(6) << "Title\t\t\t\t" << setw(10) << "Income\t" << setw(9) << "Comment\t" << endl;
	//for loop - assign comment to movie based on average
	for (i = 0; i < quantity; i++)
	{
		string str;
		if (rev[i] > mean)
		{
			str = "Above Average";
		}
		else if (rev[i] < mean)
		{
			str = "below average";
		}
		else
		{
			str = "Average";
		}
		//print int to the file
		outMovie << titular[i] << "\t\t\t\t"  << rev[i] << right << "\t" << str << "\n";
	}
	cout << "\nTheBest.txt is ready\n";
}

/**************************************
Function Definitions - Average
**************************************/
double average(long long int sum1, int numPram1)
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
	if (numPram1 <= 0)
	{
		cout << "\nYour data file has no numerical elements or is empty."
			<< "\nDivision by zero error! Closing program now." << endl;
		return 0;
	}
	//Varuables
	long double avg1, sum2, numPram2;
	long long int avg2;

	//Turning into doubles
	sum2 = static_cast<long double>(sum1);
	numPram2 = static_cast<long double>(numPram1);

	avg1 = sum2 / numPram2;

	//Rounding to one decimal place
	avg1 = avg1 * 10.0;
	avg1 = avg1 + 0.5;
	avg2 = static_cast<long long int>(avg1);
	avg1 = static_cast<long double>(avg2);
	avg1 = avg1 / 10.0;

	//Return avg1 to main
	return avg1;
}