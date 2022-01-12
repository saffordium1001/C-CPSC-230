/*****************************************************************************
// CPSC 230TR			Fall 2021			HW # 9b
// Twymun Safford
// Last Update Date: 11/21/2021
//
// * Letter to Santa
//
// * Program that uses strings and arrays to construct a program to write a
// *letter to Santa asking for gifts. 
****************************************************************************/

/*******************************************
Function Prototypes
********************************************/

/**************************************
Headers
**************************************/
//input output stream
#include <iostream>
//strings
#include <string>
//input/output manipulation
#include <iomanip>
using namespace std;

/*******************************************
Function Prototype - Scanner
********************************************/
//function to expand space in array dynamically
//and to allow users to enter a series of gifts
void Scanner(string* items, int size);

/*******************************************
Function Prototype - Printer
********************************************/
//function to expand space in array dynamically
//and to allow users to enter a series of gifts
void Printer(string* items, int size, string name);

int main()
{
    //variable declarations
    int numGifts; //used for cin for number of gifts user thinks they deserve
    string name; //holds the users name
    //get input from user for name
    cout << "Hello, please enter your name: " << endl;
    //use getline to get the user's name - could be spaces or could be first name/last name
    getline(cin, name);
    //have user enter the number of gifts
    cout << "Please enter the number of gifts you think you deserve: " << endl;
    cin >> numGifts;
    //declare dynamic array - uses pointers
    string *listGifts = new string[numGifts];
    //call the function
    Scanner(listGifts, numGifts);
    //display the message
    Printer(listGifts, numGifts, name);
    //free allocated memory
    delete[] listGifts;
    return 0;
}


/*******************************************
Function Definition - Scanner()
********************************************/
//function to expand space in array dynamically
//and to allow users to enter a series of gifts
void Scanner(string *items, int size)
{
    //counter variable
    int i;
    for (i = 0; i < size; i++)
    {
        //print statement to ask user to enter item number
        cout << "Please enter gift number " << (i + 1) << "and press enter: " << endl;
        //input from keyboard
        string temp;
        cin.ignore();
        getline(cin, temp);
        items[i] = temp;
    }
    return;
}

/*******************************************
Function Prototype - Printer
********************************************/
//function to expand space in array dynamically
//and to allow users to enter a series of gifts
void Printer(string *items, int size, string name)
{
    //counter variable
    int i;
    //print out the message
    cout << "\t\nDear Santa, \n \t \t I have been extra good this year.\n\t I believe I've earned " << size
        << " presents.\n \t Thank you for not leaving them on the porch.\n\t\tHere is my list : " << endl;
    for (i = 0; i < size; i++)
    {
        cout << "\t\t" << i + 1 << ") " << items[i] << endl;
    }
    cout << "\t\t\t-" << name << endl << endl;
    //return
    return;
}