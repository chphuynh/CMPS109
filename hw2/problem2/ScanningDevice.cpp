
#include "ScanningDevice.h"

// Constructor
ScanningDevice::ScanningDevice()
{
	// Initializes all array values as zero
	// Represents empty stock
	for(int i = 0; i < MAX_COLORS; i++)
		for(int j = 0; j < MAX_PRODUCTS; j++)
			products[i][j] = 0;
}

// Checks a product into stock
bool ScanningDevice::checkProductInToStock(int color_number, int product_number)
{
	// Checks index of color_number and product_number
	if(color_number >= MAX_COLORS || product_number >= MAX_PRODUCTS || color_number < 0 || product_number < 0)
	{
		printf("Color ID or Product ID out of index\n");	
		return false;
	}

	// Checks if product is at max stock
	if(products[color_number][product_number] > MAX_PRODUCTS)
	{	
		printf("Product stock full\n");
		return false;
	}

	// Increments product stock
	products[color_number][product_number]++;
	return true;
}

// Checks product out of stock
bool ScanningDevice::checkProductOutOfStock(int color_number, int product_number)
{
	// Checks if color_number and product_number is within index
	if(color_number >= MAX_COLORS || product_number >= MAX_PRODUCTS || color_number < 0 || product_number < 0)
	{
		printf("Color ID or Product ID out of index\n");	
		return false;
	}

	// Checks if there is no stock to check out
	if(products[color_number][product_number] < 1)
	{	
		printf("No product in stock to check out\n");
		return false; 
	}
	
	// Decrements product counter
	products[color_number][product_number]--;
	return true;
}

// Checks if a specific product and color exists in stock
bool ScanningDevice::checkIfProductExistsInStock(int color_number, int product_number)
{
	// Checks if color_number and product_number is in index
	if(product_number >= MAX_PRODUCTS || product_number < 0 || color_number >= MAX_COLORS || color_number < 0)
	{
		printf("Color ID or Product ID out of index\n");	
		return false;
	}

	// Returns true if there are 1 or more items 
	if(products[color_number][product_number] > 0)
		return true;

	return false;
}

// Retrieves number of items for specific product
int ScanningDevice::getNumberOfProductInStockByID(int product_number)
{
	int product_count = 0;

	// If index out of bounds returns zero
	if(product_number >= MAX_PRODUCTS || product_number < 0)
		return product_count;

	// Iterates through array at product ID and adds stock to total count
	for(int i = 0; i < MAX_COLORS; i++)
		product_count += products[i][product_number];

	return product_count;
}

// Retrieves number of items for specific product and color
int ScanningDevice::getNumberOfSpecificProductInStock(int product_number, int color_number)
{
	// if index out of bounds returns zero
	if(product_number >= MAX_PRODUCTS || product_number < 0 || color_number >= MAX_COLORS || color_number < 0)
		return 0;

	// Returns product count at specific array location
	int product_count = products[color_number][product_number];

	return product_count;
}

// Retrieves number of items for specific color
int ScanningDevice::getNumberOfProductInStockByColor(int color_number)
{
	int product_count = 0;

	// if index out of bound returns zero
	if(color_number >= MAX_COLORS || color_number < 0)
		return product_count;

	// iterates through array at color ID and adds stock to total count
	for(int i = 0; i < MAX_PRODUCTS; i++)
		product_count += products[color_number][i];

	return product_count;
}

// Returns number of product with stock
int ScanningDevice::getNumberOfProductWithStock()
{
	int product_with_stock_count = 0;
	// Iterates through every element in array
	for(int j = 0; j < MAX_PRODUCTS; j++)
		for(int i = 0; i < MAX_COLORS; i++)
			if(products[i][j] > 0)
			{
				// Increments counter when any item with more than 1 stock
				// is found
				product_with_stock_count++;
				break;
			}

	return product_with_stock_count;
}

// Decontructor
ScanningDevice::~ScanningDevice()
{

}