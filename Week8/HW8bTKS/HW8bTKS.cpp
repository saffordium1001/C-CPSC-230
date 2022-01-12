/*****************************************************************************
// CPSC 230TR			Fall 2021			HW # 8b
// Twymun Safford
// Last Update Date: 11/16/2021
//
// * Phonebook! - Lesson on Vectors
//
// * Uses parallel arrays to construct a text file containing movies that
// * have made at least 300 million or more. Processes the number of movies
// * that are user selected and renders an average of those values.
****************************************************************************/

/**************************************
Headers
**************************************/
#include <iostream>
#include <vector>
#include <string>
using namespace std;
/*******************************************
Function Prototypes
********************************************/


/*******************************************
Function Prototype - showPhoneBook()
********************************************/
//void showPhoneBook(string N[], int P[], int size); <- old method
//vector implementation of showPhonebook()
void showPhoneBook(vector<string>& N, vector<int>& P);
/*******************************************
Function Prototype - toChoice()
********************************************/
int toChoice(string c);
/*******************************************
Function Prototype - editNum()
********************************************/
//void editNum(string N[], int P[], int size, int c1); <- old method
//vector implementation of editNum()
void editNum(vector<string>& N, vector<int>& P, int size, int c1);
/*******************************************
Function Prototype - add()
********************************************/
//void function to add new name and phone number into vectors
void add(vector<string>& N, vector<int>& P);
/*******************************************
Function Prototype - editNum()
********************************************/
//maximum size permitted to the arrays - comes into play later on
const int MAX = 10;
/*******************************************
Main
********************************************/
int main()
{
	//counter variable for vectors
	unsigned int i;
	//variables
	string eleName;
	int elePhone, choice1;
	string choice;
	//array implementation of names - these will be pushed into the vector (0s for elements other than the first 5 elements - helps to intiailize vector)
	string names_array[MAX] = { "Andrico", "Bonnie", "Charles", "Debbie", "Enrique", "Felicia" };
	//vector implementation of name
	vector<string> name(MAX);
	//array imlementation of phone number array  (0s for elements other than the first 5 elements - helps to intiailize vector)
	int phone_array[MAX] = { 5551234, 5555678, 5552468, 5551379, 5559876, 5554321};
	//vector implementation of the phone array
	vector<int> phone(MAX);
	//copy the values from the arrays into the vectors
	for (i = 0; i < MAX; i++)
	{
		//check if the values are empty for names
		if (names_array[i].empty())
		{
			name[i] = "Null";
		}
		else
		{
			name[i] = names_array[i];
		}
			phone[i] = phone_array[i];
	}
	do
	{
		//call function showPhoneBook
		showPhoneBook(name, phone);

		//get user request
		cout << "\n\nWho\'s phone number do you want to see?" << endl;
		cout << "remember, type \'e\' for edit, type \'a\' for add, and \'x\' for exit, otherwise just type the number of the person." << endl;
		cin >> choice;

		//call function toChoice
		elePhone = toChoice(choice);
		if (elePhone != -1)
		{
			cout << "The phone number for " << name[elePhone] << " is " << phone[elePhone] << ".\n\n\n\n\n\n";
		}
		if (choice == "e")
		{
			cout << "Which entry do you want to edit?  ";
			cin >> choice1;
			//check if the number entered is valid-if the user put in a value within the range of the vector size
			if (choice1 <= name.size())
			{
				editNum(name, phone, name.size(), choice1);
			}
			//else, if they enter a number greater than the current size of the array
			else
			{
				cout << "You entered a value outside of the range of numbers. Instead, we will take the courtesy of adding a new entry for you.  ";
				//add new entry
				add(name, phone);
			}
		}
		//add an entry
		if (choice == "a")
		{
			cout << "We will now be adding an entry.   ";
			//function call to the add function
			add(name, phone);
		}

	} while (choice != "x");

	return 0;
}


/*******************************************
Function Definitions
********************************************/


//print function - for vectors
void showPhoneBook(vector<string>& N, vector<int>& P)
{
//Preconditions: For this function now designed for vectors, the function will receive
//the vector for names and the vector for phone. Both must be passed by reference
//since the user will be updating entries - both vectors have to exist
//
//Postcondition: Prints to the screen the name in the phonebook and the phone number in the phonebook
//from the associated name and number vectors
	unsigned int i;
	for (i = 0; i < N.size(); i++)
	{
		cout << i << " " << N[i] << "\t" << P[i] << endl;
	}
	return;
}

int toChoice(string c)
{
//DO NOT CHANGE/HAS NOT BEEN CHANGED!!!
//Preconditions: User needs to input a string 'c' corresponding to their choice to edit or add records,
// or to quit.
//
//Postcondition: string c is used to direct user to appropriate function to add or edit records
	//num initialized to zero
	int num = 0;
	//if the first character of the string is a digit
	if (isdigit(c[0]))
	{
		//convert it to the corresponding number
		num = stoi(c);
	}
	//else, assign value of -1 
	else
	{
		num = -1;
	}
	return num;
}


void editNum(vector<string>& N, vector<int>& P, int size, int c1)
{
//Preconditions: For this function now designed for vectors, the function will receive
//the vector for names and the vector for phone number. Also receives the entry number of the value for choice entered.
//Vectors are pass by reference while c1 (choice) is by value.
// 
//Postcondition: Edits the name and phone number of the appropriate record.
	//name and string used for names and number
	string name;
	int number;
	//prompt user for name to edit entry
	cout << "What is the name for entry " << c1 << "?: ";
	//take in the new name
	cin >> name;
	//prompt user for number to edit entry
	cout << "What is the number for entry " << c1 << "?: ";
	//take in the number
	cin >> number;
	//overwrite entry c1 with the new name and number
	N[c1] = name;
	P[c1] = number;
	return;
}

void add(vector<string>& N, vector<int>& P)
{
//Preconditions: For this function now designed for vectors, the function will add a new entry
//based upon user-specified name and phone number. To do so, it is dependent upon
//the vectors for name and phone numbers. Both must be passed by reference
//since the user will be adding new entries - means both need to exist and be accessible
//
//Postcondition: Adds to the phonebook directory (vectors name and phone) the new name and new phone number.
	//use string for the name
	string name;
	//use integer for the number
	int number;
	//ask user for name for new entry
	cout << "What is the name for the new entry? ";
	//receive the name
	cin >> name;
	//ask user for number for new entry
	cout << "What is the number for the new entry? ";
	//get number for new entry
	cin >> number;
	//push the new name and number into the vectpr
	N.push_back(name);
	P.push_back(number);
	return;
}