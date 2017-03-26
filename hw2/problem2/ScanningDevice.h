#include <stdio.h>

#define MAX_COLORS 8
#define MAX_PRODUCTS 256

class ScanningDevice
{
	private:
		int products[MAX_COLORS][MAX_PRODUCTS];
	public:
		ScanningDevice();

		bool checkProductInToStock(int color_number, int product_number);
		bool checkProductOutOfStock(int color_number, int product_number);
		bool checkIfProductExistsInStock(int color_number, int product_number);
		int getNumberOfProductInStockByID(int product_number);
		int getNumberOfSpecificProductInStock(int product_number, int color_number);
		int getNumberOfProductInStockByColor(int color_number);
		int getNumberOfProductWithStock();

		~ScanningDevice();
};