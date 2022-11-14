#include "controller-categories.h"

struct ControlProduct {
private:
	Product produse[100];
	int dim;

	void citire() {
		ifstream f("produse.txt");
		dim = 0;

		while (!f.eof()) {
			string id, name, price, category, stock;

			f >> id;
			f >> name;
			f >> price;
			f >> category;
			f >> stock;

			Product x(stoi(id), name, stoi(price), category, stoi(stock));
			produse[dim] = x;
			dim++;
		}
		f.close();
	}

public:

	ControlProduct() {
		citire();
	}

	int idUnic() {
		if (dim == 0) {
			return 1;
		}
		else {
			return produse[dim - 1].getID() + 1;
		}
	}

	Product getByID(int id) {
		for (int i = 0; i < dim; i++) {
			if (id == produse[i].getID()) {
				return produse[i];
			}
		}
		return Product();
	}

	int getIndice(int id) {
		for (int i = 0; i < dim; i++) {
			if (id == produse[i].getID()) {
				return i;
			}
		}
		return -1;
	}

	void seeDetails(int i) {
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		produse[i].descriereProdus();
	}

	void changeProductName(int i, string name) {
		this->produse[i].setName(name);
	}

	void changeProductPrice(int i, int price) {
		this->produse[i].setPrice(price);
	}

	void changeProductCategory(int i, string category) {
		this->produse[i].setCategory(category);
	}

	void changeProductStock(int i, int stock) {
		this->produse[i].setStock(stock);
	}

	void changeProduct(int i, Product produs) {
		this->produse[i] = produs;
	}

	void removeProduct(int j) {
		for (int i = j; i < dim - 1; i++) {
			this->produse[i] = produse[i + 1];
		}
		dim--;
	}

	void addProduct(Product x) {
		produse[dim] = x;
		dim++;
	}
	
	Product getProduct(int i) {
		return this->produse[i];
	}

	void updateStock(int i, int cantitate) {
		this->produse[i].setStock(produse[i].getStock() - cantitate);
	}

	int getDim() {
		return dim;
	}

	void afisareProduse() {
		for (int i = 0; i < dim; i++) {
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			produse[i].descriereProdus();
		}
	}

	int findByName(string productName) {
		for (int i = 0; i < dim; i++) {
			if (produse[i].getName() == productName) {
				return i;
			}
		}
		return -1;
	}

	void afisareProduseClient() {
		for (int i = 0; i < dim; i++) {
			Product x = produse[i];
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "Name : " << x.getName() << endl;
			cout << "Category : " << x.getCategory() << endl;
			cout << "Price : " << x.getPrice() << endl;
			cout << "Stock Ammount : " << x.getStock() << endl;
		}
	}

	string toSave() {
		string r = "";
		for (int i = 0; i < dim; i++) {
			r += produse[i].toSave();
			if (i != dim - 1) {
				r += "\n";
			}
		}
		return r;
	}

	void saveFile() {
		ofstream f("produse.txt");

		f << toSave();
	}

	void getAllProducts(Product products[], int& d) {
		for (int i = 0; i < dim; i++) {
			products[i] = produse[i];
		}
		d = dim;
	}
};
