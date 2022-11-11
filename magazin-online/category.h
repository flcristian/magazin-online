#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Category {
private:

	int id = -1;
	string name = "";

public:

	Category() {
	}

	Category(int id, string name) {
		this->id = id;
		this->name = name;
	}

	int getID() {
		return this->id;
	}

	string getName() {
		return this->name;
	}

	void setID(int id) {
		this->id = id;
	}

	void setName(string name) {
		this->name = name;
	}

	void descriereCategorie() {
		cout << "ID : " << id << endl;
		cout << "Name : " << name << endl;
	}
};