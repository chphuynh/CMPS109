/*  ========================================================================
	$File: deprecated3_c_plus_plus_14.cpp $
	$Date: 1/18/2017$
	$Revision: $
	$Creator: Christopher Huynh $
	$Notice: $
	======================================================================== */

// Use this tag to mark deprecated
[[deprecated]] 
int addTwo(int a, int b)
{
	return a + b;
}

// Use this tag to mark deprecated with a message
[[deprecated("use addition operators instead")]] 
int addNumber(int a, int b)
{
	return a + b;
}

int main(void)
{	
	addTwo(1, 3); // warning: 'addTwo' is deprecated
	addNumber(1, 10); //warning: 'addNumber' is deprecated:
					  // use addition operators instead"
}