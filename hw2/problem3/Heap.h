#include <iostream>

class Heap
{
	private:
		int * array;
		int MaxSize, Nel;
		void adjust (int a[], int i, int n);

	public:
		// Constructor
		Heap(int MSize);

		// Copy Constructor
		Heap(const Heap &heap);

		// Modifiers
		bool insert (int item);
		bool delMax(int & item);

		// Selectors
		int getMaxSize() const;
		int getNel() const;
		int * getArray() const;

		// Operators
		Heap operator+(const Heap &b);
		Heap operator+(int number);
		int operator[](int kthLargest);
		Heap operator=(const Heap &b);
		Heap operator+=(const Heap &b);
		Heap operator+=(int number);
		friend std::ostream &operator<<(std::ostream &os, const Heap &heap);
		
		// Deconstructor
		~Heap();
};