#include "controller-products.h"

struct ControlUser {
private:
	User users[100];
	int dim;

	void citire() {
		ifstream f("users.txt");
		dim = 0;

		while (!f.eof()) {
			string id, email, password, name1, name2, full_name, country, phone_number, type, status;

			f >> id;
			f >> email;
			f >> password;
			f >> name1;
			f >> name2;
			full_name = name1 + " " + name2;
			f >> country;
			f >> phone_number;
			f >> type;
			f >> status;

			User x(stoi(id), email, password, full_name, country, phone_number, type, status);
			users[dim] = x;
			dim++;
		}
		f.close();
	}

public:

	ControlUser() {
		citire();
	}

	User getUser(int i) {
		return this->users[i];
	}

	void modifyName(string full_name, int i) {
		this->users[i].setFullName(full_name);
	}

	void modifyNumber(string number, int i) {
		this->users[i].setPhoneNumber(number);
	}

	void modifyCountry(string country, int i) {
		this->users[i].setCountry(country);
	}

	void modifyPassword(string password, int i) {
		this->users[i].setPassword(password);
	}

	void modifyEmail(string email, int i) {
		this->users[i].setEmail(email);
	}

	void addManager(int i) {
		this->users[i].setType("Manager");
	}

	int getDim() {
		return this->dim;
	}

	int getIndice(int id) {
		for (int i = 0; i < dim; i++) {
			if (id == users[i].getID()) {
				return i;
			}
		}
		return -1;
	}

	int idUnic() {
		if (dim == 0) {
			return 1;
		}
		else {
			return users[dim - 1].getID() + 1;
		}
	}

	void addUser(User x) {
		users[dim] = x;
		dim++;
	}

	void afisareUsers() {
		for (int i = 0; i < dim; i++) {
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			users[i].descriereUser();
		}
	}

	string toSave() {
		string r = "";
		for (int i = 0; i < dim; i++) {
			r += users[i].toSave();
			if (i != dim - 1) {
				r += "\n";
			}
		}
		return r;
	}

	void banUser(int i) {
		this->users[i].setStatus("Banned");
	}

	void unbanUser(int i) {
		this->users[i].setStatus("Normal");
	}

	void getBannedIDs(int indici[], int& n) {
		for (int i = 0; i < dim; i++) {
			if (users[i].getStatus() == "Banned") {
				indici[n] = i;
				n++;
			}
		}
	}

	void afisareBannedUsersEmails(int indici[], int n) {
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		for (int i = 0; i < n; i++) {
			cout << users[indici[i]].getEmail() << " - " << users[indici[i]].getFullName() << " (Banned)" << endl;
		}
	}

	void getManagerIDs(int indici[], int& n) {
		for (int i = 0; i < dim; i++) {
			if (users[i].getType() == "Manager") {
				indici[n] = i;
				n++;
			}
		}
	}

	void afisareManagersEmails(int indici[], int n) {
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		for (int i = 0; i < n; i++) {
			cout << users[indici[i]].getEmail() << " - " << users[indici[i]].getFullName() << " (Manager)" << endl;
		}
	}

	void removeUser(int j) {
		for (int i = j; i < dim - 1; i++) {
			this->users[i] = this->users[i + 1];
		}
		dim--;
	}

	int findByEmail(string email) {
		for (int i = 0; i < dim; i++) {
			if (users[i].getEmail() == email) {
				return i;
			}
		}
		return -1;
	}

	int findByLoginDetails(string email, string password) {
		bool foundAnEmail = false;
		for (int i = 0; i < dim; i++) {
			if (users[i].getEmail() == email && users[i].getPassword() == password) {
				return i;
			}
			if (users[i].getEmail() == email) {
				foundAnEmail = true;
			}
		}
		if (foundAnEmail) {
			return -2;
		}
		else {
			return -1;
		}
	}

	void saveFile() {
		ofstream f("users.txt");

		f << toSave();
	}

	void viewBestClient(int ids[], int ammounts[], int n) {
		int indici[100];
		for (int i = 0; i < dim; i++) {
			indici[i] = getIndice(ids[i]);
		}
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Cel mai mare cumparator este : " << users[indici[0]].getFullName() << endl;
		cout << "Produse cumparate in valoare de : " << ammounts[0] << "$" << endl;
	}

	void viewSortedByQuantityBought(int ids[], int ammounts[], int n) {
		int indici[100];
		for (int i = 0; i < n; i++) {
			indici[i] = getIndice(ids[i]);
		}
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		for (int i = 0; i < n; i++) {
			cout << users[indici[i]].getFullName() << " : " << ammounts[i] << "$" << endl;
		}
	}

};
