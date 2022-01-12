///*****************************************************************************************************
// CPSC 230TR			Fall 2021			HW # 8a
// Twymun Safford
// Last Update Date: 11/16/2021
//
// * C-Strings and Strings
//
// * Series of programs to use functions related to strings and C-strings for reading and decoding
// *lines of text - uses pointers
//******************************************************************************************************/

/**************************************
Headers
**************************************/
#include<iostream>
#include<cstring>
#include<string>
#include<cctype>
#include<vector>
using namespace std;

/**************************************
Function Declarations - Frequency of Characters
**************************************/
//counts the frequency of each character from a sentence
void countFrequency(string text, int frequency[26]);
//sorting the frequency from higher to lower.
void sortFrequency(int frequency[], char letters[]);

/**************************************
Function Declarations - Message Decryption
**************************************/
//used to filter the characters
bool filter(const char& chr);
//used to descrypt the message
string decryptedString(const string& secret, int key);


/*******************************************
Main
********************************************/
int main()
{
	//integer to initiate running process
	char run_again = 'Y';
	char choice;
	do {
		std::cout << "Please enter a letter from one of the following options and press enter : " << endl;
		cout << "****************************************************************" << endl;
		cout << "*   A) Frequency of Characters                                 *" << endl;
		cout << "*   B) Decode Message                                          *" << endl;
		cout << "****************************************************************" << endl;
		std::cin >> choice;
		//character- used to assess if user wants to enter another word
		choice = toupper(choice);
		switch (choice)
		{
			/**************************************
			Case 1 - User Wants to Figure out Number of Word
			**************************************/
			//case 1 - the user wants to know how to play the game
		case 'A':
		{
			char anotherword = 'Y';
			do {
				//introduce user to the program
				cout << "**********************************************************************" << endl;
				//use a new line to separate the border line above from the program name below
				cout << "*                                                                    *" << endl;
				//describe what the program does 
				cout << "*                    'Frequency of Characters'                       *" << endl;
				cout << "*  This program will read in a sentence (string) and then output     *" << endl;
				cout << "*  the number of words in each line and the number of occurences     *" << endl;
				cout << "*  of each character.                                                *" << endl;
				cout << "**********************************************************************" << endl;
				cin.ignore();
				int frequency[26]; //array for store frequency of each letter.
				char letters[26]; //array for 26 alphabets.
				string text; // input text
				int i; //counter variable
				int wordCount = 0;
				//initializing arrays.
				for (i = 0; i < 26; i++)
				{
					frequency[i] = 0; //initializing frequency of each alphabet to 0.
					letters[i] = i + 97; //storing 26 alphabets - based on ASCII
				}
				cout << "Enter your sentence please: "; //prompting to enter text.
				getline(cin, text); //reading the text.
				//converting upper letters to lower letters.
				for (i = 0; text[i]; i++)
				{
					text[i] = tolower(text[i]);
				}
				//cases where we can assess/determine the number of words there are in the sentence based on characters
				for (i = 0; i < text.size(); i++)
				{
					if (((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'a' && text[i] <= 'z')) && (text[i + 1] == '.' || text[i + 1]
						== ',' || text[i + 1] == ' '))
					{
						wordCount++;
					}
				}
				//character x - used to determine what characters are in the senetence
				char x = text[text.size() - 1];
				//
				if (x != '.' && x != 'z' && x != ' ')
				{
					wordCount++;
				}
				countFrequency(text, frequency); //calling the function to count the frequency.
				sortFrequency(frequency, letters); //calling the function to sort the frequency from higher to lower.
				//print statement - number of words and number of each kind of character
				cout << "\n\n There are " << wordCount << " word(s)." << endl;
				cout << "\n\nCount\tLetters" << endl;
				cout << "===================" << endl;
				//for the number of characters
				for (i = 0; i < 26; i++)
				{
					//word counts
					if (frequency[i] > 0)
					{
						cout << frequency[i] << "\t" << letters[i] << endl;
					}
				}
				//tell user they can enter another string
				cout << "Would you like to enter another sentence? Select Y for yes or press any other key to end." << endl;
				//get user input
				cin >> anotherword;
				anotherword = toupper(anotherword);
				//while condition
			} while (anotherword == 'Y');
			break;
		}
		//for the second program, assesses if the user wants to decode the message coming from enemy secret code
			/**************************************
			Case 2 - User Wants to Decode a message
			**************************************/
		case 'B':
		{
			char decodeagain = 'Y';
			do {
				cout << "**********************************************************************" << endl;
				//use a new line to separate the border line above from the program name below
				cout << "*                                                                    *" << endl;
				//describe what the program does 
				cout << "*                    'Message Decoder'                               *" << endl;
				cout << "*  This program will decode from a secret string of characters       *" << endl;
				cout << "*  the enemy is using to send messages back and forth.               *" << endl;
				cout << "**********************************************************************" << endl;
				cin.ignore();
				int i; //counter variable
				string decryptedString(const string & secret, int key);
				string secretMsg = ":mmZ\\dxZmx]Zpgy";
				cout << "\nThe original undecoded message was: " << secretMsg;
				int key;
				//holds the number of correct attempts - initialize to zero
				int attempts = 0;
				char user_input; //user input to confirm if the decryption makes sense
				int coherent_select = 0; //number of picks the user selected as coherent
				vector<string> decoded; //vector to hold the decoded strings
				vector<int> keys; //vector to hold key numbers
				for (key = 1; key < 101; ++key)
				{
					string result = decryptedString(secretMsg, key);
					//rather than wasting time, only consider those keys which have values
					if (result.length() > 0)
					{
						++attempts;
						cout << "\nAttempted decryption for key number " << key << " - "
							<< result
							<< endl;
						cout << "\nIs this attempt coherent? Enter 'Y' for (Yes) or any other key to continue." << endl;
						cin >> user_input;
						user_input = toupper(user_input);
						//if user input is yes, then tell them the key they selected
						if (user_input == 'Y')
						{
							coherent_select++;
							cout << "\nThe key " << key << " you selected has the following decoded message: " << result << endl;
							//add the result into the vector
							decoded.push_back(result);
							//add the key into the vector keys
							keys.push_back(key);

						}
					}
				}
				//print sttaement for keys and decoded strings
				cout << "\nYou selected " << coherent_select << " results as being coherent. Your selections were: " << endl;
				for (i = 0; i < coherent_select; i++)
				{
					cout << "\nKey number: " << keys[i] <<"\t" << "Decoded message: " << decoded[i] << endl;
				}
				//if none were decrypted sucessfully or no decrypted string have meaning, update the filter"
				cout << endl;
				//cin.get();
				//tell user they can enter another string
				cout << "Would you like to decode this message again? Select Y for yes or press any other key to end." << endl;
				//get user input
				cin >> decodeagain;
				decodeagain = toupper(decodeagain);
				//while condition
			} while (decodeagain == 'Y');
			break;
		}
		//default case
		default:
		{
			cout << "Invalid entry!" << endl;
			break;
		}
		}
		//tell user they can play the program again
		cout << "Would you like to run this program again? Select Y for yes or press any other key to end." << endl;
		//get user input
		cin >> run_again;
		run_again = toupper(run_again);
	} while (run_again == 'Y');
	return 0;
}


/**************************************
Function Definitions- Character Frequency
**************************************/
void countFrequency(string text, int frequency[26])
//function to count the frequency of each character.
{
	//counter integer
	int i;
	for (i = 0; text[i]; i++) //read every character in word.
	{
		if (isalpha(text[i])) //if character is a alphabet.
		{
			frequency[(int)text[i] - 'a']++; //incrementing the count of each character in array.
		}
	}
}
void sortFrequency(int frequency[], char letters[])
//sorting the frequency from higher to lower.
{
	int i, j;
	int n = 26;
	int temp;
	char let;
	//sorting using bubble sort.
	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			if (frequency[j] < frequency[j + 1])
			{
				//swapping frequency.
				temp = frequency[j];
				frequency[j] = frequency[j + 1];
				frequency[j + 1] = temp;

				//swapping letters.
				let = letters[j];
				letters[j] = letters[j + 1];
				letters[j + 1] = let;
			}
		}
	}
}

/**************************************
Function Definitions- Boolean Filter
**************************************/
bool filter(const char& chr)
{
	return (toupper(chr) >= 'A' && toupper(chr) <= 'Z') || //a-z A-Z
		(chr >= '0' && chr <= '9') ||                   //0-9
		(chr == ' ' || chr == '\t' || chr == '\n') || //white spaces
		(chr == ',' || chr == '.' ||                  //punctuations
			chr == ':' || chr == ';' ||
			chr == '\'' || chr == '\"' ||
			chr == '?' || chr == '!');
}

/**************************************
Function Definitions- Decryption
**************************************/
string decryptedString(const string& secret, int key)
{
	int i;
	string decoder = "";
	for (i = 0; i < secret.length(); i++)
	{
		if (filter(secret[i] - key))
			decoder += secret[i] - key;
		else if (filter(secret[i] - key + 127 - 32))
			decoder += secret[i] - key + 127 - 32;
	}
	if (decoder.length() == secret.length()) //All encrypted chars must be decrypted
		return decoder;
	return decoder = "";
}