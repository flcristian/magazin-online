#include "view-client.h"

struct ViewManager {
private:
	ControlUser controluser;
	ControlProduct controlproduct;
	ControlOrder controlorder;
	ControlOrderDetails controlorderdetails;
	User user;

	void afisareProduse() {
		if (controlproduct.getDim() != 0) {
			controlproduct.afisareProduseClient();
		}
		else {
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "Nu exista produse." << endl;
		}

	}

	void afisareBannedUserEmails() {
		User users[100];
		int dim;
		controluser.getAllUsers(users, dim);

		User banned[100];
		int n = 0;
		for (int i = 0; i < dim; i++) {
			if (users[i].getStatus() == "Banned") {
				banned[n] = users[i];
				n++;
			}
		}

		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Banned users :" << endl;
		for (int i = 0; i < n; i++) {
			cout << banned[i].getFullName() << " - " << banned[i].getEmail() << endl;
		}
	}

	void afisareManagerEmails() {
		User users[100];
		int dim;
		controluser.getAllUsers(users, dim);

		User managers[100];
		int n = 0;
		for (int i = 0; i < dim; i++) {
			if (users[i].getType() == "Manager") {
				managers[n] = users[i];
				n++;
			}
		}

		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Managers :" << endl;
		for (int i = 0; i < n; i++) {
			cout << managers[i].getFullName() << " - " << managers[i].getEmail() << endl;
		}
	}

	// MODIFICARE USER :

	void banUser() {
		string email;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Introduceti email-ul clientului :" << endl;
		cin >> email;
		int i = controluser.findByEmail(email);
		if (i != -1) {
			User client = controluser.getUser(i);
			if (client.getType() != "Manager") {
				if (client.getStatus() != "Banned") {
					controluser.banUser(i);
					int n, d;
					int ids[100], productIDs[100], quantities[100];
					controlorder.banUser(ids, n, client.getID());
					controlorderdetails.banUser(ids, n, productIDs, quantities, d);
					for (int k = 0; k < d; k++) {
						controlproduct.updateStock(controlproduct.getIndice(productIDs[k]), quantities[k] * -1);
					}
					controluser.saveFile();
					controlorder.saveFile();
					controlorderdetails.saveFile();
					controlproduct.saveFile();
					cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
					cout << "Ati blocat cu succes accesul acestui client." << endl;
					cout << "Toate comenzile sale au fost anulate, iar stock-ul updatat." << endl;
				}
				else {
					cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
					cout << "Acest client este deja blocat." << endl;
				}
			}
			else {
				cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
				cout << "Nu puteti bloca un alt administrator!" << endl;
			}
		}
		else {
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "Acest client nu exista." << endl;
		}
	}

	void unbanUser() {
		string email;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Introduceti email-ul clientului :" << endl;
		cin >> email;
		int i = controluser.findByEmail(email);
		if (i != -1) {
			User client = controluser.getUser(i);
			if (client.getStatus() == "Banned") {
				controluser.unbanUser(i);
				controluser.saveFile();
				cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
				cout << "Ati deblocat cu succes accesul acestui client." << endl;
			}
			else {
				cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
				cout << "Acest client nu este blocat." << endl;
			}
		}
		else {
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "Acest client nu exista." << endl;
		}
	}

	void removeUser() {
		string email;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Introduceti email-ul clientului :" << endl;
		cin >> email;
		int i = controluser.findByEmail(email);
		if (i != -1) {
			User client = controluser.getUser(i);
			if (client.getType() != "Manager") {
				controluser.removeUser(i);
				int n, d;
				int ids[100], productIDs[100], quantities[100];
				controlorder.banUser(ids, n, client.getID());
				controlorderdetails.banUser(ids, n, productIDs, quantities, d);
				for (int k = 0; k < d; k++) {
					controlproduct.updateStock(controlproduct.getIndice(productIDs[k]), quantities[k] * -1);
				}
				controluser.saveFile();
				controlorder.saveFile();
				controlorderdetails.saveFile();
				controlproduct.saveFile();
				cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
				cout << "Ati sters cu succes acest client." << endl;
				cout << "Toate comenzile sale au fost anulate, iar stock-ul updatat." << endl;
			}
			else {
				cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
				cout << "Nu puteti sterge contul altui administrator!" << endl;
			}
		}
		else {
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "Acest client nu exista." << endl;
		}
	}

	void addManager() {
		string email;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Introduceti email-ul user-ului :" << endl;
		cin >> email;
		int i = controluser.findByEmail(email);
		if (i != -1) {
			User client = controluser.getUser(i);
			if (client.getType() != "Manager") {
				controluser.addManager(i);
				controluser.saveFile();
				cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
				cout << "Ati atribuit functia de administrator acestui user!" << endl;
			}
			else {
				cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
				cout << "Acest user este deja un administrator." << endl;
			}
		}
		else {
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "Acest user nu exista." << endl;
		}
	}

	// MODIFICARE PRODUS : 

	void addProduct() {
		string nume, pret, categorie, stock;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Introduceti numele produsului :" << endl;
		cin >> nume;
		cout << "Introduceti pretul produsului :" << endl;
		cin >> pret;
		cout << "Introduceti categoria produsului :" << endl;
		cin >> categorie;
		cout << "Introduceti cantitatea din stock a produsului :" << endl;
		cin >> stock;
		Product produs(controlproduct.idUnic(), nume, stoi(pret), categorie, stoi(stock));
		controlproduct.addProduct(produs);
		controlproduct.saveFile();
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Ati adaugat '" << nume << "' cu succes!" << endl;
	}

	void seeProductDetails(int i) {
		controlproduct.seeDetails(i);
	}

	void modificareIntregProdus(int i) {
		Product x = controlproduct.getProduct(i);
		string nume, pret, categorie, stock;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Introduceti numele produsului :" << endl;
		cin >> nume;
		cout << "Introduceti pretul produsului :" << endl;
		cin >> pret;
		cout << "Introduceti categoria produsului :" << endl;
		cin >> categorie;
		cout << "Introduceti cantitatea din stock a produsului :" << endl;
		cin >> stock;
		Product produs(x.getID(), nume, stoi(pret), categorie, stoi(stock));
		controlproduct.changeProduct(i, produs);
		controlproduct.saveFile();
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Ati modificat cu succes produsul!" << endl;
	}

	void modifyName(int i) {
		string name;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Introduceti numele produsului :" << endl;
		cin >> name;
		controlproduct.changeProductName(i, name);
		controlproduct.saveFile();
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Ati modificat numele produsului cu succes!" << endl;
	}

	void modifyPrice(int i) {
		string pret;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Introduceti pretul produsului :" << endl;
		cin >> pret;
		controlproduct.changeProductPrice(i, stoi(pret));
		controlproduct.saveFile();
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Ati modificat pretul produsului cu succes!" << endl;
	}

	void modifyCategory(int i) {
		string categorie;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Introduceti categoria produsului :" << endl;
		cin >> categorie;
		controlproduct.changeProductCategory(i, categorie);
		controlproduct.saveFile();
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Ati modificat categoria produsului cu succes!" << endl;
	}

	void modifyStock(int i) {
		string stock;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Introduceti cantitatea din stock a produsului :" << endl;
		cin >> stock;
		controlproduct.changeProductStock(i, stoi(stock));
		controlproduct.saveFile();
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Ati modificat cantitatea din stock a produsului cu succes!" << endl;
	}

	void removeProduct(int i) {
		controlproduct.removeProduct(i);
		controlproduct.saveFile();
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Ati sters produsul cu succes!" << endl;
	}

	// STATISTICI :

	void seeMostPopularProduct() {
		int frequency[100]{};
		controlorderdetails.productFrequency(frequency);
		Product products[100];
		int dim;
		controlproduct.getAllProducts(products, dim);

		bool flag = true;
		do {
			flag = true;
			for (int i = 0; i < dim - 1; i++) {
				if (frequency[products[i].getID()] < frequency[products[i + 1].getID()]) {
					Product r = products[i];
					products[i] = products[i + 1];
					products[i + 1] = r;
					flag = false;
				}
			}
		} while (flag == false);

		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Cel mai popular produs este " << products[0].getName() << endl;
		cout << "Numar comandat : " << frequency[products[0].getID()] << endl;
	}

	void seeSortedByPopularity() {
		int frequency[100]{};
		controlorderdetails.productFrequency(frequency);
		Product products[100];
		int dim;
		controlproduct.getAllProducts(products, dim);

		bool flag = true;
		do {
			flag = true;
			for (int i = 0; i < dim - 1; i++) {
				if (frequency[products[i].getID()] < frequency[products[i + 1].getID()]) {
					Product r = products[i];
					products[i] = products[i + 1];
					products[i + 1] = r;
					flag = false;
				}
			}
		} while (flag == false);

		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		int j = dim;
		for (int i = 0; i < dim && frequency[products[i].getID()] > 0; i++, j--) {
			cout << products[i].getName() << " - " << frequency[products[i].getID()] << endl;
		}
		cout << "Restul de " << j << " produse nu au fost comandate." << endl;
	}

	void seeBestActivityClient() {
		int f[100]{};
		controlorder.frecventaOrders(f);
		User u[100];
		int dim = 0;
		controluser.getAllUsers(u, dim);
		bool flag = true;
		do {
			flag = true;
			for (int i = 0; i < dim - 1; i++) {
				if (f[u[i].getID()] > f[u[i+1].getID()]){
					User aux = u[i];
					u[i] = u[i + 1];
					u[i + 1] = aux;
					flag = false;
				}
			}
		} while (flag == false);

		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Cel mai activ user este : " << u[dim-1].getEmail() << endl;
		cout << "Numarul de comenzi : " << f[u[dim-1].getID()] << endl;
	}

	void seeBestClient() {
		int ammounts[100]{};
		controlorder.getAmmountsSpent(ammounts);
		int dim;
		User users[100];
		controluser.getAllUsers(users, dim);

		bool flag = true;
		do {
			flag = true;
			for (int i = 0; i < dim - 1; i++) {
				if (ammounts[users[i].getID()] < ammounts[users[i + 1].getID()]) {
					User r = users[i];
					users[i] = users[i + 1];
					users[i + 1] = r;
					flag = false;
				}
			}
		} while (flag == false);

		int i = 0;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Cel mai bun client este " << users[0].getFullName() << endl;
		cout << "Email : " << users[0].getEmail() << endl;
		cout << "Suma cheltuita : " << ammounts[users[i].getID()] << endl;
	}

	void seeSortedByAmmountSpent() {
		int ammounts[100]{};
		controlorder.getAmmountsSpent(ammounts);
		User users[100];
		int dim;
		controluser.getAllUsers(users, dim);

		bool flag = true;
		do {
			flag = true;
			for (int i = 0; i < dim - 1; i++) {
				if (ammounts[users[i].getID()] < ammounts[users[i + 1].getID()]) {
					User r = users[i];
					users[i] = users[i + 1];
					users[i + 1] = r;
					flag = false;
				}
			}
		} while (flag == false);

		int j = dim;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		for (int i = 0; i < dim && ammounts[users[i].getID()] > 0; i++, j--) {
			cout << users[i].getFullName() << " - " << users[i].getEmail() << " - " << ammounts[users[i].getID()] << endl;
		}
		cout << "Restul de " << j << " persoane nu au cheltuit nimic." << endl;
	}

	// MENIURI :

	void menu() {
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n" << endl;
		cout << "Introduceti : " << endl;
		cout << "- 1 pentru a vedea produsele" << endl;
		cout << "- 2 pentru a adauga un produs" << endl;
		cout << "- 3 pentru a modifica un produs" << endl;
		cout << "- 4 pentru a vedea statisticile" << endl;
		cout << "- 5 pentru a bloca un client" << endl;
		cout << "- 6 pentru a debloca un client" << endl;
		cout << "- 7 pentru a sterge un client" << endl;
		cout << "- 8 pentru a afisa clientii blocati" << endl;
		cout << "- 9 pentru a afisa administratorii" << endl;
		cout << "- 10 pentru a adauga functia de administrator unui user" << endl;
		cout << "- 20 pentru a va deloga" << endl;
	}

	void modifyProduct() {
		string numeProdus;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Introduceti numele produsului :" << endl;
		cin >> numeProdus;
		int i = controlproduct.findByName(numeProdus);
		if (i != -1) {
			bool running = true;
			int y;

			while (running) {
				menuModifyProduct();
				string ay;
				cin >> ay;
				y = stoi(ay);
				
				switch (y)
				{
				case 1:
					seeProductDetails(i);
					break;
				case 2:
					modificareIntregProdus(i);
					break;
				case 3:
					modifyName(i);
					break;
				case 4:
					modifyPrice(i);
					break;
				case 5:
					modifyCategory(i);
					break;
				case 6:
					modifyStock(i);
					break;
				case 7:
					removeProduct(i);
					break;
				case 8:
					running = false;
					break;
				default:
					break;
				}
			}
		}
		else {
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "Acest produs nu exista." << endl;
		}

	}

	void menuModifyProduct() {
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n" << endl;
		cout << "Introduceti : " << endl;
		cout << "- 1 pentru a vedea detaliile produsului" << endl;
		cout << "- 2 pentru a modifica toate proprietatiile produsului" << endl;
		cout << "- 3 pentru a modifica numele produsului" << endl;
		cout << "- 4 pentru a modifica pretul produsului" << endl;
		cout << "- 5 pentru a modifica categoria produsului" << endl;
		cout << "- 6 pentru a modifica cantitatea din stock a produslui" << endl;
		cout << "- 7 pentru a sterge produsul" << endl;
		cout << "- 8 pentru a va opri din a modifica produsul" << endl;
	}

	void statistics() {
		bool running = true;
		int z;

		while (running) {
			menuStatistics();
			string az;
			cin >> az;
			z = stoi(az);

			switch (z)
			{
			case 1:
				seeMostPopularProduct();
				break;
			case 2:
				seeSortedByPopularity();
				break;
			case 3:
				seeBestClient();
				break;
			case 4:
				seeSortedByAmmountSpent();
				break;
			case 5:
				seeBestActivityClient();
				break;
			case 6:
				running = false;
				break;
			default:
				break;
			}																												
		}
	}

	void menuStatistics() {
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n" << endl;
		cout << "Introduceti : " << endl;
		cout << "- 1 pentru a vedea cel mai cumparat produs" << endl;
		cout << "- 2 pentru a vedea toate produsele sortate dupa popularitate" << endl;
		cout << "- 3 pentru a vedea cel mai fidel client" << endl;
		cout << "- 4 pentru a vedea totii clientii sortati dupa cantitatea cumparata" << endl;
		cout << "- 5 pentru a vedea clientul cu cea mai buna activitate" << endl;
		cout << "- 6 pentru a iesi" << endl;
	}

public:

	ViewManager() {
		User x(11, "geomanager@gmail.com", "Parola13", "George Gabriel", "Romania", "0712849121", "Manager", "Normal");

		this->user = x;
	}

	ViewManager(User x) {
		this->user = x;
	}

	void play() {
		bool running = true;
		int p;

		while (running) {
			menu();
			string al;
			cin >> al;
			p = stoi(al);

			switch (p)
			{
			case 1:
				afisareProduse();
				break;
			case 2:
				addProduct();
				break;
			case 3:
				modifyProduct();
				break;
			case 4:
				statistics();
				break;
			case 5:
				banUser();
				break;
			case 6:
				unbanUser();
				break;
			case 7:
				removeUser();
				break;
			case 8:
				afisareBannedUserEmails();
				break;
			case 9:
				afisareManagerEmails();
				break;
			case 10:
				addManager();
				break;
			case 20:
				running = false;
				break;
			default:
				break;
			}
 		}
	}
};