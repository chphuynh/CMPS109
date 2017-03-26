/*  ========================================================================
	$File: nullptr3_c_plus_plus_11.cpp $
	$Date: 1/18/2017$
	$Revision: $
	$Creator: Christopher Huynh $
	$Notice: $
	======================================================================== */

#include <iostream>

int main(void)
{
	// Creates function to test if a value is null or not
	auto g = [] (auto a)
	{
		if(a)
			std::cout << "Input not null";
		else
			std::cout << "Input is null";
	};

	// Uses nullptr as an arguement to prove nullptr is similar to NULL
	g(nullptr);
}