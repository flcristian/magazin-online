#include "controller-orders.h"

struct ControlOrderDetails {
private:
	ControlOrder controlorder;
	OrderDetails orderdetails[100];
	int dim;

	void citire() {
		ifstream f("orderdetails.txt");
		dim = 0;

		while (!f.eof()) {
			string id, order_id, product_id, price, quantity, status;

			f >> id;
			f >> order_id;
			f >> product_id;
			f >> price;
			f >> quantity;
			f >> status;

			OrderDetails x(stoi(id), stoi(order_id), stoi(product_id), stoi(price), stoi(quantity), status);
			orderdetails[dim] = x;
			dim++;
		}
		f.close();
	}

public:

	ControlOrderDetails() {
		citire();
	}

	bool forBanUser(int id, int ids[], int n) {
		for (int i = 0; i < n; i++) {
			if (ids[i] == id) {
				return true;
			}
		}
		return false;
	}

	void banUser(int ids[], int n, int productIDs[], int quantities[], int& d) {
		d = 0;
		int i = 0;
		while (i < dim) {
			if (forBanUser(orderdetails[i].getOrderID(), ids, n) && orderdetails[i].getStatus() != "Canceled") {
				productIDs[d] = orderdetails[i].getProductID();
				quantities[d] = orderdetails[i].getQuantity();
				d++;
				orderdetails[i].setStatus("Canceled");
			}
			i++;
		}
	}

	OrderDetails getOrderDetails(int i) {
		return this->orderdetails[i];
	}

	int getDim() {
		return this->dim;
	}
	 
	int idUnic() {
		if (dim == 0) {
			return 1;
		}
		else {
			return orderdetails[dim - 1].getID() + 1;
		}
	}

	void modifyOrderStatus(int orderID, string status) {
		for (int i = 0; i < dim; i++) {
			if (orderdetails[i].getOrderID() == orderID) {
				orderdetails[i].setStatus(status);
			}
		}
	}

	void getIDsFromOrderID(int orderID, int order_detail_ids[], int& n) {
		for (int i = 0; i < dim; i++) {
			if (orderdetails[i].getOrderID() == orderID) {
				order_detail_ids[n] = orderdetails[i].getID();
				n++;
			}
		}
	}

	void getIDsFromOrderIDWithProductIDs(int orderID, int order_detail_ids[], int product_ids[], int& n) {
		for (int i = 0; i < dim; i++) {
			if (orderdetails[i].getOrderID() == orderID) {
				order_detail_ids[n] = orderdetails[i].getID();
				product_ids[n] = orderdetails[i].getProductID();
				n++;
			}
		}
	}

	int getIndice(int id) {
		for (int i = 0; i < dim; i++) {
			if (orderdetails[i].getID() == id) {
				return i;
			}
		}
		return -1;
	}

	void removeOrderDetails(int pozitie) {
		for (int i = pozitie; i < dim - 1; i++) {
			orderdetails[i] = orderdetails[i + 1];
		}
		dim--;
	}

	void updateOrderDetails(int i, int cantitate, int pret) {
		this->orderdetails[i].setQuantity(cantitate);
		this->orderdetails[i].setPrice(pret);
	}

	int findByProductAndOrder(int productID, int orderID) {
		for (int i = 0; i < dim; i++) {
			if (orderdetails[i].getOrderID() == orderID && orderdetails[i].getProductID() == productID) {
				return i;
			}
		}
		return -1;
	}

	void produseCos(int id, OrderDetails detalii[], int& n) {
		n = 0;
		for (int i = 0; i < dim; i++) {
			if (orderdetails[i].getOrderID() == id) {
				detalii[n] = orderdetails[i];
				n++;
			}
		}
	}

	void addOrderDetails(OrderDetails x) {
		orderdetails[dim] = x;
		dim++;
	}

	void afisareOrderDetails() {
		for (int i = 0; i < dim; i++) {
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			orderdetails[i].descriereOrderDetails();
		}
	}

	string toSave() {
		string r = "";
		for (int i = 0; i < dim; i++) {
			r += orderdetails[i].toSave();
			if (i != dim - 1) {
				r += "\n";
			}
		}
		return r;
	}

	void saveFile() {
		ofstream f("orderdetails.txt");

		f << toSave();
	}

	void productFrequency(int f[]) {
		for (int i = 0; i < dim; i++) {
			f[orderdetails[i].getProductID()] += orderdetails[i].getQuantity();
		}
	}

};