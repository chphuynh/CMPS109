/*  ========================================================================
	$File: sizeof6_c_plus_plus_11.cpp $
	$Date: 1/18/2017$
	$Revision: $
	$Creator: Christopher Huynh $
	$Notice: $
	======================================================================== */

#include <iostream>

// Creates object dog with member number
struct Dogs {
	int number;
};

int main(void)
{
	// Sets x to the size of member number within Dogs.
	// Notice how we do not need to have an explicit object created.
	auto x = sizeof(Dogs::number);

	// Prints sizeof
	std::cout << x;
}