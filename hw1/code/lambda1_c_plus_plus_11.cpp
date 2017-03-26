/*  ========================================================================
	$File: lambda1_c_plus_plus_11.cpp $
	$Date: 1/17/2017$
	$Revision: $
	$Creator: Christopher Huynh $
	$Notice: $
	======================================================================== */

#include <iostream>

int main(void)
{
	// Declaration and Initialization
	int a = 300;
	int b = 100;
	int c = 250;

	// Use Lambda funciton to turn variable d into a function that adds three variables.
	// Lambda function syntax: [capture] (paramaters) { body }
	auto addThreeNumbers = [] (int e, int f, int g){return e + f + g;};

	// Runs function addThreeNumbers and prints the return
	std::cout << addThreeNumbers(a, b, c);
}