#include "options.h"

struct Product {
private:
	int id = -1;
	string name = "";
	int price = -1;
	string category = "";
	int stock = -1;

public:

	Product() {
	}

	Product(int id, string name, int price, string category, int stock) {
		this->id = id;
		this->name = name;
		this->price = price;
		this->category = category;
		this->stock = stock;
	}

	int getID() {
		return this->id;
	}

	string getName() {
		return this->name;
	}

	int getPrice() {
		return this->price;
	}

	string getCategory() {
		return this->category;
	}

	int getStock() {
		return this->stock;
	}

	void setID(int id) {
		this->id = id;
	}

	void setName(string name) {
		this->name = name;
	}

	void setPrice(int price) {
		this->price = price;
	}

	void setCategory(string category) {
		this->category = category;
	}

	void setStock(int stock) {
		this->stock = stock;
	}

	void descriereProdus() {
		cout << "ID : " << id << endl;
		cout << "Name : " << name << endl;
		cout << "Price : " << price << endl;
		cout << "Category : " << category << endl;
		cout << "Stock : " << stock << endl;
	}

	string toSave() {
		string r = to_string(id) + " " + name + " " + to_string(price) + " " + category + " " + to_string(stock);
		return r;
	}
};