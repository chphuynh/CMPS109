/*  ========================================================================
	$File: rangedfor4_c_plus_plus_11.cpp $
	$Date: 1/18/2017$
	$Revision: $
	$Creator: Christopher Huynh $
	$Notice: $
	======================================================================== */

	#include <iostream>

	int main(void)
	{
		// Declares and initializes array
		int array[6] = {10, 2, 1, 4, 1, 2};

		// For loop iterates through array
		for(int& x : array)
		{
			// Prints element of array
			std::cout << x << std::endl;
		}
	}