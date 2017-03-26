
#include "ScanningDevice.h"

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
	// Initializing Scanning Device
	ScanningDevice * scanDevice = new ScanningDevice();

	// Checking in products with (colorID, productID)
	printTF(scanDevice->checkProductInToStock(5, 45)); // returns true when checked in
	printTF(scanDevice->checkProductInToStock(1, 23)); // returns true when checked in
	printTF(scanDevice->checkProductInToStock(1, 45)); // returns true when checked in
	printTF(scanDevice->checkProductInToStock(3, 78)); // returns true when checked in
	printTF(scanDevice->checkProductInToStock(3, 78)); // returns true when checked in
	printTF(scanDevice->checkProductInToStock(-1, 2)); // returns false because invalid color id
	printTF(scanDevice->checkProductInToStock(9, 2));  // returns false because invalid color id
	printTF(scanDevice->checkProductInToStock(2, -5)); // returns false because invalid product id
	printTF(scanDevice->checkProductInToStock(2, 256));  // returns false because invalid product id

	// Checking product out of stock
	printTF(scanDevice->checkProductOutOfStock(1, 23)); // returns true when checked out
	printTF(scanDevice->checkProductOutOfStock(4, 22)); // returns false because that product not in stock

	// Checking items exists in inventory
	printTF(scanDevice->checkIfProductExistsInStock(5, 45)); // returns true because product in stock
	printTF(scanDevice->checkIfProductExistsInStock(3, 22)); // returns false because no product in stock

	// Checking items of specific item id
	printf("%d\n", scanDevice->getNumberOfProductInStockByID(78)); // returns 2
	printf("%d\n", scanDevice->getNumberOfProductInStockByID(45)); // returns 2
	printf("%d\n", scanDevice->getNumberOfProductInStockByID(23)); // returns 0
	printf("%d\n", scanDevice->getNumberOfProductInStockByID(21)); // returns 0

	// Checking items of specific by (item id, color id)
	printf("%d\n", scanDevice->getNumberOfSpecificProductInStock(78, 3)); // returns 2
	printf("%d\n", scanDevice->getNumberOfSpecificProductInStock(45, 6)); // returns 0

	// Checking items of specific color
	printf("%d\n", scanDevice->getNumberOfProductInStockByColor(3)); // returns 2
	printf("%d\n", scanDevice->getNumberOfProductInStockByColor(4)); // returns 0

	// Checking number of product types having stock
	printf("%d\n", scanDevice->getNumberOfProductWithStock()); // returns 2

	delete(scanDevice);
}