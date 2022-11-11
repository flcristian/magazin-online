#include "controller-order-details.h"

struct ViewClient {
private:
	ControlUser controluser;
	ControlOrderDetails controlorderdetails;
	ControlOrder controlorder;
	ControlProduct controlproduct;
	User client;

	// Basket:
	Order order;

	void afisareProduse() {
		if (controlproduct.getDim() != 0) {
			controlproduct.afisareProduseClient();
		}
		else {
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "Nu exista produse." << endl;
		}
		
	}

	// MODIFICARE CONT :

	void modificareNume() {
		string first_name, last_name, full_name;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Introduceti prenumele :" << endl;
		cin >> first_name;
		cout << "Introduceti numele :" << endl;
		cin >> last_name;
		full_name = first_name + " " + last_name;
		controluser.modifyName(full_name, controluser.getIndice(client.getID()));
		controluser.saveFile();
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "V-ati schimbat numele cu succes!" << endl;
	}

	void modificareNumar() {
		string number;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Introduceti numarul de telefon :" << endl;
		cin >> number;
		controluser.modifyNumber(number, controluser.getIndice(client.getID()));
		controluser.saveFile();
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "V-ati schimbat numarul de telefon cu succes!" << endl;
	}

	void modificareTara() {
		string country;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Introduceti tara :" << endl;
		cin >> country;
		controluser.modifyCountry(country, controluser.getIndice(client.getID()));
		controluser.saveFile();
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "V-ati schimbat tara cu succes!" << endl;
	}

	void modificareParola() {
		string old_password, password;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Introduceti parola veche :" << endl;
		cin >> old_password;
		int i = controluser.findByLoginDetails(client.getEmail(), old_password);
		if (i == controluser.getIndice(client.getID())) {
			cout << "Introduceti parola noua :" << endl;
			cin >> password;
			controluser.modifyPassword(password, i);
			controluser.saveFile();
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "V-ati schimbat parola cu succes!" << endl;
		}
		else {
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "Ati gresit parola!" << endl;
		}
	}

	void modificareEmail() {
		string email;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Introduceti email-ul :" << endl;
		cin >> email;
		if (controluser.findByEmail(email) == -1) {
			controlorder.changeEmail(client.getEmail(), email);
			controluser.modifyEmail(email, controluser.getIndice(client.getID()));
			controluser.saveFile();
			controlorder.saveFile();
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "V-ati schimbat email-ul cu succes!" << endl;
		}
		else {
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "Email-ul este deja utilizat!" << endl;
		}
	}

	void modificareCont() {
		bool running = true;
		int l;

		while (running) {
			meniuModificareCont();
			string ax;
			cin >> ax;
			l = stoi(ax);

			switch (l)
			{
			case 1:
				modificareNume();
				break;
			case 2:
				modificareNumar();
				break;
			case 3:
				modificareTara();
				break;
			case 4:
				modificareParola();
				break;
			case 5:
				modificareEmail();
				break;
			case 6:
				running = false;
				break;
			default:
				break;
			}
		}
	}

	// PRODUSE + COS :

	void adaugareCosProdus() {
		string productName;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Introduceti numele produsului :" << endl;
		cin >> productName;

		int i = controlproduct.findByName(productName);
		if (i != -1) {
			string cantitate;
			cout << "Introduceti cantitatea :" << endl;
			cin >> cantitate;
			if (stoi(cantitate) > 0) {
				Product produs = controlproduct.getProduct(i);
				if (stoi(cantitate) <= produs.getStock()) {
					OrderDetails x(controlorderdetails.idUnic(), order.getID(), produs.getID(), produs.getPrice() * stoi(cantitate), stoi(cantitate), "Preparing");
					controlorderdetails.addOrderDetails(x);
					order.setAmmount(order.getAmmount() + produs.getPrice() * stoi(cantitate));
					controlproduct.updateStock(i, stoi(cantitate));
					cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
					cout << "Ati adaugat produsul/le cu succes." << endl;
				}
				else {
					cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
					cout << "Cantitatea de produse nu mai este in stock." << endl;
				}
			}
			else {
				cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
				cout << "Produsul nu a fost adaugat deoarece valoarea este nula sau negativa." << endl;
			}
		}
		else {
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "Acest produs nu exista." << endl;
		}
	}

	void afisareCos() {
		OrderDetails orderdetails[100];
		int n;
		controlorderdetails.produseCos(order.getID(), orderdetails, n);
		if (n != 0) {
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			for (int i = 0; i < n; i++) {
				Product produs = controlproduct.getByID(orderdetails[i].getProductID());			
				cout << produs.getName() << " : " << produs.getPrice() << " x " << orderdetails[i].getQuantity() << " = " << orderdetails[i].getPrice() << endl;
				
			}
			cout << "\nTotal : " << order.getAmmount() << endl;
		}
		else {
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "Cosul este gol." << endl;
		}
		
	}

	void modificareCantitateProdus() {
		string numeProdus;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Introduceti numele obiectului :" << endl;
		cin >> numeProdus;
		
		int i = controlproduct.findByName(numeProdus);
		if (i != -1) {
			Product produs = controlproduct.getProduct(i);
			int j = controlorderdetails.findByProductAndOrder(produs.getID(), order.getID());
			if (j != -1) {
				string modificare;
				cout << "Introduceti cu cat doriti sa modificati cantitatea :" << endl;
				cin >> modificare;
				OrderDetails detalii = controlorderdetails.getOrderDetails(j);
				if (stoi(modificare) <= detalii.getQuantity() * -1) {
					controlproduct.updateStock(i, detalii.getQuantity() * -1);
					controlorderdetails.removeOrderDetails(j);
					order.setAmmount(order.getAmmount() - produs.getPrice() * detalii.getQuantity());
					cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
					cout << "Produsul a fost sters din cos." << endl;
				}
				else if (stoi(modificare) <= produs.getStock()) {
					controlorderdetails.updateOrderDetails(j, detalii.getQuantity() + stoi(modificare), (detalii.getQuantity() + stoi(modificare)) * produs.getPrice());
					controlproduct.updateStock(i, stoi(modificare));
					order.setAmmount(order.getAmmount() + produs.getPrice() * stoi(modificare));
					cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
					cout << "Cantitatea noua : " << detalii.getQuantity() + stoi(modificare) << endl;
				}
				else {
					cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
					cout << "Nu exista stock suficient." << endl;
				}
			}
			else {
				cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
				cout << "Produsul nu este in cos." << endl;
			}
		}
		else {
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "Produsul nu exista." << endl;
		}
	}

	void eliminareProdusCos() {
		string numeProdus;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Introduceti numele obiectului :" << endl;
		cin >> numeProdus;

		int i = controlproduct.findByName(numeProdus);
		if (i != -1) {
			Product produs = controlproduct.getProduct(i);
			int j = controlorderdetails.findByProductAndOrder(produs.getID(), order.getID());
			if (j != -1) {
				OrderDetails detalii = controlorderdetails.getOrderDetails(j);
				controlproduct.updateStock(i, detalii.getQuantity() * -1);
				controlorderdetails.removeOrderDetails(j);
				order.setAmmount(order.getAmmount() - produs.getPrice() * detalii.getQuantity());
				cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
				cout << "Produsul a fost sters din cos." << endl;
			}
			else {
				cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
				cout << "Produsul nu este in cos." << endl;
			}
		}
		else {
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "Produsul nu exista." << endl;
		}
	}

	void golireCos() {
		int order_detail_ids[100], product_ids[100];
		int n = 0;
		controlorderdetails.getIDsFromOrderIDWithProductIDs(order.getID(), order_detail_ids, product_ids, n);
		for (int i = 0; i < n; i++) {
			int j = controlorderdetails.getIndice(order_detail_ids[i]);
			OrderDetails detalii = controlorderdetails.getOrderDetails(j);
			int k = controlproduct.getIndice(product_ids[i]);
			controlproduct.updateStock(k, detalii.getQuantity() * -1);
			controlorderdetails.removeOrderDetails(j);
		}
		order.setAmmount(0);
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Gosul a fost golit." << endl;
	}

	void modificareCos() {
		bool running = true;
		int y;

		while (running) {
			meniuModificareCos();
			string a;
			cin >> a;
			y = stoi(a);

			switch (y)
			{
			case 1:
				modificareCantitateProdus();
				break;
			case 2:
				eliminareProdusCos();
				break;
			case 3:
				golireCos();
				break;
			case 4:
				running = false;
				break;
			default:
				break;
			}
		}
	}

	// COMANDA :

	void trimiteComanda() {
		order.setOrderStatus("Preparing");
		controlorderdetails.modifyOrderStatus(order.getID(), "Preparing");
		controlorderdetails.saveFile();
		controlorder.addOrder(order);
		cout << controlorder.getDim() << " " << controlorderdetails.getDim() << endl;
		controlorder.saveFile();
		controlproduct.saveFile();
		order.setID(controlorder.idUnic());
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Comanda dumneavoastra a fost trimisa si este in curs de pregatire!" << endl;
	}

	void anulareComanda() {
		int order_detail_ids[100], product_ids[100];
		int n = 0;
		controlorderdetails.getIDsFromOrderIDWithProductIDs(order.getID(), order_detail_ids, product_ids, n);
		for (int i = 0; i < n; i++) {
			int j = controlorderdetails.getIndice(order_detail_ids[i]);
			OrderDetails detalii = controlorderdetails.getOrderDetails(j);
			int k = controlproduct.getIndice(product_ids[i]);
			controlproduct.updateStock(k, detalii.getQuantity() * -1);
			controlorderdetails.removeOrderDetails(j);
		}
		order.setAmmount(0);
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Comanda dumneavoastra a fost anulata!" << endl;
	}

	// MENIURI :
	
	void menu() {
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n" << endl;
		cout << "Introduceti : " << endl;
		cout << "- 1 pentru a vedea produsele" << endl;
		cout << "- 2 pentru a adauga un produs in cos" << endl;
		cout << "- 3 pentru a afisa continutul cosului" << endl;
		cout << "- 4 pentru a modifica cosul" << endl;
		cout << "- 5 pentru a trimite comanda" << endl;
		cout << "- 6 pentru a anula comanda" << endl;
		cout << "- 7 pentru a va modifica contul" << endl;
		cout << "- 8 pentru a va deloga" << endl;
	}

	void meniuModificareCont() {
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n" << endl;
		cout << "Introduceti : " << endl;
		cout << "- 1 pentru a va schimba numele" << endl;
		cout << "- 2 pentru a va schimba numarul de telefon" << endl;
		cout << "- 4 pentru a va schimba tara" << endl;
		cout << "- 4 pentru a va schimba parola" << endl;
		cout << "- 5 pentru a va schimba email-ul" << endl;
		cout << "- 6 pentru a iesi" << endl;
	}

	void meniuModificareCos() {
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n" << endl;
		cout << "Introduceti : " << endl;
		cout << "- 1 pentru a modifica cantitatea unui produs" << endl;
		cout << "- 2 pentru a scoate un obiect din cos" << endl;
		cout << "- 3 pentru a goli cosul" << endl;
		cout << "- 4 pentru a va opri din a modifica cosul" << endl;
	}

public:

	ViewClient() {
		User x(1, "geogabi@gmail.com", "Parola12", "George Gabriel", "Romania", "0717219240", "Client", "Normal");
		this->client = x;

		order.setID(controlorder.idUnic());
		order.setCustomerID(client.getID());
		order.setAmmount(0);
		order.setOrderEmail(client.getEmail());
		order.setOrderStatus("Uninitialized");
	}

	ViewClient(User x) {
		this->client = x;

		order.setID(controlorder.idUnic());
		order.setCustomerID(client.getID());
		order.setAmmount(0);
		order.setOrderEmail(client.getEmail());
		order.setOrderStatus("Uninitialized");
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
				adaugareCosProdus();
				break;
			case 3:
				afisareCos();
				break;
			case 4:
				modificareCos();
				break;
			case 5:
				trimiteComanda();
				break;
			case 6:
				anulareComanda();
				break;
			case 7:
				modificareCont();
				break;
			case 8:
				running = false;
				break;
			default:
				break;
			}
		}
	}

};