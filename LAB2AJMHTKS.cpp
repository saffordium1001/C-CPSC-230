//***********************************************************
//CPSC 230 TR Fall 2021             Lab 2A
//Twymun Safford
//Justin Hutmacher
//Lab 2A - Calculator for acceleration
// Calculates the acceleration required by a vehicle to reach
// a certain speed based on the time frame it has to do it
// Uses input, output, and type-casting
// Inputs are speed and time
// Constant value is a double that converts from mph to mps
// Output is acceleration
//**********************************************************

//Algorithm layout:
// 
//1.) Define the problem:
// 
//* Need to calculate the acceleration needed to reach
// 
//a certain speed based on a time frame

//2.) Define the parameters/variables needed
// 
// Variables:
// 
// * Constant conversion factor (MPH2MPS): convert from miles per hour
// to meters per second
// 
//absolutely required!
// 
// * 'v': What speed is the vehicle trying to reach (miles per hour)
// * 't': How long does it have to reach this speed (seconds)
// * 'a': How much acceleration does the vehicle need to reach this speed

//3.) Prompt user for information
//Use logo/text box to inform user about program
//Inform user of inputs needed - 'v' and 't'
// 
//Prompt user for 'v'
// 
//Prompt user for 't'

//4.) Receive information
// *Receive'v' from user
// 
// *Receive 't' from user

//5.) Calculations
//* Convert from miles per hour to meters per second - have const double for that
// MPH2MPS is 1609.0/3600.0
// 
//* Calculate acceleration as a = MPH2MPS * (v/t)
// 
// * Need to calculate as double precision - round off to one digit but display as two digits
// 
// * Multiply acceleration result first by 10
// 
// * add 0.5 to acceleration to create decimal place 
// 
// * convert acceleration result to an integer by using static cast and another variable name
// 
// * convert this number to a double and then divide by 10 to get the final decimal value

//6.) Output
// //*Finally, output acceleration to user needed
// 
// //Values need to be doubles with two decimal pts. - even though they came in as one
// 
//* The results need to be output on several lines
// 
//* Line 1 comment - "acceleration required.. (for 'a')"
// 
//*insert new lines as need to be to communicate v, t, and so forth

/// *User should be able to read the final output successfully! 

//input/output stream
#include <iostream>
//include ionmanip - for setting decimal precision 
#include <iomanip>
//namespace
using namespace std;

//constant double MPH2MPS - convert mps to meters per second
const double MPH2MPS = 1609.0 / 3600.0;
/**************************************
Main
**************************************/
int main()
{
	//define variables
	//'v' - speed/velocity (in MPH)
	// 
	//'t' - time (in seconds)
	// 
	//'a' - acceleration (meters/s^2)
	double v, t, a;
	//optional border around program explanation
	cout << "**********************************************************************" << endl;
	//use a new line to separate the border line above from the program name below
	cout << "*                                                                    *" << endl;
	//describe what the program does 
	cout << "*                   Acceleration Program                             *" << endl;
	cout << "* This program calculates the acceleration needed by a vehicle to    *" << endl;
	cout << "* reach a certain speed within a given time frame. The speed is      *" << endl;
	cout << "* accepted in miles per hour and the time is accepted in seconds.    *" << endl;
	cout << "* After each prompt, enter your value (as a number) and press enter. *" << endl;
	//don't forget tp include a new line here
	cout << "*                                                                    *" << endl;
	//finish here by enclosing the initials inside another border 
	cout << "**********************************************************************" << endl;

	//* Use cout to ask for and cin statement to receive speed in mph from user
	cout << "Please enter the velocity the car needs to reach in miles per hour and \npress enter:" << endl;
	cin >> v;
	//* Use cout to ask and cin statement to receive time in seconds from user
	cout << "\nPlease enter the time it has to do so in seconds and press enter:" << endl;
	cin >> t;

	//* Convert from miles per hour to meters per second - have const double for that defined above
	//* Calculate acceleration as a = MPH2MPS * (v/t)
	a = MPH2MPS * (v / t);
	// * Need to calculate as double precision - round off to one digit but display as two digits
	//first, mutiply by 10
	a *= 10;
	//add 0.5 to create decimal place
	a += 0.5;
	//convert number to an integer by using static cast and assigning a variable to hold value
	int acceleration_recast = static_cast<int>(a);
	//convert this number to a double and then divide by 10 to get the double
	a = static_cast<double>(acceleration_recast) / 10;
	//* Line 1 comment - "acceleration required.."
	cout << "\nThe acceleration required by a vehicle to reach" << endl;
	//*insert new line as need - to reach speed in miles per hour based on time in secs
	cout << "a velocity of " << setprecision(2) << fixed << showpoint << v << " miles per hour in " << t << " second(s)" << endl;
	//report this acceleration out with units
	cout << "is " << a << " meter(s) per second squared.\n";
	// return statement
	return 0;
}