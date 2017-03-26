#include "Heap.h"

int main(void)
{
	// Create a heap of size 5
	Heap heap1(5);

	// Insert 2 elements into heap
	heap1.insert(10);
	heap1.insert(5);

	// Create a copy of heap1 as heap2
	Heap heap2(heap1);

	// Print the the heaps to show they are similar
	std::cout << heap1;
	std::cout << heap2 << std::endl;

	// Deleting from heap2 does not affect heap 1
	int item;
	heap2.delMax(item);
	std::cout << heap1;
	std::cout << heap2 << std::endl;

	// Addition of 2 heaps create a heap with both heaps combined
	Heap heap3 = heap1 + heap2;
	std::cout << heap3 << std::endl;

	// Addition of heap and integer
	Heap heap4 = heap2 + 45;
	std::cout << heap4 << std::endl;

	// Return 2nd largest in heap4
	std::cout << heap4[2] << std::endl << std::endl;

	// Assignment operator for heap
	heap4 = heap2;
	std::cout << heap4 << std::endl;

	// Operator+= for heap
	heap4 += heap2;
	std::cout << heap4 << std::endl;

	// Operator+= for integer
	heap4 += 1;
	std::cout << heap4 << std::endl;

	return 0;
}