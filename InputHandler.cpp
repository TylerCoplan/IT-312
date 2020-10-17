/* Tyler Coplan
 * IT-312-J1768
 * September 30, 2020
 * Final Project: Farkle
 *
 * Validates user input to ensure an appropriate option is selected.
 */

#include "InputHandler.h"

using namespace std;

// Verifies input is either y or n and keeps bugging the user until they input correctly
void InputHandler::VerifyYN(string& YorN)
{
	while (YorN != "Y" && YorN != "y" &&
		   YorN != "N" && YorN != "n")
	{
		std::cout << "Please enter either \"y\" or \"n\": " << std::endl;
		getline(std::cin, YorN);
	}
}

// Verifies input is either k or r or e
void InputHandler::VerifyKRE(string& kre)
{
	while (kre != "k" && kre != "K" &&
		   kre != "r" && kre != "R" &&
		   kre != "e" && kre != "E")
	{
		cout << "Please enter either \"k\" or \"r\" or \"e\": " << endl;
		getline(cin, kre);
	}
}

// Verifies the input is either r or e
void InputHandler::VerifyRE(string& re)
{
	while (re != "r" && re != "R" &&
		   re != "e" && re != "E")
	{
		cout << "Please enter either \"r\" or \"e\": " << endl;
		getline(cin, re);
	}
}