#include "order-details.h"

struct ControlCategory {
private:
	Category categorii[100];
	int dim;

	void citire() {
		ifstream f("categori.txt");
		dim = 0;

		while (!f.eof()) {
			string id, name;

			f >> id;
			f >> name;

			Category x(stoi(id), name);
			categorii[dim] = x;
			dim++;
		}
		f.close();
	}

public:

	ControlCategory() {
		citire();
	}

	int idUnic() {
		if (dim == 0) {
			return 1;
		}
		else {
			return categorii[dim - 1].getID() + 1;
		}
	}

	int findByName(string name) {
		for (int i = 0; i < dim; i++) {
			if (categorii[i].getName() == name) {
				return i;
			}
		}
		return -1;
	}

	Category getCategory(int i) {
		return categorii[i];
	}

	void addCategory(Category x) {
		categorii[dim] = x;
		dim++;
	}

	int getDim() {
		return dim;
	}

	void afisareListaCategorii() {
		for (int i = 0; i < dim; i++) {		
			cout << categorii[i].getName() << endl;
		}
	}

	void afisareCategorii() {
		for (int i = 0; i < dim; i++) {
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			categorii[i].descriereCategorie();
		}
	}

};
