//Phone Book
//
//Rodger Irish

#include <iostream>
#include <string>

using namespace std;

//Prototypes
void showPhoneBook(string N[], int P[], int size);
int toChoice(string c);
void editNum(string N[], int P[], int size, int c1);
const int MAX = 10;
int main()
{
	//variables
	string eleName;
	int elePhone, choice1;
	string choice;
	string name[MAX] = { "Andrico", "Bonnie", "Charles",
						"Debbie", "Enrique", "Felicia" };
	int phone[MAX] = { 5551234,
						5555678,
						5552468,
						5551379,
						5559876,
						5554321 };


	do
	{
		//call function showPhoneBook
		showPhoneBook(name, phone, MAX);

		//get user request
		cout << "\n\nWho\'s phone number do you want to see?" << endl;
		cout << "remember, type \'e\' for edit and \'x\' for exit, otherwise just type the number of the person." << endl;
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
			editNum(name, phone, MAX, choice1);
		}
	} while (choice != "x");

	return 0;
}

//print function
void showPhoneBook(string N[], int P[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << i << "  " << N[i] << "\t" << P[i] << endl;
	}
	return;
}

int toChoice(string c)
{
	int num = 0;
	
	if (isdigit(c[0]))
	{
 		num = stoi(c);
	}
	else
		num = -1;
	return num;
}

void editNum(string N[], int P[], int size, int c1)
{
	string name;
	int number;
	cout << "What is the name for entry " << c1 << "?:  ";
	cin >> name;
	cout << "What is the number for entry " << c1 << "?:  ";
	cin >> number;

	N[c1] = name;
	P[c1] = number;
	return;
}