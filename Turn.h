/* Tyler Coplan
 * IT-312-J1768
 * September 30, 2020
 * Final Project: Farkle
 *
 * Header file for turn class.  Turn class handles turn logic.
 * See Turn.cpp for more information
 */

#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include "Player.h"


class Turn
{
public:
	// Class constructor
	Turn();
	
	// Class destructor
	~Turn();

	// Class accessors
	short GetValueCount(short index);
	bool GetIsFarkle();
	int GetTurnScore();

	// Class mutators
	void AddRollToValueCount(short index);
	void SubtractValueFromValueCount(short index, short numToSubtract);
	void ResetValueCounts();
	void SetIsFarkle(bool isFarkle);
	void AddToTurnScore(int score);
	void ResetScore();

private:
	// Each index represents a die value, counts number of times rolled
	short m_valueCountArray[7] = {0, 0, 0, 0, 0, 0, 0};
	int m_score;
	bool m_isFarkle;

};

