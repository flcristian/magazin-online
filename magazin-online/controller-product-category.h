#include "controller-products.h"

struct ControlProductCategory {
private:
	ProductCategory categoriiproduse[100];
	int dim;

	void atribuire() {
		ControlProduct controlprodus;
		ControlCategory controlcategorie;
		dim = 0;

		for (int i = 0; i < controlprodus.getDim(); i++) {
			Product produs = controlprodus.getProduct(i);
			int j = controlcategorie.findByName(produs.getCategory());
			if (j == -1) {
				Category x(controlcategorie.idUnic(), produs.getCategory());
				controlcategorie.addCategory(x);
				j = controlcategorie.getDim() - 1;
			}
			ProductCategory x(j + 1, produs.getID(), controlcategorie.getCategory(j).getID());
			categoriiproduse[dim] = x;
			dim++;
		}
	}

public:

	ControlProductCategory() {
		atribuire();
	}

	void produseCategorie(int produse[], int& n, int category_id) {
		n = 0;
		for (int i = 0; i < dim; i++) {
			if (categoriiproduse[i].getCategoryID() == category_id) {
				produse[n] = categoriiproduse[i].getProductID();
				n++;
			}
		}
	}

	void afisare() {
		for (int i = 0; i < dim; i++) {
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			categoriiproduse[i].descriereProductCategory();
		}
	}

};
