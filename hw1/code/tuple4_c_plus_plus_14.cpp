/*  ========================================================================
	$File: tuple4_c_plus_plus_14.cpp $
	$Date: 1/18/2017$
	$Revision: $
	$Creator: Christopher Huynh $
	$Notice: $
	======================================================================== */

#include <iostream>
#include <tuple>

int main(void)
{
	// Creates a tuple with types int, float, and bool
	std::tuple<int, float, bool> x(10, 6.41, true);	

	// sets y to the int value within tuple x
	int y = std::get<int>(x);

	// sets z to the float value within tuple x
	float z = std::get<float>(x);

	// Prints the y and z
	std::cout << y << std::endl << z << std::endl;
}