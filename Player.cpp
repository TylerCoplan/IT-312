/* Tyler Coplan
 * IT-312-J1768
 * September 30, 2020
 * Final Project: Farkle
 *
 * Player object with two members, name and score.  Accessors
 * and mutators for the member variables and manipulates strings
 * to prevent names from being too long.
 */

#include "Player.h"

using namespace std;

// Define class constructors
Player::Player(string name) {
	name = (name.length() > 15) ? name.substr(0, 15) : name;
	m_name = name;
	m_score = 0;
}

Player::Player()
{
	m_name = "default";
	m_score = 0;
}

// Define class destructor
Player::~Player()
{
}

// Define class accessors
string Player::GetName() 
{
	return m_name;
}

int Player::GetPlayerScore() 
{
	return m_score;
}

// Define class mutators
void Player::SetName(string name)
{
	// shortens really long names
	if (name.length() > 15)
	{
		name = name.substr(0, 15);
	}
	m_name = name;
}

void Player::AddToPlayerScore(int score)
{
	m_score += score;
}


