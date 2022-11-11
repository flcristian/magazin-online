#include "product.h"

struct ProductCategory {
private:

	int id = -1;
	int product_id = -1;
	int category_id = -1;

public:

	ProductCategory() {
	}

	ProductCategory(int id, int product_id, int category_id) {
		this->id = id;
		this->product_id = product_id;
		this->category_id = category_id;
	}

	int getID() {
		return this->id;
	}

	int getProductID() {
		return this->product_id;
	}

	int getCategoryID() {
		return this->category_id;
	}

	void setID(int id) {
		this->id = id;
	}

	void setProductID() {
		this->product_id = product_id;
	}

	void setCategoryID() {
		this->category_id = category_id;
	}

	void descriereProductCategory() {
		cout << "ID : " << id << endl;
		cout << "Product ID : " << product_id << endl;
		cout << "Category ID : " << category_id << endl;
	}
};