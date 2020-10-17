/* Tyler Coplan
 * IT-312-J1768
 * September 30, 2020
 * Final Project: Farkle
 *
 * This file contains the main function for my Farkle program.  It seeds
 * the random number generator, instantiates the game, and runds the game
 * through a public function from the game class.
 */

#include <cstdlib>
#include "Game.h"

using namespace std;

int main()
{
	srand((unsigned)time(NULL));

	Game game;
	game.PlayFarkle();
}


