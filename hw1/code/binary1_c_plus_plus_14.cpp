/*  ========================================================================
	$File: binary1_c_plus_plus_14.cpp $
	$Date: 1/18/2017$
	$Revision: $
	$Creator: Christopher Huynh $
	$Notice: $
	======================================================================== */

#include <iostream>

int main(void)
{	
	// Uses binary literal for 10
	int x = 0b1010;

	// Uses decimal literal for 10
	int y = 10;

	// Should print true because binary literal and decimal literal should be
	// equal
	if(x == y)
		std::cout << "true";
	else
		std::cout << "false";
}