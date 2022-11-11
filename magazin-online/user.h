#include "product-category.h"

struct User {
private:
	int id = -1;
	string email = "";
	string password = "";
	string full_name = "";
	string country = "";
	string phone_number = "";
	string type = "";
	string status = "";

public:

	User() {
	}

	User(int id, string email, string password, string full_name, string country, string phone_number, string type, string status) {
		this->id = id;
		this->email = email;
		this->password = password;
		this->full_name = full_name;
		this->country = country;
		this->phone_number = phone_number;
		this->type = type;
		this->status = status;
	}

	int getID() {
		return this->id;
	}

	string getEmail() {
		return this->email;
	}

	string getPassword() {
		return this->password;
	}

	string getFullName() {
		return this->full_name;
	}

	string getCountry() {
		return this->country;
	}

	string getPhoneNumber() {
		return this->phone_number;
	}

	string getType() {
		return this->type;
	}

	string getStatus() {
		return this->status;
	}

	void setID(int id) {
		this->id = id;
	}

	void setEmail(string email) {
		this->email = email;
	}

	void setPassword(string password) {
		this->password = password;
	}

	void setFullName(string full_name) {
		this->full_name = full_name;
	}

	void setCountry(string country) {
		this->country = country;
	}

	void setPhoneNumber(string phone_number) {
		this->phone_number = phone_number;
	}

	void setType(string type) {
		this->type = type;
	}

	void setStatus(string status) {
		this->status = status;
	}

	void descriereUser() {
		cout << "ID : " << id << endl;
		cout << "Email : " << email << endl;
		cout << "Password : " << password << endl;
		cout << "Full Name : " << full_name << endl;
		cout << "Country : " << country << endl;
		cout << "Phone Number : " << phone_number << endl;
		cout << "Type : " << type << endl;
		cout << "Status : " << status << endl;
	}


	string toSave() {
		string r = to_string(id) + " " + email + " " + password + " " + full_name + " " + country + " " + phone_number + " " + type + " " + status;
		return r;
	}
};