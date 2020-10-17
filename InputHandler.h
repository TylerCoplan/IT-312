/* Tyler Coplan
 * IT-312-J1768
 * September 30, 2020
 * Final Project: Farkle
 */

#pragma once

#include <string>
#include <iostream>
#include <stdexcept>

class InputHandler
{
public:
	static void VerifyYN(std::string& YorN);
	static void VerifyKRE(std::string& kre);
	static void VerifyRE(std::string& re);
};

