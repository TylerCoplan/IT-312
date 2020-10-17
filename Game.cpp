/* Tyler Coplan
 * IT-312-J1768
 * September 30, 2020
 * Final Project: Farkle
 *
 * The game class is responsible for handling the major functionality of the game.
 * The game class has a turn object, a vector of player objects, and keeps track of 
 * the number of dice in play and whose turn it is.  The class provides the functioning
 * gameloop which calls functions to handle the logic in the game such as dice rolling
 * and player decisions.
 */

#include "Game.h"

using namespace std;

// Define constructor
Game::Game()
{
	m_numOfDice = 6;
	m_playerTurn = 0;
}

// Define Destructor
Game::~Game() 
{
}

// The primary game loop. Calls functions to play the game
void Game::PlayFarkle()
{
	// Game intro
	cout << "*************FARKLE***************" << endl;
	ReadRules();
	GetPlayers();

	// Display first players turn
	cout << "It is " << m_playerList.at(m_playerTurn).GetName() << "'s turn." << endl;

	while (m_playerList.at(m_playerTurn).GetPlayerScore() < 10000)
	{
		RollDice();
		
		// Evaluate and handle user decisions for all scoring scenarios
		EvaluateRollSets();
		EvaluateRollFives();
		EvaluateRollOnes();

		// Calls function if player farkled
		if (m_turn.GetIsFarkle())
		{
			PlayerFarkled();
		}
		// Continues play if the player kept all scoring dice
		else if (m_numOfDice == 0)
		{
			cout << "Congratulations! All dice have scored.  You must roll again now." << endl;
			m_numOfDice = 6;
			PlayerRollAgain();
		}
		// Calls function to handle player decision to keep score or roll again
		else
		{
			KeepOrRoll();
		}
	}

	// Winners screen
	short max = m_playerList.at(0).GetPlayerScore();
	int winnersIndex = 0;
	for (short i = 0; i < m_playerList.size(); i++)
	{
		if (m_playerList.at(i).GetPlayerScore() > max)
		{
			max = m_playerList.at(i).GetPlayerScore();
			winnersIndex = i;
		}
	}

	cout << "Congratulations " << m_playerList.at(winnersIndex).GetName() 
		 << "! You won the game!" << endl;
}

// This function asks the users if they would like to read the rules and displays them if user answers yes
void Game::ReadRules()
{
	string input = "";

	// Prompt user for input / get input / validate input
	cout << "Would you like to read the rules (Y/N)? " << endl;
	cin >> input;
	InputHandler::VerifyYN(input);

	if (input == "Y" || input == "y")
	{
		// Creates file stream object to read rules
		ifstream file("FarkleRules.txt");

		// Outputs .txt file line by line until reaching end of file
		while (getline(file, input))
		{
			cout << input << endl;
		}
	}

	// Print new line and clear cin buffer
	cout << endl;
	cin.ignore();
	cin.clear();
}

// Function to get players.  Will record at least one player. Creates player objects
// and adds them to the vector of players part of a member of this class.
void Game::GetPlayers()
{
	string name = "";
	short i = 2;

	cout << "Enter Player 1's name: " << endl;
	getline(cin, name);

	// Do while loop will ensure at least one player is added before "start" is entered (could even name player "start")
	do
	{
		Player player(name);
		m_playerList.push_back(player);

		cout << "Enter Player " << i << "'s name, or enter \"start\" to play:" << endl;
		getline(cin, name);
		i++;
		
	} while (name != "start");
}

// Creates a die object, rolls the die, outputs the value to the screen, repeats for numOfDice
void Game::RollDice()
{
	Die die;
	short i = 1;
	string input = "";

	// Used to pause program and allow player to enter a key to roll, input is meaningless
	cout << m_playerList.at(m_playerTurn).GetName() << " press \"enter\" to roll: " << endl;
	getline(cin, input);

	// rolls a die and outputs value for each die available to be rolled
	while (i <= m_numOfDice)
	{
		die.Roll();
		cout << "Die " << i << ": " << die.GetValue() << endl;
		m_turn.AddRollToValueCount(die.GetValue());
		i++;
	}
}

// This function evaluates rolls for sets of 3.  Updates turn data with the appropriate information.
// This is my least liked function in my project.
// It has a up to 4 nested logic branches in a for loop to evaluate each value and handle
// special cases and exceptions.  I am not sure if this is common to have so many nested branches.
// Everything works as planned, although I probably should have used more functions to handle this logic.
void Game::EvaluateRollSets()
{
	string input = "";
	const short SET_MULTIPLIER = 100;

	// The value of i represents the die value being analyzed / checks values 1-6
	for (short i = 1; i <= 6; i++)
	{
		// decision branch if the roll produced a set of the current iteration value
		if (m_turn.GetValueCount(i) >= 3)
		{
			// Handles special case for evaluating sets of 1's
			if (i == 1)
			{
				cout << "Awesome! You rolled three 1's. That is worth 1000 points. " 
					 << "Would you like to keep them (Y/N)? " << endl;
				getline(cin, input);
				InputHandler::VerifyYN(input);

				// Branch makes sure that if these are the only points, the user keeps them
				if (input == "n" || input == "N")
				{
					if (m_turn.GetValueCount(1) == 0 &&
						m_turn.GetValueCount(5) == 0 &&
						m_turn.GetIsFarkle())
					{ 
						cout << "These are your only points, you must keep them to avoid a farkle." << endl;
						input = "y";
					}
					else
					{
						cout << "You chose not to keep the points." << endl;
					}
				}

				// Must remain an if statement instead of if else - input could change in previous if statement
				if (input == "y" || input == "Y")
				{
					cout << "1000 points added to turn score" << endl;
					m_turn.SubtractValueFromValueCount(i, 3);          // sets the 3 dice aside
					m_turn.AddToTurnScore(1000);                       // adds score to turn object
					m_turn.SetIsFarkle(false);                         // sets farkle boolean to false
					m_numOfDice -= 3;                                  // removes 3 dice from next roll
				}
			}

			// Evaluates all sets for 2-6
			else
			{
				// Print message to user / ask for player decision / validate input
				cout << "Nice! You rolled three " << i << "'s. That is worth "
					 << i * SET_MULTIPLIER << " points. Would you like to keep them (Y/N)? " << endl;
				getline(cin, input);
				InputHandler::VerifyYN(input);

				if (input == "n" || input == "N")

					// This branch makes sure user keeps the points if no others are available
					if (m_turn.GetValueCount(1) == 0 &&
						m_turn.GetValueCount(5) == 0 &&
						m_turn.GetIsFarkle())
					{
						cout << "These are your only points, you must keep them to avoid a farkle." << endl;
						input = "y";
					}
					else
					{
						cout << "You chose not to keep the points." << endl;
					}
				
				// Must be an if branch, not if else because input can change in previous branch
				if (input == "y" || input == "Y")
				{
					cout << i * SET_MULTIPLIER << " points added to turn score." << endl;
					m_turn.SubtractValueFromValueCount(i, 3);
					m_turn.AddToTurnScore(i * SET_MULTIPLIER);
					m_turn.SetIsFarkle(false);
					m_numOfDice -= 3;
				}
			}
		}

		// This branch gets called if current iteration is not a set.
		else
		{
			continue;
		}
	}
}

// Evaluates points for individual fives. Ensures user keeps the points if none other
// available.  Updates turn data with score, farkle, value counts.
void Game::EvaluateRollFives()
{
	string input;
	int numToKeep = -1;  

	// If there are any 5's rolled that were not kept as part of a set
	if (m_turn.GetValueCount(5) > 0)
	{
		// Display message / prompt for input
		cout << "You have " << m_turn.GetValueCount(5) << " five(s) worth 50 points each. "
			<< "How many of them would you like to keep?" << endl;
		
		// Loop will continue to run until user gives valid input
		while (numToKeep == -1)
		{
			getline(cin, input);
			try
			{
				// Attempts to converts string to int, throws errors if out of range or not a number
				numToKeep = stoi(input);
				
				// If user keeps points
				if (numToKeep > 0 && numToKeep <= m_turn.GetValueCount(5))
				{
					m_turn.AddToTurnScore(50 * numToKeep);                   // updates turn score
					m_numOfDice -= numToKeep;                                // sets dice aside
					m_turn.SubtractValueFromValueCount(5, (short)numToKeep); // adjusts turn value count
					m_turn.SetIsFarkle(false);                               // sets farkle boolean to false
					cout << "You have kept " << numToKeep << " fives worth "
						<< numToKeep * 50 << " points!" << endl;
				}
				// Branch if user tries to not keep any points
				else if (numToKeep == 0)
				{
					// Validates that user declining will not result in farkle.
					if (m_turn.GetValueCount(1) == 0 && m_turn.GetIsFarkle())
					{
						cout << "You must keep at least one 5 to avoid a farkle. "
							 << "How many would you like to keep?" << endl;
						numToKeep = -1;  // keeps loop running
					}
					else
					{
						cout << "You have chosen not to keep any fives." << endl;
					}
				}
				else
				{
					numToKeep = -1; // keeps loop running
					cout << "Please enter 0 through " << m_turn.GetValueCount(5) << ": " << endl;
				}
			}
			// catches errors for input not a number
			catch (invalid_argument& err1)
			{
				cout << err1.what() << "Please enter 0 through " 
					 << m_turn.GetValueCount(5) << ": " << endl;
			}
			catch (out_of_range& err2)
			{
				cout << err2.what() << "Please enter 0 through " 
					 << m_turn.GetValueCount(5) << ": " << endl;
			}
		}
	}
}

// Evaluates points for individual ones. Ensures user keeps the points if none other
// available.  Updates turn data with score, farkle, value counts.
void Game::EvaluateRollOnes()
{
	string input;
	int numToKeep = -1;
	if (m_turn.GetValueCount(1) > 0)
	{
		// Display message to user / prompt for input
		cout << "You have " << m_turn.GetValueCount(1) << " one(s) worth 100 points each. "
			<< "How many of them would you like to keep?" << endl;

		// Loop will continue to run until user enters valid input
		while (numToKeep == -1)
		{
			getline(cin, input);

			try
			{
				// Attempts to convert input string to integer - throws errors for invalid input
				numToKeep = stoi(input);

				// If user keeps points
				if (numToKeep > 0 && numToKeep <= m_turn.GetValueCount(1))
				{
					m_turn.AddToTurnScore(100 * numToKeep);                    // updates turn score
					m_numOfDice -= numToKeep;                                  // sets kept dice aside
					m_turn.SubtractValueFromValueCount(1, (short)numToKeep);   // updates die value counts
					m_turn.SetIsFarkle(false);                                 // switches farkle flag to false
					cout << "You have kept " << numToKeep << " ones worth "
						<< numToKeep * 100 << " points!" << endl;
				}
				else if (numToKeep == 0)
				{
					// forces user to keep points if turn is currently a farkle
					if (m_turn.GetIsFarkle())
					{
						cout << "You must keep at least one 1 to avoid a farkle. "
							 << "How many would you like to keep? " << endl;
						numToKeep = -1;
					}
					else
					{
						cout << "You have chosen not to keep any ones." << endl;
					}
				}
				else
				{
					numToKeep = -1;
					cout << "Please enter 0 through " << m_turn.GetValueCount(1) << ": " << endl;
				}
			}
			// Error message for invalid string to int argument
			catch (invalid_argument& err1)
			{
				cout << err1.what() << " Please enter 0 through " 
					 << m_turn.GetValueCount(1) << ": " << endl;
			}
			// Error message if user enters a number that is too large for an int
			catch (out_of_range& err2)
			{
				cout << err2.what() << " Please enter 0 through " 
					 << m_turn.GetValueCount(1) << ": " << endl;
			}
		}
	}
}

// This function handles farkles. It resets the dice number, resets turn data, and passes play along
// and prints the scoreboard
void Game::PlayerFarkled()
{
	m_numOfDice = 6;            // resets dice count
	m_turn.ResetValueCounts();  // resets turn value counts
	m_turn.ResetScore();        // resets turn score
	m_playerTurn += 1;          // iterates players turn
	m_playerTurn %= m_playerList.size(); // sends turn back to first player after last players turn

	// Message to players, prints scoreboard
	cout << "You have farkled! It is now " << m_playerList.at(m_playerTurn).GetName()
		<< "'s turn." << endl;
	PrintScoreboard(m_playerList);
}

// This function prompts user for decision to keep points or roll again.
void Game::KeepOrRoll()
{
	string input = "";

	// Gives user data to make a decision / prompts for input
	cout << "Your current score is " << m_playerList.at(m_playerTurn).GetPlayerScore()
		<< ". You have gained " << m_turn.GetTurnScore() << " points this turn." << endl;

	if (m_playerList.at(m_playerTurn).GetPlayerScore() == 0 &&
		m_turn.GetTurnScore() < 1000)
	{
		cout << "Roll or evaluate current roll again (R/E)?" << endl;
		getline(cin, input);
		InputHandler::VerifyRE(input);

		if (input == "e" || input == "E")
		{
			EvaluateRollSets();
			EvaluateRollFives();
			EvaluateRollOnes();
			KeepOrRoll();
		}
		else if (input == "r" || input == "R")
		{
			PlayerRollAgain();
		}
	}
	else
	{
		cout << "Would you like to keep your score, roll, or evaluate the current roll again (K/R/E)? " << endl;

		// Takes input and validates input
		getline(cin, input);
		InputHandler::VerifyKRE(input);

		// Handles user decision making
		if (input == "K" || input == "k")
		{
			PlayerKeepScore();
		}
		else if (input == "R" || input == "r")
		{
			PlayerRollAgain();
		}
		else if (input == "E" || input == "e")
		{
			EvaluateRollSets();
			EvaluateRollFives();
			EvaluateRollOnes();
			KeepOrRoll();
		}
	}
}

// This function handles game logic if user keeps the points.  Determines if player is eligible to 
// keep points and resets turn data if points kept successfully.
void Game::PlayerKeepScore()
{
	cout << "Great job. " << m_turn.GetTurnScore() << " points have been added to your score.\n";

	m_playerList.at(m_playerTurn).AddToPlayerScore(m_turn.GetTurnScore()); //Updates player score
	m_turn.ResetScore();                                                   // Resets turn score
	m_turn.ResetValueCounts();                                             // resets turn value counts
	m_turn.SetIsFarkle(true);                                              // sets farkle to true
	m_numOfDice = 6;                                                       // resets number of dice

	//iterates player turn and loops back to first player after last players turn
	m_playerTurn += 1;
	m_playerTurn %= m_playerList.size();

	// Message to players / prints scoreboard
	cout << "It is now " << m_playerList.at(m_playerTurn).GetName() << "'s turn." << endl;
	PrintScoreboard(m_playerList);
}

// Handles logic if same player rolls again
void Game::PlayerRollAgain()
{
	m_turn.SetIsFarkle(true);   //reset farkle flag
	m_turn.ResetValueCounts();  //reset turn value counts
}

void Game::PrintScoreboard(vector<Player> playerArr)
{
	cout << "===============================" << endl;
	cout << "|       Current Scores        |" << endl;
	cout << "|-----------------------------|" << endl;
	for (unsigned int i = 0; i < playerArr.size(); i++)
	{   //prints players name and score on new lines
		cout << "| " << left << setw(17) << playerArr.at(i).GetName() << " | "
			<< setw(6) << playerArr.at(i).GetPlayerScore()
			<< setw(3) << right << "|" << endl;
		cout << "|-----------------------------|" << endl;
	}
	cout << "===============================" << endl;
	{

	}
}

void Game::test()
{
	//USED TO TEST FUNCTIONS
}