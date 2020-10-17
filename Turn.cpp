/* Tyler Coplan
 * IT-312-J1768
 * September 30, 2020
 * Final Project: Farkle
 *
 * Turn class handles the logic for each turn.  Keeps track of the current
 * turn score, keeps an array of the count of the values of each roll.
 */

#include "Turn.h"

using namespace std;

// Define class constructor
Turn::Turn()
{
	m_valueCountArray[7];
	m_score = 0;
	m_isFarkle = true;
}

// Define class destructor
Turn::~Turn()
{
}

// Define class accessors
short Turn::GetValueCount(short index)
{
	return m_valueCountArray[index];
}

int Turn::GetTurnScore()
{
	return m_score;
}

bool Turn::GetIsFarkle()
{
	return m_isFarkle;
}

// Define class mutators

// This mutator takes the argument of the die roll
void Turn::AddRollToValueCount(short index)
{
	m_valueCountArray[index] += 1;
}

// This mutator takes a die value as the index and how many to subtract
void Turn::SubtractValueFromValueCount(short index, short numToSubtract)
{
	m_valueCountArray[index] -= numToSubtract;
}

// This mutator resets the die value counts before each roll
void Turn::ResetValueCounts()
{
	int i = 1;
	while (i <= 7) {
		m_valueCountArray[i] = 0;
		i++;
	}
}

void Turn::AddToTurnScore(int score)
{
	m_score += score;
}

void Turn::SetIsFarkle(bool isFarkle)
{
	m_isFarkle = isFarkle;
}

void Turn::ResetScore()
{
	m_score = 0;
}

