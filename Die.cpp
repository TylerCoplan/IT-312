/* Tyler Coplan
 * IT-312-J1768
 * September 30, 2020
 * Final Project: Farkle
 *
 * Die object holds an integer value and rolls a die using
 * the c standard library random function.  Class also returns
 * the die value through public accessor functions.
 */

#include "Die.h"

// Define class constructor
Die::Die()
{
	m_value = 0;
}

// Define class destructor
Die::~Die()
{
}

// Define class accessor
short Die::GetValue()
{
	return m_value;
}

// Define class mutator
void Die::Roll()
{
	m_value = (rand() % 6) + 1;
}
