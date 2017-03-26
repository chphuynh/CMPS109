/*  ========================================================================
	$File: delegate5_c_plus_plus_11.cpp $
	$Date: 1/18/2017$
	$Revision: $
	$Creator: Christopher Huynh $
	$Notice: $
	======================================================================== */

	#include <iostream>

	// Class dogs which only holds number of dogs
	class Dogs {
		int number;

		public:
			// First constructor: if used with number it will set number
			// of dogs to that number
			Dogs(int dogCount) : number(dogCount) {}

			// Second constructor: delegates first contructor to create
			// Dog class with 0 dogs.
			Dogs() : Dogs(0) {}

			// Function to print the number of dogs
			int PrintNum(void)
			{
				return number;
			}
	};

	int main(void)
	{	
		// Declares and initializes variable a as dog class
		// Uses constructor that delegates
		 Dogs a = Dogs();

		// Prints the number of dogs to console
		 std::cout << a.PrintNum();
	}