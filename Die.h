/* Tyler Coplan
 * IT-312-J1768
 * September 30, 2020
 * Final Project: Farkle
 *
 * Header file for Die class. See Die.cpp for full description
 */

#pragma once
#include <cstdlib>
class Die
{
public:
	// Class constructor
	Die();

	// Class destructor
	~Die();

	// Class accessor
	short GetValue();

	// Class mutator
	void Roll();

private:
	short m_value;
};

