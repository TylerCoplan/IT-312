/* Tyler Coplan
 * IT-312-J1768
 * September 30, 2020
 * Final Project: Farkle
 *
 * Header file for Player class. See Player.cpp for full description.
 */

#pragma once
#include <string>

class Player
{
public:
	// Class constructors
	Player();
	Player(std::string name);

	// Class destructor
	~Player();

	// Class accessors
	std::string GetName();
	int GetPlayerScore();

	// Class mutators
	void SetName(std::string name);
	void AddToPlayerScore(int score);

private:
	std::string m_name;
	int m_score;
};

