#include "order.h"

struct OrderDetails {
private:
	int id = -1;
	int order_id = -1;
	int product_id = -1;
	int price = -1;
	int quantity = -1;
	string status = "";

public:

	OrderDetails() {
	}

	OrderDetails(int id, int order_id, int product_id, int price, int quantity, string status) {
		this->id = id;
		this->order_id = order_id;
		this->product_id = product_id;
		this->price = price;
		this->quantity = quantity;
		this->status = status;
	}

	int getID() {
		return this->id;
	}

	int getOrderID() {
		return this->order_id;
	}

	int getProductID() {
		return this->product_id;
	}

	int getPrice() {
		return this->price;
	}

	int getQuantity() {
		return this->quantity;
	}

	string getStatus() {
		return this->status;
	}

	void setID(int id) {
		this->id = id;
	}

	void setOrderID(int order_id) {
		this->order_id = order_id;
	}

	void setProductID(int product_id) {
		this->product_id = product_id;
	}

	void setPrice(int price) {
		this->price = price;
	}

	void setQuantity(int quantity) {
		this->quantity = quantity;
	}

	void setStatus(string status) {
		this->status = status;
	}

	void descriereOrderDetails() {
		cout << "ID : " << id << endl;
		cout << "Order ID : " << order_id << endl;
		cout << "Product ID : " << product_id << endl;
		cout << "Price : " << price << endl;
		cout << "Quantity : " << quantity << endl;
		cout << "Status : " << status << endl;
	}

	string toSave() {
		string r = to_string(id) + " " + to_string(order_id) + " " + to_string(product_id) + " " + to_string(price) + " " + to_string(quantity) + " " + status;
		return r;
	}
};