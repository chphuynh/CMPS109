//#include <iostream>
#include "CardReader.h"

// CardReader Constructor
CardReader::CardReader()
{
	// Initializes all classrooms to zero
	for(int i = 0; i < MAX_CLASSES; i++)
		for(int j = 0; j < MAX_CLASS_SIZE; j++)
			classrooms[i][j] = 0;
}

bool CardReader::checkInToClass(int p_student_number, int p_class_number)
{	
	printf("Card Reader checking Student %d into Class %d\n", p_student_number, p_class_number);
	
	// Checks if class number in index
	if(p_class_number > MAX_CLASSES || p_class_number < 0)
	{
		printf("Invalid class.\n");
		return false;
	}

	// Checks if student number in index
	if(p_student_number > MAX_CLASS_SIZE || p_student_number < 0)
	{
		printf("Invalid student number.");
		return false;
	}

	// Iterates through classes to check if student is checked into another class
	for(int i = 0; i < MAX_CLASSES; i++)
		if(classrooms[i][p_student_number] == 1)
		{
			printf("Check in failed. Student still checked into class %d\n", i);
			return false;
		}

	// Sets the seat to 1 to signify seat is occupied
	classrooms[p_class_number][p_student_number] = 1;
	return true;
}

bool CardReader::checkOutOfClass(int p_student_number, int p_class_number)
{
	printf("Card Reader checking Student %d out of Class %d\n", p_student_number, p_class_number);
	
	// Check if class number is in index
	if(p_class_number > MAX_CLASSES || p_class_number < 0)
	{
		printf("Invalid class.\n");
		return false;
	}
		
	// Check if student number is in index
	if(p_student_number > MAX_CLASS_SIZE || p_student_number < 0)
	{
		printf("Invalid student number.");
		return false;
	}

	// If seat is occupied, set to unoccupied and return true
	if(classrooms[p_class_number][p_student_number] == 1)
	{
		classrooms[p_class_number][p_student_number] = 0;
		return true;
	}
	
	printf("Check out failed. Student not checked into this class.\n");
	return false;
}

bool CardReader::checkIfSeatOccupied(int class_number, int seat_number)
{
	printf("Card Reader checking if seat %d in class %d is occupied.\n", seat_number, class_number);

	// Checks if class_number is in index
	if(class_number > MAX_CLASSES || class_number < 0)
	{
		printf("Invalid class.\n");
		return false;
	}
		
	// Checks if seat number in index
	if(seat_number > MAX_CLASS_SIZE || seat_number < 0)
	{
		printf("Invalid student number.");
		return false;
	}
	
	// If seat is 1 for occupied return true
	if(classrooms[class_number][seat_number] == 1)
	{
		printf("Seat is occupied\n");
		return true;
	}

	printf("Seat is not occupied\n");
	return false;
}

int CardReader::seatsAvailable(int class_number)
{
	printf("Card Reader checking seats available in class %d\n", class_number);

	// Checks if class number is in index
	if(class_number > MAX_CLASSES || class_number < 0)
	{
		printf("Invalid Class\n");
		// Returns -1 to signify an error
		return -1;
	}
	int seat_counter = 256;

	// Iterates through array and subtracts from seat counter whenever
	// a seat is occupied
	for(int i = 0; i < MAX_CLASS_SIZE; i++)
		if(classrooms[class_number][i] == 1)
			seat_counter--;

	printf("Class %d has %d available seats.\n", class_number, seat_counter);
	return seat_counter;
}

int CardReader::checkStudentLocation(int seat_number)
{	
	// Checks if seat number in index
	if(seat_number > MAX_CLASS_SIZE || seat_number < 0)
	{
		printf("Invalid Student number\n");
		// Returns -2 for index error
		return -2;
	}

	int student_location = -1;

	// Iterates through array to find student location
	for(int i = 0; i < MAX_CLASSES; i++)
		if(classrooms[i][seat_number] == 1)
		{
			student_location = i;
			break;
		}

	// Returns class number where student is located
	// If not in a class, returns -1
	if(student_location != -1)
		printf("Student is currently in class %d\n", student_location);
	else
		printf("Student is not in a class.\n");

	return student_location;
}

// CardReader Deconstructor
CardReader::~CardReader()
{	

}