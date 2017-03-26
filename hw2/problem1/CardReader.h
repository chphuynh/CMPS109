#include <stdio.h>

#define MAX_CLASS_SIZE 256
#define MAX_CLASSES 8

class CardReader
{
	private:
		int classrooms[MAX_CLASSES][MAX_CLASS_SIZE];
	public:
		CardReader();

		bool checkInToClass(int p_student_number, int p_class_number);
		bool checkOutOfClass(int p_student_number, int p_class_number);
		bool checkIfSeatOccupied(int class_number, int seat_number);
		int seatsAvailable(int class_number);
		int checkStudentLocation(int seat_number);

		virtual ~CardReader();
};