#include "view-manager.h"

struct ViewLogin {
private:
	ControlUser controluser;
	User user;

	void login() {
		string email, password;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Introduceti email-ul :" << endl;
		cin >> email;
		cout << "Introduceti parola :" << endl;
		cin >> password;
		int i = controluser.findByLoginDetails(email, password);
		if (i == -2) {
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "Parola este gresita." << endl;
		}
		else if (i == -1) {
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "Nu exista un cont cu acest email." << endl;
		}
		else {
			user = controluser.getUser(i);
			if (user.getStatus() != "Banned" || user.getType() == "Manager") {
				if (user.getType() == "Manager") {
					ViewManager view(user);
					view.play();
				}
				else if (user.getType() == "Client") {
					ViewClient view(user);
					view.play();
				}
			}
			else {
				cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
				cout << "Nu aveti accesul de a va loga." << endl;
			}
			
		}
	}

	void newAccount() {
		string email, password, first_name, last_name, full_name, country, phone_number, type;
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
		cout << "Introduceti email-ul :" << endl;
		cin >> email;
		cout << "Introduceti parola :" << endl;
		cin >> password;
		cout << "Introduceti prenumele :" << endl;
		cin >> first_name;
		cout << "Introduceti numele :" << endl;
		cin >> last_name;
		cout << "Introduceti tara :" << endl;
		cin >> country;
		cout << "Introduceti numarul de telefon :" << endl;
		cin >> phone_number;
		full_name = first_name + " " + last_name;
		if (controluser.findByEmail(email) != -1) {
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "Exista deja un cont pe acest email." << endl;
		}
		else {
			User x(controluser.idUnic(), email, password, full_name, country, phone_number, "Client", "Normal");
			controluser.addUser(x);
			controluser.saveFile();
			cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
			cout << "Ati creat contul cu succes!" << endl;
		}
	}

	void menu() {
		cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n" << endl;
		cout << "Introduceti : " << endl;
		cout << "- 1 pentru a va loga" << endl;
		cout << "- 2 pentru a va crea un cont" << endl;
	}

public:

	ViewLogin() {
		play();
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
				login();
				break;
			case 2:
				newAccount();
				break;
			default:
				break;
			}
		}
	}
};
