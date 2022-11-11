#include "user.h"

struct Order {
private:
	int id = -1;
	int customer_id = -1;
	int ammount = -1;
	string order_email = "";
	string order_status = "";

public:

	Order() {
	}

	Order(int id, int customer_id, int ammount, string order_email, string order_status) {
		this->id = id;
		this->customer_id = customer_id;
		this->ammount = ammount;
		this->order_email = order_email;
		this->order_status = order_status;
	}

	int getID() {
		return this->id;
	}

	int getCustomerID() {
		return this->customer_id;
	}

	int getAmmount() {
		return this->ammount;
	}

	string getOrderEmail() {
		return this->order_email;
	}

	string getOrderStatus() {
		return this->order_status;
	}

	void setID(int id) {
		this->id = id;
	}

	void setCustomerID(int customer_id) {
		this->customer_id = customer_id;
	}

	void setAmmount(int ammount) {
		this->ammount = ammount;
	}

	void setOrderEmail(string order_email) {
		this->order_email = order_email;
	}

	void setOrderStatus(string order_status) {
		this->order_status = order_status;
	}

	void descriereOrder() {
		cout << "ID : " << id << endl;
		cout << "Customer ID : " << customer_id << endl;
		cout << "Ammount : " << ammount << endl;
		cout << "Order Email : " << order_email << endl;
		cout << "Order Status : " << order_status << endl;
	}

	string toSave() {
		string r = to_string(id) + " " + to_string(customer_id) + " " + to_string(ammount) + " " + order_email + " " + order_status;
		return r;
	}
};