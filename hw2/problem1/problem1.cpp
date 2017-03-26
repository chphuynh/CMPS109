
#include "CardReader.h"

// Prints the words true or false depending on callback
void printTF(bool callback)
{
	if(callback)
		printf("true\n");
	else
		printf("false\n");

}

int main(void)
{
	// Card Reader Declaration
	CardReader * cardReader = new CardReader();

	/* Testing the ability to check in and out of class */
	
	// Checking student with seat number 6 into class 4
	printTF(cardReader->checkInToClass(6, 4)); // Returns true after successful check in
	
	// Attempting to check same student into class 5
	printTF(cardReader->checkInToClass(6, 5)); // Should fail and return false

	// Attempting to check student out of wrong class
	printTF(cardReader->checkOutOfClass(6, 5)); // Should fail and return false

	// Checking student out of class 4
	printTF(cardReader->checkOutOfClass(6, 4)); // Returns true after successful check out

	/* Method that returns if seat is occupied in specific class */
	printTF(cardReader->checkInToClass(99, 8));
	printTF(cardReader->checkIfSeatOccupied(8, 99)); // returns true b\c seat 99 in class 8 is occupied.
	printTF(cardReader->checkIfSeatOccupied(3, 45)); // returns false b\c seat 45 is class 3 not occupied.

	/* Method to return number of available seats in a class */
	printTF(cardReader->checkInToClass(6, 8));
	printf("%d\n", cardReader->seatsAvailable(8)); // returns value of seats available in class 8 which is 254

	/* Inquire about location of student */
	printf("%d\n", cardReader->checkStudentLocation(99)); // returns student of seat 99's location, which is class 8

	printTF(cardReader->checkOutOfClass(99, 8));
	printf("%d\n", cardReader->checkStudentLocation(99)); // returns -1 for not in a class

	delete(cardReader);
	return 0;
}