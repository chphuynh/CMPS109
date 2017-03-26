#include "Heap.h"
#include <stdlib.h>

// Adjusts the heap during delMax()
// Remains unchanged from given pseudocode
void Heap::adjust (int a[], int i, int n)
{
	int j = 2*i, item = a[i];
	while ( j <= n )
	{
		if (j<n && (a[j] < a[j+1])) j++;
		// Compare left and right child
		// and let j be the larger child
		if ( item >= a[j] ) break;
		a[j/2] = a[j]; j*=2;
	}
	a[j/2] = item;
}

// Heap constructor
// Remains unchanged from given pseudocode
Heap::Heap(int MSize):MaxSize(MSize)
{
	array = (int *) calloc(MSize+1,sizeof(int));
	Nel = 0;
}

// Heap copy constructor
// Sets MaxSize and Nel to same as target Heap
Heap::Heap(const Heap &heap):MaxSize(heap.MaxSize), Nel(heap.Nel)
{
	// Allocates array to same size as target Heap
	array = (int *) calloc(MaxSize+1, sizeof(int));

	// Temporarily point to target heap array
	int * temp = heap.array;

	for(int i = 0; i < MaxSize+1; i++)
	{
		// Copy the values from target heap array
		array[i] = temp[i];
	}
}

// Heap insert
// Added 1 line to pseudocode
bool Heap::insert (int item)
{
	int i = ++Nel;

	if ( i > MaxSize)
	{
		std::cout << "heap size exceeded" << std::endl;
		// Ensures counter stays at MaxSize and does not keep going
		Nel--;
		return false;
	}

	while ( (i > 1 ) && ( array[i/2] < item )) 
	{
		array[i] = array[i/2];
		i/=2;
	}
	array[i] = item;
	adjust(array,1,Nel);
}

// Heap delMax
// delMax now shifts array left and replaces the empty spot with zeros
bool Heap::delMax(int & item)
{
	if ( !Nel) 
	{ 
		std::cout << "heap is empty" << std::endl;
		return false; 
	}
	item = array[1];
	array [1] = array[Nel];
	array[Nel] = 0;
	Nel--;
	adjust (array,1,Nel);
	return true;
}

// Heap getMaxSize
// Uses const so it can be used in the overload operators
int Heap::getMaxSize() const
{
	return MaxSize;
}

// Heap getNel
// Uses const so it can be used in the overload operators
int Heap::getNel() const
{
	return Nel;
}

// Heap getArray
// Uses const so it can be used in the overload operators
int * Heap::getArray() const
{
	return array;
}

// Heap Deconstructor
Heap::~Heap()
{

}

// Heap operator+
Heap Heap::operator+(const Heap& b)
{
	// MaxSize of heap is now the total of both MaxSize
	Heap heap(this->getMaxSize() + b.getMaxSize());
	int item;
	// Temporarily stores seperate array
	int * temp = this->getArray();
	// Individual insert each element in heap
	for(int i = 1; i <= this->getNel(); i++)
		heap.insert(temp[i]);
	// Creates another temp array
	temp = b.getArray();
	// Individual insert each element in heap
	for(int i = 1; i <= this->getNel(); i++ )
		heap.insert(temp[i]);

	// Returns new heap with both heaps combined
	return heap;
}

// Heap operator+
// Performs simple insert on heap with number
Heap Heap::operator+(int number)
{
	this->insert(number);
	return *this;
}

// Heap operator[]
int Heap::operator[](int kthLargest)
{	
	// Copies heap into temporary heap.
	Heap heap(*this);
	int item;
	// Deletes max of temporary heap k times.
	for(int i = 1; i <= kthLargest; i++)
	{
		heap.delMax(item);
		//std::cout << item << std::endl;
	}
	// Returns the last deleted Max
	return item;
}

// Heap operator=
// Creates a heap using the copy constructor
// and returns it
Heap Heap::operator=(const Heap &b)
{
	Heap heap(b);
	return heap;
}

// Heap operator+=
// Inserts elements of 2nd heap into 1st heap
Heap Heap::operator+=(const Heap &b)
{
	int * temp = b.getArray();
	for(int i = 1; i <= b.getNel(); i++)
		this->insert(temp[i]);
	return *this;
}

// Heap operator+=
// Performs heap insert with number
Heap Heap::operator+=(int number)
{
	this->insert(number);
	return *this;
}

// Heap operator<<
// Prints the heap in the format: Heap array = {x1,x2,...,xn}
std::ostream &operator<<(std::ostream &os, const Heap &heap)
{
	os << "Heap array = {";
	// Uses temp array so source array is not affected
	int * temp = heap.getArray();
	// Iterates through elements of heap
	for(int i = 1; i < heap.getMaxSize(); i++)
		os << temp[i] << ", ";
	// Formats end of print
	os << temp[heap.getMaxSize()] << "}\n";
	return os;
}