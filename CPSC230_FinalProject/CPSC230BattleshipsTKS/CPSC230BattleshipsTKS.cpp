/********************************************************************************************************
// CPSC 230TR			Fall 2021			Final Project
// Twymun Safford
// Last Update Date: 11/15/2021
//
// * Battleships!!!
//
// * C++ Implementation of the Game 'Battleships' for the final project for
// * for CPSC 230.
//
// * This project is based on the game Battleship (termed 'Battleships' here to avoid
// * issues with infringement). The game in its current state is a human vs CPU game where the objective of 
// * the user is to sink the CPU's fleet after placing their fleet (randomly or manually). The game ends if 
// * the player quits, wins, or loses.
// * The AI for the CPU had to be randomly generated based on inspiration from various texbooks and
// * algorithms which were accessible. These are referenced within the subject matter report. 
// *
// * This program utilizes various subject matter, criteria, and tools taught in CPSC 230.
*****************************************************************************************************/

/********************************************************************************************************
//PREFACE ARGUMENT - USING STACKS:
// I referenced websites such as GeeksforGeeks and Stack Overflow.
//Stacks from what I was able to find are a special class of container adapter
//that functions like a vector but isn't quite a vector (vectors can be stacks but stacks can't be vectors).
// The order in which operations in a stack are peformed are 'LIFO' -last in, first out.
// The stack stores members as elements and while it wouldn't be as flexible as a vector,
// for me I feel like it  would be the systematic approach I needed to implement for push, pop, or top
// depending on what the stack needed to accomplish for the AI.  I didn't want the AI's actions
//to be accessible to user influence. Additionally, I wanted to constrain actions by the AI - I wanted to guarantee
//that if the last operation in was a matter of choosing. Since the push_back.() function was similar enough, it
// provided some grounding and basis for this program.
//
// I used the push, pop, and top operations with stacks to get a functional AI. By reference (notes for myself):
//
//Push: Adds an item in the stack. If the stack is full then I need to watch for overflow
//
//Pop: Removes an item from the stack.The items are popped in the reversed order in which they are pushed.If the stack is empty,
//then I need to be wary of underflow
//
//Top : Returns the top element of the stack.
***************************************************************************************************** /

/**************************************
Headers
**************************************/
//input/output stream
#include <iostream>
//for random seeds
#include <cstdlib>
//for math libraries
#include <cmath>
//strams for files and strings
#include <fstream>
#include <sstream>
#include <string>
//input and output manipulation
#include <iomanip>
//stacks
#include <stack>
#include <ctime>
using namespace std;

/*********************************************
Constant Variables - Maximum Size of the Board
*********************************************/
//maximum size of the board will be a 15 x 15 board for play
const int MAX_ROWS = 15;//Maximum length of the rows: Rows are labeled: A-O
const int MAX_COLS = 15;//Maximum length of the columns: Columns are labeled:  1-15

/*******************************************
Function Prototype  - Game Instructions
********************************************/
//displays the logo
void LogoDisplay();

/*******************************************
Function Prototype  - Game Instructions
********************************************/
//displays the user menu choices
void DisplayMenu();

/*******************************************
Function Prototype  - Game Instructions
********************************************/
//provides game instructions to user
void GameInstruct(ifstream& gameInstructions);

/****************************************************
Function Prototype  - Initializing the Game Board
****************************************************/
//initializes the game boards
void initializeBoards(char attackBoard[][MAX_ROWS], char shipBoard[][MAX_ROWS], char enemyBoard[][MAX_ROWS]);

/****************************************************
Function Prototype  - Display Game Boards (enemy)
****************************************************/
//displays the game boards for the enemy
void displayBoards(char[][MAX_ROWS], char[][MAX_ROWS]);

/****************************************************
Function Prototype  - Display User Board
****************************************************/
//displays the users game boards
void displayPlayerBoard(char[][MAX_ROWS]);

/****************************************************
Function Prototype  - Place Ships
****************************************************/
//places the ships on the board for both the player and the enemy
void placeEnemyShips(char[][MAX_ROWS]);
void placePlayerShips(char[][MAX_ROWS]);

/****************************************************
Function Prototype  - Attack!
****************************************************/
//function for user and enemy to attack
void attack(char[][MAX_ROWS], char[][MAX_ROWS], char[][MAX_ROWS], int[]);
/****************************************************
Function Prototype  - RevPush
****************************************************/
void revPush(int, int, char);
/****************************************************
Function Prototypes  - Clear and Pause
****************************************************/
//user designed functions clear and pause
//clear essentilly clears the screen of the previous board status
//pause will 'pause' the screen for clarity so the user can look at the board currently
void clear();
void pause();
/****************************************************
Function Prototypes  - Do the Ships Overlap
****************************************************/
//checks to see if a user's placement would overlap with one of their current ships
//also is a nice check to prevent the enemy from experiencing overlap as well
bool isShipsOverlap(char[][MAX_ROWS], int, int, int, int);
/****************************************************
Function Prototypes  - Player Hit
****************************************************/
//function that determines if the player hit the enemy's ship
//and updates board with this information accordingly
char didHit(char[][MAX_ROWS], int, int);
/****************************************************
Function Prototypes  - Random Hit AI
****************************************************/
//function that initiates a random hit from the enemy ship
//assesses if it hit, and returns the updated symbols based on this
char hitRandom(char[][MAX_ROWS], char[][MAX_ROWS], bool&, bool&, bool&, int&, int&, int&, stack <int>&, stack <int>&, stack <char>&);
/************************************************************
Function Prototypes  - Converts Character Input to Number
************************************************************/
//converts the user's character assignment for the
int charToNum(char);
/*************************************************************
Function Prototypes  - Converts Ships to Represented Numbers
*************************************************************/
int shipToNum(char);

/*************************************************************
Main()
*************************************************************/
int main()
{
	//srand: will not use current time as seed for random generator for enemy AI and randomly generated ship placement
	srand(time(NULL));
	//pre-game boards
	//ship arrays based on how many spaces they take up and health for player and enemy
	int playerHealth[] = { 5, 4, 3, 3, 2 };
	int enemyHealth[] = { 5, 4, 3, 3, 2 };
	string shipNames[] = { "Aircraft Carrier", "Battleship", "Submarine", "Cruiser", "Destroyer" };
	//string to hold user's namegoogl
	string username;
	//user continue game variable - playagain starts at Y but can become no if user chooses so
	char playagain = 'Y';
	//variable for input stream for instruction file
	ifstream instructions;
	//name of the instruction files
	string input_file = "Battleship.txt";
	//usergame choice - symbolized by number
	int user_gamechoice;
	//the direction variable for the AI
	int AIDir = -1;
	//set to false by default until the CPU makes a move - once true, CPU will generate a set of instructions for AI to follow
	bool shouldUseLogic = false;
	//boolean - multiple ships left on the game board. set to false if 1 or no ships are left, set to true otherwise
	bool isMultipleShips = false;
	//did the AI already hit the ship? false if not, true if they did
	bool AIPrevHit = false;
	//counter variable for the number of ships
	int numOfShips = 0;
	//ships left for either the CPU or the player - starts at 5 and decrements if a ship is sank by either side
	int shipsLeft;
	//AI ends starts at 0 - the condition to ends the AI's turn is 2 (see below)
	int AIEnds = 0;
	//stacks for x and y coordinate positions
	stack <int> xStack;
	stack <int> yStack;
	//stack for the direction
	stack <char> dirStack;
	//do-while loop here - for the case where the user wants to play the game again or view instructions again
	//greet user and ask for their name
	std::cout << "\nHello and welcome to Battleships! What's your name: " << endl;
	//get user name using getline
	getline(std::cin, username);
	//get user's game choice
	std::cin.ignore();
	//tell user press enter to continue
	std::cout << "\nNow press enter to continue. " << endl;
	do
	{
		//introduce user to the program using ASCII logo
		LogoDisplay();
		//tell user about program options
		std::cout << "Welcome, " << username << " . Please enter a number from one of the following options and press enter: " << endl;
		//display game menu
		DisplayMenu();
		std::cout << "\n\n" << endl;
		std::cin >> user_gamechoice;
		//check if the user's entry was valid
		if ((user_gamechoice != 1) && (user_gamechoice != 2) && (user_gamechoice != 3))
		{
			//if it does not match, then assign value for default case
			user_gamechoice = 10;
		}
		switch (user_gamechoice)
		{
			/**************************************
			Case 1 - User Wants to Know How to Play
			**************************************/
			//case 1 - the user wants to know how to play the game
		case 1:
		{
			//open input file
			instructions.open(input_file, ios::in);
			//if the file failed to open, instructions not found. Still allow user to play the game
			if (instructions.fail())
			{
				//if the instructions for the file could not be found, tell user and use the break case below to go back to the menu
				std::cout << "\nOops! Could not find the instructions for Battleships! Please check the location or file name. Going back to the main menu.\n" << endl;
			}
			else
			{
				//make function call to the read instructions function - instructions should print to screen
				std::cout << "\n";
				GameInstruct(instructions);
			}
			break;
		}
		/**************************************
		Case 2 - Playing the Game!
		**************************************/
		//case 2 - player wants to play the game
		case 2:
		{
			char attackBoard[MAX_ROWS][MAX_COLS]; //attack board
			char shipBoard[MAX_ROWS][MAX_COLS]; //the player shipboard
			char enemyBoard[MAX_ROWS][MAX_COLS]; //the enemy shipboard

			char hit; //for player or enemy hits
			bool done = false; //checks if the player is done or the enemy is done
			bool didSink = false; //did the ship sink? only sets to true once the sink has run out of hits it can take
			bool playerWin = false; //did the player win?
			bool enemyWin = false; //did the player lose?
			int i; //counter for the for loop for ships and various other functions
			//since we are playing the game, generate the game boards for the player and enemy
			initializeBoards(attackBoard, shipBoard, enemyBoard);
			placeEnemyShips(enemyBoard);
			placePlayerShips(shipBoard);
			//self-created clear function
			clear();
			//display the boards for the user's boards and the attacked board every time a turn is taken by either
			displayBoards(attackBoard, shipBoard);
			std::cout << "\n\n\n";
			std::cout << "Press enter to continue...";
			std::cin.get();
			std::cin.get();
			clear(); //clears the screen to update the board for the next round of computer move -> player move
		/**************************************
		CPU Actions and AI - Start Here
		**************************************/
		//while the game has not finished - the flag for the game finished 'done' does not trigger during play until the user's or CPU's entire fleet gets sunk
			while (!done)
			{
				//clear the board again
				clear();
				//CPU goes first - initiates a random hit to the player
				hit = hitRandom(shipBoard, attackBoard, shouldUseLogic, isMultipleShips, AIPrevHit, numOfShips, shipsLeft, AIEnds, xStack, yStack, dirStack);
				//if one of the player's ships in their fleet were hit
				if (hit != '#')
				{
					//if the CPU did not miss, then count it as an attack
					int hitNum = shipToNum(hit);
					//now subtract a point of health from that player's ship
					playerHealth[hitNum]--;
				}
				//counter for the loop that checks on the health of each ship
				for (i = 0; i < 5; i++)
				{
					//if one of the player's ships has been struck and is out of hit points
					if (playerHealth[i] == 0)
					{
						//pause for clarity for user
						pause();
						//display updated boards
						displayBoards(attackBoard, shipBoard);
						//tell the user that the enemy sunk their ship
						std::cout << "\n\nThe enemy sunk your " << shipNames[i] << ", " << username << "!\n";
						//set health to -1 - the ship has been sunk and is not recoverable
						playerHealth[i] = -1;
						//if there are multiple ships in play (i.e. there are still ships and the player can still play)
						if (!isMultipleShips)
						{

							//stacks are set up for the purpose of the CPU to use for their moves - initialized back to empty since CPU has executed moves
							xStack = stack<int>(); //stack for the move at the y position
							yStack = stack<int>(); //stack for the move at the x position
							dirStack = stack<char>(); //stack for the direction
							shouldUseLogic = false; //CPU shouldn't have to worry about using logic once a move has been launched
							//for the sake of ending the AI when the CPU is done, the AI recognizes that it shouldn't move again
							AIPrevHit = false; 
							numOfShips = 0; //number of ships AI targets now reset back to zero until next turn
							shipsLeft = 0; //number of ships left to target down to 0 until reinitialized within loops
							AIDir = -1; //
							AIEnds = 0; //AI back to 0
						}
						//the player lost a ship
						else
						{
							shipsLeft--;
							//if after that ship has been destroyed,then 
							if (shipsLeft == 0)
							{
								//stacks are set up for the purpose of the CPU to use for their moves - initialized back to empty since CPU has executed moves
								xStack = stack<int>(); //stack for the move at the y position
								yStack = stack<int>(); //stack for the move at the x position
								dirStack = stack<char>(); //stack for the direction
								shouldUseLogic = false; //CPU shouldn't have to worry about using logic once it has launched a move
								//for the sake of ending the AI when the CPU is done, the AI recognizes that it shouldn't move again - this time, it's to end the game
								AIPrevHit = false;
								numOfShips = 0;
								shipsLeft = 0;
								AIDir = -1;
								AIEnds = 0;
							}
						}
						//true whether this sinking ship causes the player to lose the game or they lose one of the ships in their fleet
						didSink = true;
					}
				}
				//whether the ship sank or not, player has to press enter after the CPU's actions to move on to their turn 
				if (didSink)
				{
					std::cout << "Press enter to continue...";
					didSink = false;
				}
				else
				{
					std::cout << "Press enter to continue...";
				}
				std::cin.get();
				/**************************************
				Player's Actions Start Here
				**************************************/
				//THIS IS WHERE THE PLAYER'S TURNS NOW TAKE PLACE - LOOK AT THESE ACCORDINGLY
				attack(shipBoard, attackBoard, enemyBoard, enemyHealth);
				for (i = 0; i < 5; i++)
				{
					if (enemyHealth[i] == 0)
					{
						clear();
						displayBoards(attackBoard, shipBoard);
						std::cout << "\n\nYou sunk the enemy's " << shipNames[i] << "!\n";
						enemyHealth[i] = -1;
						std::cout << "Press enter to continue...";
						std::cin.get();
					}
				}
				/**************************************
				Win and Loss Conditions Assessed Here
				**************************************/
				//set true for both by default but changed to false for the corresponding lose
				playerWin = true;
				enemyWin = true;
				//check if each ship has been sank - if all ships for player or CPU are marked as -1, game is over
				for (i = 0; i < 5; i++)
				{
					if (playerHealth[i] != -1)
					{
						enemyWin = false;
					}
					if (enemyHealth[i] != -1)
					{
						playerWin = false;
					}
				}
				//the games ends once the player wins or the enemy wins
				if (playerWin || enemyWin)
				{
					done = true;
				}
			}
			clear();
			//tell the user that they won
			if (playerWin == true)
			{
				//include username
				std::cout << "Congratulations, " << username << "! You Won!";
			}
			//tell user that they lost
			else
			{
				//print message to screen
				std::cout << "Sorry, " << username << " you lost. Try again..?";
			}
			//break out to the option to play the game again and ask if they would like to
			break;
		}
		/**************************************
		Case 3 - Quit
		**************************************/
		//case 3 - player wants to quit
		case 3:
		{
			std::cout << "\nHope to see you again soon, " << username << "!" << endl;
			return 0;
			break;
		}
		/**************************************
		Default() Case
		**************************************/
		default:
		{
			std::cout << "\nThat wasn't a valid entry!" << endl;
			break;
		}
		/**************************************
		Prompt Player to Play Again
		**************************************/
		//ask user if they would like to play again 
		cout << "Would you like to try again? Select (Y) for yes or press any other key to end." << endl;
		//get user input
		cout << " " << endl;
		cin >> playagain;
		//take even user input that is lowercase by converting to upper
		playagain = toupper(playagain);
		//while condition
		if (playagain != 'Y')
		{
			//tell user see them later
			cout << "\nThank you for playing, " << username << "! Come back soon!" << endl;
		}
		}
	} while (playagain == 'Y');
	//return - end main function 
	return 0;
}

/*******************************************
Function Defintiion  - Logo Display
********************************************/
//The main game logo. This displays each time the user boots up the program/game after entering their name or after choosing to play the game again.
//
//Preconditions: User has to have entered their name successfully. Logo will display afterwards
// 
// Postconditions: Logo displays to inform user that this is a battleships game - user will then see the menu beneath the logo
void LogoDisplay()
{
	cout << "*******************************************************************************************************************" << endl;
	cout << "*   /$$$$$$$              /$$     /$$     /$$                     /$$       /$$                     /$$ /$$ /$$   *" << endl;
	cout << "*  | $$__  $$            | $$    | $$    | $$                    | $$      |__/                    | $$| $$| $$   *" << endl;
	cout << "*  | $$  \ $$  /$$$$$$  /$$$$$$ /$$$$$$  | $$  /$$$$$$   /$$$$$$$| $$$$$$$  /$$  /$$$$$$   /$$$$$$$| $$| $$| $$    *" << endl;
	cout << "*  | $$$$$$$  |____  $$|_  $$_/|_  $$_/  | $$ /$$__  $$ /$$_____/| $$__  $$| $$ /$$__  $$ /$$_____/| $$| $$| $$   *" << endl;
	cout << "*  | $$__  $$  /$$$$$$$  | $$    | $$    | $$| $$$$$$$$|  $$$$$$ | $$  \ $$| $$| $$  \ $$|  $$$$$$ |__/|__/|__/     *" << endl;
	cout << "*  | $$  \ $$ /$$__  $$  | $$ /$$| $$ /$$| $$| $$_____/ \____  $$| $$  | $$| $$| $$  | $$ \____  $$                  *" << endl;
	cout << "*  | $$$$$$$/|  $$$$$$$  |  $$$$/|  $$$$/| $$|  $$$$$$$ /$$$$$$$/| $$  | $$| $$| $$$$$$$/ /$$$$$$$/ /$$ /$$ /$$   *" << endl;
	cout << "*  | _______ / \_______ / \___ / \___/  |__ / \_______/|_______/ |__/  |__/|__/| $$____/ |_______/ |__/|__/|__ /      *" << endl;
	cout << "*                                                                              | $$                               *" << endl;
	cout << "*                                                                              | $$                               *" << endl;
	cout << "*                                                                              |__/                               *" << endl;
	cout << "*******************************************************************************************************************" << endl;
	return;
}

/*******************************************
Function Definition  - Display Menu
********************************************/
//Displays the menu at the start of the game/after starting a new round to let the user know what their options are
//
//Preconditions: User has already seen the game logo and is deciding on whether to read how to play the game,
// to play the game itself, or to quit.
// 
// Postconditions: Menu will display - will not display once the user makes a selection, but will display if the user decides to play the game again.
void DisplayMenu()
{
	cout << "****************************************************************" << endl;
	cout << "*   1.) How do I play Battleships?                             *" << endl; //to inform user on how to play the game
	cout << "*   2.) Play!                                                  *" << endl; //plays the game but is limited to player vs CPU
	cout << "*   3.) Press '3' and enter to quit                            *" << endl; //provide user the option to quit the game
	cout << "****************************************************************" << endl;
	return;
}



/*******************************************
	Function Definition  - Game Instructions
********************************************/
//Prints from the input file the instructions on how to play this C++ implementation of the game Battleship
//
//Preconditions: The input text file with the instructions needs to be present - a check is in place to determine
// if this file can be read in. This function will not be called unless the check passes. This function will also be called
// only in the case that the user opts to view how to play the game (selection 1 for user choice in main).
// 
// Postconditions: The instructions on how to play the game will display to screen - user then prompted
// if they want to play the game or if they would like to quit
void GameInstruct(ifstream& gameInstructions)
{
	//user choice to play after reading instructions
	char play_game = 'Y';
	//string line
	string line;
	//check to see if the end-of-the file has been reached
	while (!gameInstructions.eof())
	{
		//while taking in information from file
		while (getline(gameInstructions, line))
		{
			//print out the instructions line by line
			cout << line << endl;
		}
	}
	//close the instructions file
	gameInstructions.close();
	//ASK USER if they want to play the game or quit
	cout << "\nWould you like to play Battleships? Enter (Y) to return to the main menu or any other key to quit.";
	//spacing for the line
	cout << "\n\n" << endl;
	//receive input to play the game
	cin >> play_game;
	//play the game
	play_game = toupper(play_game);
	//check if user wants to play game
	if (play_game != 'Y')
	{
		//exit the game - user doesn't want to play
		exit(1);
	}
	//otherwise, the user will be returned to the menu to play the game
	return;
}

/****************************************************
Function Definition  - Initializing the Game Board
****************************************************/
//Initializes the game boards for both the player and enemy - the squares on the grid of the board are all initialized to
// spaces/blank values as they are prepared. This is before ship placement and attacks are made.
//
//Preconditions: User has to select to play the game. Additionally, the blank/default boards will initialize every time
// 
// Postconditions: The instructions on how to play the game will display to screen - user then prompted
// if they want to play the game or if they would like to quit
void initializeBoards(char attackBoard[][MAX_ROWS], char shipBoard[][MAX_ROWS], char enemyBoard[][MAX_ROWS])
{
	int i, a;
	for (i = 0; i < MAX_ROWS; i++)
	{
		for (a = 0; a < MAX_ROWS; a++)
		{
			//use tildas for water
			attackBoard[a][i] = ' ';
			shipBoard[a][i] = ' ';
			enemyBoard[a][i] = ' ';
		}
	}
	return;
}

/**********************************************************
Function Definition  - Display the Game Board for enemy
**********************************************************/
//Displays both the user's and enemy's game boards. This takes place after every move in the game.
//
//Preconditions: The game must be in play, user or enemy has made a valid move-choice/selection, and whether
// there was a hit or a miss has been updated so the game boards can be updated.
// 
// Postconditions: Displays the updated game board. 
void displayBoards(char attackBoard[][MAX_ROWS], char enemyBoard[][MAX_ROWS])
{
	//display for enemyboard
	int i, a;
	//display the board with letters at top corresponding to the column and numbers for the rows
	cout << "          Enemy Attack Board\n" << "  A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  \n";
	for (i = 0; i < MAX_ROWS; i++)
	{
		if (i + 1 != MAX_ROWS)
		{
			cout << "";
		}
		cout << i + 1;
		for (a = 0; a < MAX_ROWS; a++)
		{
			//generates brackets to separate each individual grid sqaure from the next one
			cout << "[" << attackBoard[a][i] << "]";
		}
		cout << endl;
	}
	//display the user's board using the same approach as above
	cout << "\n           Your Ship Board\n" << "  A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  \n";
	for (i = 0; i < MAX_ROWS; i++) {
		if (i + 1 != MAX_ROWS) {
			cout << "";
		}
		cout << i + 1;
		for (a = 0; a < MAX_ROWS; a++) {
			cout << "[" << enemyBoard[a][i] << "]";
		}
		cout << endl;
	}
	return;
}

/**********************************************************
Function Definition  - Display Player Boards
**********************************************************/
//Displays the player's board for where they placed ships - allows the user to confirm before play begins
//
//Preconditions: User has selected to place their ships by hand/choice (through input to console) as opposed
// to allowing the game engine itself to randomly place their ships
// 
// Postconditions: Displays the user's board for their ship placement after they have decided to place their ships. 
void displayPlayerBoard(char board[][MAX_ROWS])
{
	//integer counters 
	int i, a;
	//dispaly user's board with x and y components (column on top with letters, numbers on left side for row)
	cout << "            Your Placement Board\n" << "  A  B  C  D  E  F  G  H  I  J  K  L  M  N  O  \n";
	for (i = 0; i < MAX_ROWS; i++) {
		if (i + 1 != MAX_ROWS) {
			cout << "";
		}
		cout << i + 1;
		for (a = 0; a < MAX_ROWS; a++) {
			cout << "[" << board[a][i] << "]";
		}
		cout << endl;
	}
	return;
}

/****************************************************
Function Definitions  - Placing the Ships
****************************************************/

/***********************
Place Enemy Ships
***********************/
//Uses random functions to replicate enemy AI to place their ships on their own grid board - function calls
//another function to determine if the ships overlap or not. This function also doubles for placing 
// the user's ships if they choose to randomly place them as opposed to placing them manually. 
//
//Preconditions: The user needs to opt to play the game. Whether they choose to place their ships randomly or
// manually, the CPU needs to place the ships randomly.
// 
// Postconditions: Places ships randomly on the board adhering to conditions of the game board boundaries
// and whether or not the ships have overlap. The ships cannot have overlap in these cases. 
void placeEnemyShips(char enemyBoard[][MAX_ROWS])
{
	bool done;//used to determine when enemy ship placement has been done
	int dir; //determines the direction of the ships
	int startX; //determines starting x position selected for the ships
	int startY; //determines starting y position selected for the ships
	int shipLength[] = { 5, 4, 3, 3, 2 }; //ship lengths based on ship type
	char shipLetter[] = { 'A', 'B', 'S', 'C', 'D' }; //letters associated with each
	int ship; //used for a counter for the ship placement
	int x, y; //column and row counters
	int i; //counter used for combination of ship distance and initial position
	for (ship = 0; ship < 5; ship++) //check whether or not ship placement is done
	{
		done = false; //not done until ships placed
		while (!done) 
		{
			dir = rand() % 2; //random direction - has to be 1 or 2 (1
			startX = rand() % MAX_ROWS; //random column selected between 0 and 15 inclusive (formula is rand() % (Max + 1 - Min) + Min for inclusive)
			startY = rand() % MAX_ROWS;//random row selected betwwen 0 and 15 inclusive (formula is rand() % (Max + 1 - Min) + Min for inclusive)
			done = isShipsOverlap(enemyBoard, startX, startY, dir, shipLength[ship]); //sent to the function call overlap - returns true or false
			if (startX + shipLength[ship] >= MAX_ROWS || startY + shipLength[ship] >= MAX_ROWS) //if the ship placement is violated (out of range), tell CPU
			{
				done = false;
			}
		}
		if (dir == 0)
		{
			//check first if the ship horizontally is at the boundary
			if ((startX + shipLength[ship]) >= MAX_ROWS)
			{
				//until runs until x is less than the starting position plus the length of the ships
				for (i = startX;  i < startX + shipLength[ship]; i++)
				{
					//ship will be positioned with letters marking the ship's orientation
					enemyBoard[startX][startY] = shipLetter[ship];
					//and decrease x's value by 1 - need it to fit within the board boundaries
					startX--;
				}
			}
			//otherwise, if the head of the ship and length (tail) does not touch the eastern boundary but instead the western boundaries
			else
			{
				//until runs until x is less than the starting position plus the length of the ships
				for (i = startX; i < startX + shipLength[ship]; i++)
				{
					//ship will be positioned with letters marking the ship's orientation
					enemyBoard[startX][startY] = shipLetter[ship];
					//and increase x's value by 1 - need it to fill towards eastern most columns since the west boundary is the western most
					startX++;
				}
			}
		}
		//case where ship was selected to have a vertical orientation - ship is aligned across several rows
		else
		{
			//check first if the ship vertically is at the boundary
			if ((startY + shipLength[ship]) >= MAX_ROWS)
			{
				//until runs until x is less than the starting position plus the length of the ships
				for (i = startY; i < startY + shipLength[ship]; i++)
				{
					//ship will be positioned with letters marking the ship's orientation
					enemyBoard[startX][startY] = shipLetter[ship];
					//and decrease y's value by 1 - need it to fit within the board boundaries
					startY--;
				}
			}
			//otherwise, if the head of the ship and length (tail) does not touch the boundary
			else
			{
				//until runs until x is less than the starting position plus the length of the ships
				for (i = startY; i < startY + shipLength[ship]; i++)
				{
					//ship will be positioned with letters marking the ship's orientation
					enemyBoard[startX][startY] = shipLetter[ship];
					//and increase x's value by 1 - need it to fill towards eastern most columns since the west boundary is the western most
					startY++;
				}
			}
		}
	}
	return;
}

/*******************
Place Player Ships
*******************/
//Places the ships for the user's board - allows the user to confirm before play begins
//
//Preconditions: User has selected to place their ships by hand/choice (through input to console) as opposed
// to allowing the game engine itself to randomly place their ships; ships placement must be valid as well
// 
// Postconditions: Displays the user's board for their ship placement after they have decided to place their ships. 
void placePlayerShips(char shipBoard[][MAX_ROWS])
{
	//variables for board
	//for the character corresponding to column
	char xChar;
	//x and y coordinates for gameplay
	int x;
	int y;
	//direction for vertical or horizontal placement
	int dir;
	//ship number for the loop
	int shipNumber = 0;
	//check if user wants to enter their ship placement manually or randomly
	int manRand = 0;
	//names of ships
	string names[] = { "Aircraft Carrier", "Battleship", "Submarine", "Cruiser", "Destroyer" };
	//representation of thoe ships by letter
	char shipLetter[] = { 'A', 'B', 'S', 'C', 'D' };
	//ships lengths
	int lengths[] = { 5, 4, 3, 3, 2 };
	//booleans to determine if user placement is done and whether or not ships overlap
	bool done = false;
	bool isOverlap = true;
	//counter - check if ship placement is valid
	int i;
	//ask user if they want to place ships manually or randomized by CPU
	cout << "Would you like to place your ships manually, or at random?\n";
	cout << "1.) Manual\n";
	cout << "2.) Random\n";
	cout << "Enter choice (1/2): ";
	//input for manual implementation - user needs to select choice 1 to place, otherwise, choice 2 will place their ships
	cin >> manRand;
	if (manRand == 2) {
		done = true;
		placeEnemyShips(shipBoard); //function call also used to place user ships
	}
	//while user placement of ships are not done
	while (!done)
	{
		//user defined clear function - helpful with clearing board and displaying new board as ships are set
		clear();
		displayPlayerBoard(shipBoard);
		//tell user what ships they are placing
		cout << "\nYou are placing the " << names[shipNumber] << ".\n";
		cout << "Its length is " << lengths[shipNumber] << ".\n\n";
		//where should the ship be placed by letters
		cout << "Where should the front of the ship be? (A-O): ";
		cin >> xChar;
		//do double duty here and inspect if the user's ship placement with a function meets the requirements
		//check if user has not entered a valid character placement for the gameboard
		x = charToNum(xChar);
		while (x < 0 || x> 14)
		{
			//messages if user did not enter the proper board placement
			cout << "Please enter a valid starting column position.\n";
			cout << "You are placing the " << names[shipNumber] << ".\n";
			cout << "Its length is " << lengths[shipNumber] << ".\n";
			cout << "Where should the front of the ship be? (A-O): ";
			//prompt user to enter column character again
			cin >> xChar;
			x = charToNum(xChar);
		}
		//clear to make board easier to see
		clear();
		displayPlayerBoard(shipBoard);
		//ask user to enter starting row (1-15)
		cout << "\n\nPlease enter the other starting position. (1-15): ";
		cin >> y;
		//check if the value of y is valid
		while (y < 1 || y > 15)
		{
			//messages if user did not enter the proper board placement
			cout << "Please enter a valid starting row position.\n";
			cout << "You are placing the " << names[shipNumber] << ".\n";
			cout << "Its length is " << lengths[shipNumber] << ".\n";
			cout << "Please enter the other starting position. (1-15): ";
			cin >> y;
		}
		//decrement y by one
		y--;
		int startX = x; //the ship's placement starts at the column specified for the head
		int startY = y; //the ship's placement starts at the row specified for the head
		clear();
		displayPlayerBoard(shipBoard);
		//choose ships direction - 1 for vertical, 2 if the ship is to lie horizontal
		cout << "What direction would you like the ship to face?\n";
		cout << "1. Vertical\n";
		cout << "2. Horizontal\n";
		//user input for ship direction
		cin >> dir;
		//check if user input a valid direction
		while (dir != 1 && dir != 2)
		{
			clear();
			displayPlayerBoard(shipBoard);
			//tell user selected direction was not valid
			cout << "Please enter a valid direction:\n\n";
			cout << "What direction would you like the ship to face?\n";
			cout << "1.) Vertical\n";
			cout << "2.) Horizontal\n";
			cin >> dir;
		}
		//if ship orientation is selected to be horizontal
		if (dir == 2)
		{
			//then the ship shouldn't have vertical orientation - in the original battleship there wasn't placement for diagonals
			dir -= 2;
		}
		//check to see if there is anyoverlap with the ships-function call isShipsOverlap
		isOverlap = isShipsOverlap(shipBoard, startX, startY, dir, lengths[shipNumber]);
		//if there isn't overlap - clear was used to return for isOverlap whether the user was clear from any kind of overlap
		if (isOverlap==true)
		{
//for the horizontal orientation where ship spans the columns
			if (dir == 0)
			{
				//check first if the ship horizontally is at the boundary
				if ((startX + lengths[shipNumber]) >= MAX_ROWS)
				{
					//until runs until x is less than the starting position plus the length of the ships
					for (i = startX; i < startX + lengths[shipNumber]; i++)
					{
						//ship will be positioned with letters marking the ship's orientation
						shipBoard[x][y] = shipLetter[shipNumber];
						//and decrease x's value by 1 - need it to fit within the board boundaries
						x--;
					}
				}
				//otherwise, if the head of the ship and length (tail) does not touch the eastern boundary but instead the western boundaries
				else
				{
					//until runs until x is less than the starting position plus the length of the ships
					for (i = startX; i < startX + lengths[shipNumber]; i++)
					{
						//ship will be positioned with letters marking the ship's orientation
						shipBoard[x][y] = shipLetter[shipNumber];
						//and increase x's value by 1 - need it to fill towards eastern most columns since the west boundary is the western most
						x++;
					}
				}
			}
			//case where ship was selected to have a vertical orientation - ship is aligned across several rows
			else
			{
				//check first if the ship vertically is at the boundary
					if ((startY + lengths[shipNumber]) >= MAX_ROWS)
					{
						//until runs until x is less than the starting position plus the length of the ships
						for (i = startY; i < startY + lengths[shipNumber]; i++)
						{
							//ship will be positioned with letters marking the ship's orientation
							shipBoard[x][y] = shipLetter[shipNumber];
							//and decrease y's value by 1 - need it to fit within the board boundaries
							y--;
						}
					}
				//otherwise, if the head of the ship and length (tail) does not touch the boundary
					else
					{
						//until runs until x is less than the starting position plus the length of the ships
						for (i = startY; i < startY + lengths[shipNumber]; i++)
						{
							//ship will be positioned with letters marking the ship's orientation
							shipBoard[x][y] = shipLetter[shipNumber];
							//and increase x's value by 1 - need it to fill towards eastern most columns since the west boundary is the western most
							y++;
						}
					}
			}
			//ships will be placed as long as the user hasn't placed the smallest ship yet (ships placed in order from 5 to 1 (4-0 in this case for the indices
			//representing the ship array).
			if (shipNumber < 4)
			{
				//increment ship number to next ship to be placed
				shipNumber++;
			}
			else 
			{
				//now the user is done with ship placement
				done = true;
			}
		}
		//if there was overlap
		else 
		{
			//user has not entered valid coordinates for the orientation of the ship based on horizontal/vertical alignment or coordinates, or ship overlap
			cout << "Your ship has not been placed either because your ship's length was outside the board"
				   << " based on placement, overlapped with another ship, or"
				<< " you made an inaccurate assignment of the front of the ship."
				 << "\nPlease enter valid coordinates for the ship...\n";
			pause();
			cin.get();
		}
	}
	return;
}

/****************************************************
Function Definitions  - Hit Random
****************************************************/
//Uses random functions to replicate enemy AI to launch an attack against the user. Uses a stack to essentially pop a random assortment of coordinates (letter/number for column and row respectively)
//to launch attacks. For directions to dictate to the AI how to shoot, 'U' is used for up,'L' for left, 'R' for right, and 'D' for down.
//
//Preconditions: The CPU needs to have a stack initialized to make moves - the stack updates during the course of the game and tries to do so seamlessly to limit any latency
// 
// Postconditions: An attack is launched on the user - user is told where the attack occurs and whether or not a ship was hit.
char hitRandom(char shipBoard[][MAX_ROWS], char attackBoard[][MAX_ROWS], bool& shouldUseLogic, bool& isMultipleShips, bool& AIPrevHit, int& numOfShips, int& shipsLeft, int& AIEnds, stack <int>& xStack, stack <int>& yStack, stack <char>& dirStack)
{
	//generates a random hit for the CPU to initiate against the player 
	//integer x and y corresponding to a random coordinate
	int x;
	int y;
	//set to false until the CPU is done
	bool done = false;
	//determines if all stack operations are good to use for the program
	bool stackGood = false;
	//justMiss - did the CPU miss (set to false until CPU's turn)
	bool justMiss = false;
	//Did the CPU hit the player's ship?
	char didHitChar;
	//letters corresponding to column name
	string letters = "ABCDEFGHIJKLMNO";
	//x and y are geenrated as random integers
	x = rand() % MAX_ROWS;
	y = rand() % MAX_ROWS;
	//if the CPU has already hit a ship in a spot or has already missed a shot in a spot, rather than repeating that choice, the function is called recursively
	if (shipBoard[x][y] == '#' || shipBoard[x][y] == '@')
	{
		//stop this current choice, and now call the function recursively 
		done = true;
		//call function recursively 
		hitRandom(shipBoard, attackBoard, shouldUseLogic, isMultipleShips, AIPrevHit, numOfShips, shipsLeft, AIEnds, xStack, yStack, dirStack);
	}
	//if the stack for the column orders are currently empty
	if (!xStack.empty())
	{
		while (!stackGood) //while there are still instructions that the CPU needs for the stack for the horizontal columns
		{
			//check if the top of stack includes any values less than 0 (prohibited in the program since we use the ASCII decimals associated with
			//letters for columns and numbers greater than or equal to zero for the indices of rows)
			if (xStack.top() < 0 || yStack.top() < 0 || shipBoard[xStack.top()][yStack.top()] == '@' || shipBoard[xStack.top()][yStack.top()] == '#')
			//check also if the stack has any values which correspond to a hit or miss that the AI recorded at the top
			{
				//if the top of the stack has any values less than 0 or greater than 0 while the stack is not good
				if (xStack.top() < 0 || yStack.top() < 0 || xStack.top() > 0 || yStack.top() > 0)
				{
					//increments AI ends by one - 2 is the condition for the CPU's process of 
					//[generate moves -> launch moves -> analyze prior moves - rinse, wash, and repeat] to end
					AIEnds++;
				}
				//pop from the stack the last items that were pushed into it for the vertical and horizontal coordinates along with the direction (up, down, left, right)
				xStack.pop();
				yStack.pop();
				dirStack.pop();
			}
			//otherwise, the stacks have been operated on, initializations are good, and the CPU is ready for action
			else
			{
				stackGood = true;
			}
		}
	}
/****************************************************
CPU/AI Is Thinking of Next Move For Upcoming Turn (Hit Successfully)
****************************************************/
	//if the CPU is done (always the case when they end their turn)
	if (!done)
	{
		//CPU will generate logic to use for its next attack
		if (!shouldUseLogic)
		{
			//the CPU has hit the player-need to update the player's board to reflect that and to let the CPU also know that
			didHitChar = didHit(shipBoard, x, y);
			//if the CPU has not been recorded as hitting the user yet
			if (didHit(shipBoard, x, y) != '#')
			{
				//record the CPU as hitting the player
				shipBoard[x][y] = '#';
				//display the updated boards
				displayBoards(attackBoard, shipBoard);
				//print to screen where they attacked the player 
				cout << "\nEnemy attacked at " << letters.at(x) << " " << y + 1 << endl;
				//tell user they hit their ship
				cout << "They hit your ship!\n";
				//here, the CPU should now reset its logic and behavior after it made a successful attack - the CPU should use logic as it determines
				//in a challenging enough but not alienating way to determine how to hit the next ship or another ship (i.e., should it decide to implement
				// moves to aim down of its original shot, left, right, etc.?). 
				shouldUseLogic = true;
				//now the AI knows that it should also be targeting another portion of ship on its next turn
				numOfShips++;
				//to do so, it will need to first "push" into its instruction stack a list of instructions where it will guess which spot adjacent to
				//its successful shot to target next

				//for right, the CPU needs to push in a value to the right of the current column, a value that is the same as row - represents right and
				//now the direction stack has R in its contents
				xStack.push(x + 1);
				yStack.push(y);
				dirStack.push('R');

				//for left, the CPU needs to push in a value to the left of the current column, a value that is the same as row - represents right and
				//now the direction stack has L for left in its contents
				xStack.push(x - 1);
				yStack.push(y);
				dirStack.push('L');

				//for down, the CPU needs to push in a value that is the same as the current column, a value that is one more than the row - 
				// (the rows go downward with 1 at the top and 15 at the bottom) now these instructions represent down and
				//now the direction stack has D in its contents
				xStack.push(x);
				yStack.push(y + 1);
				dirStack.push('D');

				//for down, the CPU needs to push in a value that is the same as the current column, a value that is one more than the row - 
				// (the rows go downward with 1 at the top and 15 at the bottom) now these instructions represent down and
				//now the direction stack has D in its contents
				xStack.push(x);
				yStack.push(y - 1);
				dirStack.push('U');

			}
			//the CPU has already tried for an attack and has missed! since they missed, the AI doesn't need to have a set of instructions
			//"pushed" into the stacks - this would be a rather expensive decision computationally and it was much easier to simply
			//consider cases of a successful hit
/***********************************************************
CPU/AI Missed Here - Will Not Create Routes for Next Attack
************************************************************/
			else
			{
				//mark this spot as a miss by the enemy
				shipBoard[x][y] = '@';
				//display the updated boards
				displayBoards(attackBoard, shipBoard);
				//tell the user the enemy attacked them at coordinates but missed
				cout << "\nEnemy attacked at " << letters.at(x) << " " << y + 1 << endl;
				cout << "They missed!\n";
			}
		}
/***********************************************************
CPU/AI is Attacking (and was Successful)
************************************************************/
		//if set logic has defaulted back to false then the CPU is currently in the process of executing a move (thoughts in -> actions out)
		else
		{
			//first, CPU targets on the player's ship a coordinate character-number combination
			didHitChar = didHit(shipBoard, xStack.top(), yStack.top());
			//if the CPU hit the player's ship but that has not been noted and placed into the stack
			if (didHit(shipBoard, xStack.top(), yStack.top()) != '#') 
			{
				//now the x,y coordinates in terms of the respective stacks have that mark for hitting the player's ship - stored to make sure
				//the AI doesn't target the same spot again
				shipBoard[xStack.top()][yStack.top()] = '#';
				//display the updated user boards
				displayBoards(attackBoard, shipBoard);
				//tell the user that their ship was struck
				cout << "\nEnemy attacked at " << letters.at(xStack.top()) << " " << yStack.top() + 1 << endl;
				cout << "They hit your ship!\n";
				//if there are still ships in play, the CPU needs to know that it will need to prepare the AI for next round
				if (!isMultipleShips)
				{
					//increment by 1
					numOfShips++;
				}
				AIPrevHit = true; //AI has also targeted and hit a ship previously - kicks off the chain of the AI from that hit selecting the best moves
				//to target the rest of the player's ship in their fleet
				x = xStack.top(); //x is now initialized for the next turn as the coordinate at the top of the stack 
				y = yStack.top(); //y is now initialized for the next turn as the coordinate at the top of the stack
				//since x and y have been initialized, pop off these values-no longer needed
				xStack.pop();
				yStack.pop();
				//switch case statement for direction for revPush - need to keep the stream of moves coming from the AI
				switch (dirStack.top())
				{
					//for up
				case 'U':   
					dirStack.pop();
					revPush(x - 1, y, 'L');
					revPush(x + 1, y, 'R');

					xStack.push(x);
					yStack.push(y - 1);
					dirStack.push('U');
					break;

					//for down
				case 'D':   
					dirStack.pop();
					revPush(x - 1, y, 'L');
					revPush(x + 1, y, 'R');

					xStack.push(x);
					yStack.push(y + 1);
					dirStack.push('D');
					break;

					//for left
				case 'L':   
					dirStack.pop();
					revPush(x, y - 1, 'U');
					revPush(x, y + 1, 'D');

					xStack.push(x - 1);
					yStack.push(y);
					dirStack.push('L');
					break;

					//for right
				case 'R':   
					dirStack.pop();
					revPush(x, y - 1, 'U');
					revPush(x, y + 1, 'D');

					xStack.push(x + 1);
					yStack.push(y);
					dirStack.push('R');
					break;
				}
			}
			else
			{
				shipBoard[xStack.top()][yStack.top()] = '@';
				displayBoards(attackBoard, shipBoard);
				cout << "\nEnemy attacked at " << letters.at(xStack.top()) << " " << yStack.top() + 1 << endl;
				cout << "They missed!\n";
				xStack.pop();
				yStack.pop();
				dirStack.pop();
				if (AIPrevHit)
				{
					AIEnds++;
				}
			}
			if (AIEnds == 2 && !isMultipleShips)
			{
				isMultipleShips = true; //tells the AI there are multiple ships still in play
				shipsLeft = numOfShips; //tells the AI it has numOfShips more portions to target
			}
		}
	}
	//for randomHit, return either '#' or '@' for a successful hit or miss respectively
	return didHitChar;
}

/****************************************************
Function Definitions  - Attack!
****************************************************/
void attack(char shipBoard[][MAX_ROWS], char attackBoard[][MAX_ROWS], char enemyBoard[][MAX_ROWS], int enemyHealth[])
//Allows user to launch an attack against the computer and displays through messages whether the player hit or missed the enemy
//
//Preconditions: It needs to be the player's turn to formulate their attack. Their selected coordinates for attacking must be valid.
// 
// Postconditions: An attack is launched on the CPU - user is told where the attack occurs and whether or not they hit the enemy's ship.
{
	//integers for x and y coord. for attack
	int x;
	int y;
	//chaarcter for column
	char charX;
	//clear board to make dsplay neat and display updated board
	clear();
	//display the updated user and enemy boards
	displayBoards(attackBoard, shipBoard);
	//have user enter COLUMN of attack
	cout << "\n\n\nPlease enter the column of the attack (A-O) or enter 'Q' to quit: ";
	cin >> charX;
	//convert character entered to uppercase
	charX = toupper(charX);
	//quit
	if (charX == 'Q')
	{
		cout << "Quitting the game.\n" << endl;
		//quit the whole program if Q was entered - don't try to do a calculation  to determine
		exit(1);
	}
	//x coordinate is claculated by converting xChar to a number
	x = charToNum(charX);
	//check if the user has not entered a correct letter value
	while (x < 0 || x > 14) //values need to be between 0 and 14 - from chartoNum 65 is subtracted from the letter and the resultant decimal ASCII value is used
	{
		//messages if user did not enter the proper board placement
		cout << "\nPlease enter a valid column position: ";
		cin >> charX;
		x = charToNum(charX);
	}
	clear();
	//display updated board
	displayBoards(attackBoard, shipBoard);
	//user enters the ROW of the attack specified by y
	cout << "\n\n\nPlease enter the row of the attack (1-15): ";
	cin >> y;
	//check if y is less than 1 or exceeds 15 (row indices go from 0 to 14)
	while (y < 1 || y > 15)
	{
		//prompt user to enter a valid row coordintae
		cout << "\nPlease enter a valid row position: ";
		cin >> y;
	}
	//decrement y by one since our row coordinates technically start at 0
	y -= 1;
	//check if user hasn't entered a position they already targeted
	if (enemyBoard[x][y] == '#' || enemyBoard[x][y] == '@')
	{
		//clear the board
		clear();
		//tell user of error
		cout << "Please enter a coordinate that has not already been entered...\n";
		//pause to allow for time to display recurisve call to attack again
		pause();
		//CALL THIS FUNCTION recursively to enter coordinates again
		attack(shipBoard, attackBoard, enemyBoard, enemyHealth);
	}
	//case where the user has hit one of their ships
	else if (enemyBoard[x][y] != ' ')
	{
		//convert the ship at the location to a number to assess hitpoints
		int shipType = shipToNum(enemyBoard[x][y]);
		//decremenet enemy ship's health by one
		enemyHealth[shipType]--;
		//clear board
		clear();
		//mark the enemy and enemy attack boards as attacked
		enemyBoard[x][y] = '#';
		attackBoard[x][y] = '#';
		//display new boards
		displayBoards(attackBoard, shipBoard);
		//enemy ship has been hit - notify the user
		cout << "\n\nYou hit one of their ships!\n";
		cout << "Press enter to continue...";
		cin.get();
		cin.get();
	}
	//user missed
	else
	{
		clear();
		//mark enemy's boards where the miss occurred
		enemyBoard[x][y] = '@';
		attackBoard[x][y] = '@';
		displayBoards(attackBoard, shipBoard);
		//display message of miss
		cout << "\n\nMissed!\n";
		//press enter to continue
		cout << "Press enter to continue...";
		cin.get();
		cin.get();
	}
	return;
}

/****************************************************
Function Definitions  - RevPush
****************************************************/
void revPush(int x, int y, char dir)
//Initializes temporary stacks based on the stacks for vertical position, horizontal position, and the character associated with direction
//in order for to push x,y, and dir values into their respective stacks - essentially generating a continuous stream
//of random moves that the enemy AI can utilize as it tries to target the player's fleet. 
//
//Preconditions: It needs to be the player's turn to formulate their attack. Their selected coordinates for attacking must be valid.
// 
// Postconditions: An attack is launched on the CPU - user is told where the attack occurs and whether or not they hit the enemy's ship.
{
	//stacks xStack, yStack, and dirStack
	stack <int> xStack;
	stack <int> yStack;
	stack <char> dirStack;

	//initialized temporary stacks based on x, y, and direction
	stack <int> tempX;
	stack <int> tempY;
	stack <char> tempDir;

	//while the stack for x is not empty
	while (!xStack.empty())
	{
		//push into the temporary stacks what was at the top of the original stacks
		tempX.push(xStack.top());
		tempY.push(yStack.top());
		tempDir.push(dirStack.top());

		//pop off of those stacks the top values since we no longer need them
		xStack.pop();
		yStack.pop();
		dirStack.pop();
	}
	//initialize these stacks to empty first - then push in the values for x,y, and direction
	xStack = stack<int>();
	yStack = stack<int>();
	dirStack = stack<char>();

	//push x, y, and dir into the corresponding stacks
	xStack.push(x);
	yStack.push(y);
	dirStack.push(dir);

	while (!tempX.empty())
	{
		//push into x,y, and dir stacks what were at the tops of the temp stacks
		xStack.push(tempX.top());
		yStack.push(tempY.top());
		dirStack.push(tempDir.top());

		//pop - no longer need what is at the top
		tempX.pop();
		tempY.pop();
		tempDir.pop();
	}
	return;
}

/****************************************************
Function Definitions  - Clear and Pause
****************************************************/

/**************
Clear
***************/
void clear()
{
	//'Clears' the player screen - simulates this process by just placing enough newline statements between the
	// previous graphical representations of the player/enemy game boards and the updated visual representations
	//
	//Preconditions: User is still playing the game, and after a player/enemy move the clear function will provide enough spacing to display the new board.
	// 
	// Postconditions: "Clears" the board - enough spacing is provided to look at the updated board. This usually happens so quickly (but not seamlessly) that it
	//almost represents an active visual update

	//counter integer
	int i;
	//prints 10 endline statemnts for spacing
	for (i = 0; i < 10; i++)
	{
		cout << endl;
	}
	//return statement
	return;
}

/**************
Pause
***************/
void pause()
{
	//'Pauses' the screen to allow the user to view the current gameboard consisting of their own board and the enemy's board(s). 
	// 
	//Preconditions: User is still playing the game, and after a player/enemy move the pause function will prompt the user to press enter to continue as they look
	//at the screen.
	//
	// Postconditions: Game is paused until the user presses enter to either move on to make their moves or to wait for the enemy to initiate their moves.
	cout << "Press enter to continue....";
	cin.get();
	clear();
	return;
}

/****************************************************
Function Definitions  - Do the Ships Overlap?
****************************************************/
bool isShipsOverlap(char board[][MAX_ROWS], int x, int y, int dir, int shipLength)
//Determines if the user or enemy's placement of the ships in their fleet have any overlap or go off the boundaries
//of the board. Overlap in battleships will not be allowed (obviously).
//
//Preconditions: User (if they choose not to use random placement) and enemy must select ship placement
// using accurate coordinates. 
// 
// Postconditions: Boolean function will determine if the placement was inaccurate - if it was, for example, then the 
//function prevents the score from clearing and instead in main the user will need to enter their coordinates
//for ship placement again
{
	//check first if the placement of the user's ships are clear. set to true initially but becomes false
	//if the user tries to overlap two ships
	bool clear = true;
	//x value is used for column
	int startX = x;
	//y value is used for row
	int startY = y;
	//counter for the integer
	int i;
	//if the selected direction for the ship has been decided
	if (dir == 0)
	{
		//use for loop to determine if the ship will not overlap or go off board boundaries
		//for (i = 0; i < startX + shipLength; i++)
		for (i = startX; i < (startX + shipLength); i++)
		{
			if (board[x][y] != ' ')
			{
				//if it does, then set clear to false and return to main
				clear = false;
			}
		}
	}
	//else, check if the y components (rows) have any overlap
	else
	{
		//use for loop to determine if the ship will not overlap or go off boundaries of the rows
		//for (i=0; i < startY + shipLength; i++)
		for (i = startY; i < (startY + shipLength); i++)
		{
			if (board[x][y] != ' ')
			{
				//return false return to main
				clear = false;
			}
		}
	}
	//otherwise clear is still true- no ship overlap
	return clear;
}

/****************************************************
Function Definitions  - Did It Hit?
****************************************************/
char didHit(char board[][MAX_ROWS], int x, int y)
{
	//Determines if the user or the enemy made a successful attack
	//on one of the ships that were part of the fleet.
	//
	//Preconditions: User or enemy must successfully complete the initialization of an attack -
	//if an error message or a check determines that the entry was invalid, the attack will not be successful
	// 
	// Postconditions: Determines based on the move made if a target grid contained a portion of a ship - replaces
	// that portion with the corresponding characters representing the attack
		//character to represent ship type
	char shipType;
	//if the board is not empty at that point but a secure shot was not landed, then it remains the same symbol
	if (board[x][y] != ' ')
	{
		shipType = board[x][y];
	}
	//if you/opponent hit a ship, replace that
	//position on the grid/board with '#' for a hit
	else
	{
		shipType = '#';
	}
	return shipType;
}

/****************************************************
Function Definitions  - Characters to Numbers
****************************************************/
int charToNum(char letter)
{
	//Converts the user choice for letter (column) into the equivalent
	// number for the sake of the program's internal calculations
	//
	//Preconditions: User has to input a correct letter choice -otherwise
	// if-else statements and conditions along with other implemented
	// methods to catch mistakes will not allow an invalid character to be input
	// 
	// Postconditions: Converts the letter to a number by subtracting 65 from it -
	//this is based on the ASCII representation with 'A' being 65 for example
	int char_to_value = letter - 65;
	//return the value which must be 0 to 14 (inclusive).
	return char_to_value;
}

/****************************************************
Function Definitions  - Ship into Numbers
****************************************************/
int shipToNum(char letter)
{
	//Receives from the program the letters representing
	//each of the different types of ships
	//
	//Preconditions: Only letters A, B, S, C, and D will be accepted
	//for the corresponding ship types - anything else will default
	// 
	// Postconditions: Converts that letter to a number
	int num = 0;
	switch (letter)
	{
		//for aircraft carrier
	case 'A':
	{
		num = 0;
		break;
	}
	//for battleship carrier
	case 'B':
	{
		num = 1;
		break;
	}
	//for submarine
	case 'S':
	{
		num = 2;
		break;
	}
	//for cruiser
	case 'C':
	{
		num = 3;
		break;
	}
	//for destroyer
	case 'D':
	{
		num = 4;
		break;
	}
	//return the number for converting the specified ship letters
	//based on the ships to numbers
	return num;
	}
}

