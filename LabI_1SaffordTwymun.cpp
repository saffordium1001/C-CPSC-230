/*********************************************************
* Twymun Saford - 8/23/2021
* CPSC 230 TR
* Lab 1-3: A Simple C++ Program
* Description: This is a simple C++ program for lab 1-3 for
* CPSC 230 TR. It computes the profit made from selling
* soft drinks cases at a rate of 20 cents per bottle and
* also calculates this profit for the year (assuming
* the year is not a leap year).
* This version only considers integer values
*********************************************************/

//Algorithm layout:
// 
//1.) Define the problem:
// 
//* Calculate the profit made from selling
// soft drinks cases at a rate of 20 cents per bottle and
// also calculates this profit for the year(assuming
// the year is not a leap year).

//2.) Define the parameters/variables needed
// 
// Variables:
// 
// BottlesPerCase - the numbers of bottles per case of soda (integer)
// ProfitBottles - profit off each bottle: will be 20 cents (integer)
// numberCases - number of cases sold
// profit - the total profit in cents off cases sold in cents (integer)
// profitYear - the total profit for the year (integer)
// profitDollars - converts the cents to a double for dollars per day
// profitDollarsYear - calculates how many dollars the individual made for the day

//3.) Prompt user for information
//Print message to user to inform them what the program does using cout
//*tell user the program calculates the profit off of each case of soda sold
//Prompt user to enter the number of cases of soda that were sold

//4.) Receive information
//User types in number of cases sold using cin
//Receive number of cases from user through cin statement 

//5.) Calculations
//calculate the profit from the number of cases that were sold
//multiply the number of cases times the number of bottles per case times the profit per bottle
//profit = numberCases * BottlesPerCase * ProfitBottles 

//Then calculate the profit made for the day in dollars
//profitDollars = profit / 100;

//calculate the profits for the year - multiply by 365
//profitYear = profit * 365;

//calculate the profits in dollars for the year. 
//profitDollarsYear = profitDollars * 365;

//6.) Output
// //*Finally, output the profits in cents and dollars for the day and for year to the user 

/// *User should be able to read the final output successfully! 


/**************************************
Main
**************************************/

//First. we need to include iostream since this program functions
//off of user input and the result will be output to the screen visually
#include <iostream>
//We also need to use namespace std
using namespace std;
//program needs int main to run successfully - our program will return
//integer values at the end of execution
int main() 
{
	//declare variables to be used in calculations
	//BottlesPerCase - the numbers of bottles per case of soda (integer)
	//ProfitBottles - profit off each bottle: will be 20 cents (integer)
	int BottlesPerCase = 12, bottleProfit = 20;
	//numberCases - number of cases sold
	//profit - the total profit in cents off cases sold in cents (integer)
	//profitYear - the total profit for the year (integer)
	//profitDollars - converts the cents to a double for dollars per day
	//profitDollarsYear - calculates how many dollars the individual made for the day
	int numberCases, profit, profitYear, profitDollars, profitDollarsYear;
	//Print message to user to inform them what the program does using cout
	cout << "This program calculates the profit from selling soda cases at a profit of 20 cents per bottle." << endl;
	cout << "Please follow the prompts below to continue.\n" ;
	//Prompt user to enter the number of cases of soda that were sold
	cout << "Please enter the number of cases of soda that were sold and press enter:\n";
	//User types in number of cases sold using cin
	cin >> numberCases;
	cout << endl;
	//calculate the profit from the number of cases that were sold
	//multiply the number of cases times the number of bottles per case times the profit per bottle
	profit = numberCases * BottlesPerCase * bottleProfit;
	//calculate the number of dollars this value would be equivalently 
	profitDollars = profit / 100;
	//calculate the profits for the year - multiply by 365
	profitYear = profit * 365;
	//calculate the profits in dollars for the year. 
	profitDollarsYear = profitDollars * 365;
	//tell the user the profit that they made first in cents per day,
	cout << "When you sold " << numberCases << " cases you made " << profit << " cents per day. " ;
	//,in dollars per day
	cout << "This is equivalent to " << profitDollars << " dollars per day.\n" ;
	//,in cents per year
	cout << "Assuming this isn't a leap year, you made " << profitYear << " cents for the year. " ; 
	//, and finally convey in dollars per year. 
	cout << "This is equivalent to " << profitDollarsYear << " dollars per year.\n" ;
	return 0;
}