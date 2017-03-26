/*  ========================================================================
	$File: auto2_c_plus_plus_11.cpp $
	$Date: 1/17/2017$
	$Revision: $
	$Creator: Christopher Huynh $
	$Notice: $
	======================================================================== */

#include <iostream>
#include <typeinfo>

int main(void)
{
	// Declaration and Initialization using auto
	auto a = 10; // variable a is an int because 10 is an int
	auto b = "hello"; // variable b is a char because "hello" is a string
	auto c = true; // variable c is bool because of true/false

	// Uses typeid to print the type of each variable
	std::cout << "Type of variable a is " << typeid(a).name() << std::endl;
	std::cout << "Type of variable b is " << typeid(b).name() << std::endl;
	std::cout << "Type of variable c is " << typeid(c).name() << std::endl;
}