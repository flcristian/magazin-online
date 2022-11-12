#include "controller-users.h"

struct ControlOrder {
private:
	Order orders[100];
	int dim;

	void citire() {
		ifstream f("orders.txt");
		dim = 0;

		while (!f.eof()) {
			string id, customer_id, ammount, order_email, order_status;

			f >> id;
			f >> customer_id;
			f >> ammount;
			f >> order_email;
			f >> order_status;

			Order x(stoi(id), stoi(customer_id), stoi(ammount), order_email, order_status);
			orders[dim] = x;
			dim++;
		}
		f.close();
	}

public:

	ControlOrder() {
		citire();
	}

	bool forBanUser(int ids[], int n, int id) {
		for (int i = 0; i < n; i++) {
			if (ids[i] == id) {
				return true;
			}
		}
		return false;
	}

	void changeEmail(string old_email, string email) {
		for (int i = 0; i < dim; i++) {
			if (orders[i].getOrderEmail() == old_email) {
				orders[i].setOrderEmail(email);
			}
		}
	}

	void banUser(int ids[], int& n, int id) {
		n = 0;
		int i = 0;
		while (i < dim) {
			if (orders[i].getCustomerID() == id) {
				orders[i].setOrderStatus("Canceled");
				if (!forBanUser(ids, n, orders[i].getID())) {
					ids[n] = orders[i].getID();
					n++;
				}
			}
			i++;
		}
	}

	int getIndice(int id) {
		for (int i = 0; i < dim; i++) {
			if (id == orders[i].getID()) {
				return i;
			}
		}
		return -1;
	}

	Order getOrder(int i) {
		return this->orders[i];
	}

	int getDim() {
		return this->dim;
	}

	int idUnic() {
		if (dim == 0) {
			return 1;
		}
		else {
			return orders[dim - 1].getID() + 1;
		}
	}

	void addOrder(Order x) {
		orders[dim] = x;
		dim++;
	}

	void afisareOrders() {
		for (int i = 0; i < dim; i++) {
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			orders[i].descriereOrder();
		}
	}

	string toSave() {
		string r = "";
		for (int i = 0; i < dim; i++) {
			r += orders[i].toSave();
			if (i != dim - 1) {
				r += "\n";
			}
		}
		return r;
	}

	void saveFile() {
		ofstream f("orders.txt");

		f << toSave();
	}

	void getAmmountsSpent(int ammounts[]) {
		dim = this->dim;
		for (int i = 0; i < dim; i++) {
			ammounts[orders[i].getCustomerID()] += orders[i].getAmmount();
		}
	}

	void frecventaOrders(int f[]) {
		for (int i = 0; i < dim; i++) {
			f[orders[i].getCustomerID()]++;
		}
	}

};