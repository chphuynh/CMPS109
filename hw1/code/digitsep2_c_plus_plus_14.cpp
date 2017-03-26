/*  ========================================================================
	$File: digitsep2_c_plus_plus_14.cpp $
	$Date: 1/18/2017$
	$Revision: $
	$Creator: Christopher Huynh $
	$Notice: $
	======================================================================== */

#include <iostream>

int main(void)
{	
	// Uses digit seperators to initialize 1 million
	int x = 1'000'000;

	// Uses regular syntax to initialize 1 million
	int y = 1000000;

	// Should return true as digit serperators do not change value
	if(x == y)
		std::cout << "true";
	else
		std::cout << "false";
}