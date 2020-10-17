/* Tyler Coplan
 * IT-312-J1768
 * September 30, 2020
 * Final Project: Farkle
 *
 * Header file for the game class.  Runs game and controls game flow
 * See Game.cpp for further description.
 */

#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include <stdexcept>
#include <fstream>
#include "Turn.h"
#include "Die.h"
#include "Player.h"
#include "InputHandler.h"

class Game
{
public:
	// Class constructor
	Game();

	// Class destructor
	~Game();

	// Run game function
	void PlayFarkle();
	void test();

private:
	// Game functions
	void ReadRules();
	void GetPlayers();
	void RollDice();
	void EvaluateRollSets();
	void EvaluateRollFives();
	void EvaluateRollOnes();
	void PlayerFarkled();
	void KeepOrRoll();
	void PlayerKeepScore();
	void PlayerRollAgain();
	void PrintScoreboard(std::vector<Player> playerArr);

	// Member variables
	std::vector<Player> m_playerList;
	Turn m_turn;
	short m_numOfDice;
	short m_playerTurn;
};

