#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<string>
#include "admin.h"
void loginPanel();
void signupPanel();
void userLogin();
void adminLogin();
void userSignup();
void adminSignup();
void userPanel(person* u);
void adminPanel(admin* a);
int main(){
	try {
		while (true) {
			cout << endl;
			cout << "[1] Login" << endl;
			cout << "[2] Signup" << endl;
			cout << "[3] Exit" << endl;
			cout << "[#] ";
			int n;
			cin >> n;
			switch (n)
			{
			case 1:
				loginPanel();
				break;
			case 2:
				signupPanel();
				break;
			case 3:
				return 0;
			default:
				break;
			}
		}
	}
	catch (...) {
		cout << "Get Error!" << endl;
		return 0;
	}
}
void loginPanel() {
	cout << endl;
	while (true) {
		cout << "[1] User" << endl;
		cout << "[2] Admin" << endl;
		cout << "[3] Back" << endl;
		cout << "[#] ";
		int n;
		cin >> n;
		switch (n)
		{
		case 1:
			userLogin();
			return;
		case 2:
			adminLogin();
			return;
		case 3:
			return;
		default:
			break;
		}
	}
}
void signupPanel(){
	cout << endl;
	while (true) {
		cout << "[1] User" << endl;
		cout << "[2] Admin" << endl;
		cout << "[3] Back" << endl;
		cout << "[#] ";
		int n;
		cin >> n;
		switch (n)
		{
		case 1:
			userSignup();
			return;
		case 2:
			adminSignup();
			return;
		case 3:
			return;
		default:
			break;
		}
	}
}
void userLogin(){
	cout << endl;
	cout << "username: ";
	string username;
	cin >> ws >> username;
	cout << "password: ";
	string password;
	cin >> ws >> password;
	auto log = person::login(username, password);
	if (!dynamic_cast<admin*>(log.second)) {
		switch (log.first)
		{
		case::loginCode::WRONGUSER:
			cout << "username does not exist" << endl;
			break;
		case loginCode::WRONGPASS:
			cout << "Password is wrong" << endl;
			break;
		case loginCode::SUCCESS:
			cout << "Login successfully" << endl;
			userPanel(log.second);
			break;
		default:
			break;
		}
	}
	else {
		cout << "username dose not exist" << endl;
	}
}
void adminLogin(){
	cout << endl;
	cout << "username: ";
	string username;
	cin >> ws >> username;
	cout << "password: ";
	string password;
	cin >> ws >> password;
	auto log = person::login(username, password);
	if (dynamic_cast<admin*>(log.second)) {
		switch (log.first)
		{
		case::loginCode::WRONGUSER:
			cout << "username does not exist" << endl;
			break;
		case loginCode::WRONGPASS:
			cout << "Password is wrong" << endl;
			break;
		case loginCode::SUCCESS:
			cout << "Login successfully" << endl;
			adminPanel(dynamic_cast<admin*>(log.second));
			break;
		default:
			break;
		}
	}
	else {
		cout << "username dose not exist" << endl;
	}
}
void userSignup(){
	cout << endl;
	cout << "name(firstName lastName): ";
	string name;
	getline(cin>>ws, name);
	date birthDate;
	while (true) {
		try {
			cout << "birthDate(YYYY MM DD): ";
			int year, month, day;
			cin >> ws >> year >> month >> day;
			birthDate = date(year, month, day);
			break;
		}
		catch (dateException ex) {
			cout << ex.what() << endl;
		}
	}
	while (true) {
		try {
			cout << "username: ";
			string username;
			cin >> ws >> username;
			cout << "password: ";
			string password;
			cin >> ws >> password;
			new person(name, birthDate, username, password);
			break;
		}
		catch (personException ex) {
			cout << ex.what() << endl;
		}
	}
}
void adminSignup(){
	cout << endl;
	cout << "name(firstName lastName): ";
	string name;
	getline(cin >> ws, name);
	date birthDate;
	while (true) {
		try {
			cout << "birthDate(YYYY MM DD): ";
			int year, month, day;
			cin >> ws >> year >> month >> day;
			birthDate = date(year, month, day);
			break;
		}
		catch (dateException ex) {
			cout << ex.what() << endl;
		}
	}
	while (true) {
		try {
			cout << "username: ";
			string username;
			cin >> ws >> username;
			cout << "password: ";
			string password;
			cin >> ws >> password;
			new admin(name, birthDate, username, password);
			break;
		}
		catch (personException ex) {
			cout << ex.what() << endl;
		}
	}
}
void userPanel(person* u){
	cout << endl;
	cout << "hello " << u->getName() << endl;
	while (true) {
		cout << "[1] Check status of bank accounts" << endl;
		cout << "[2] Transfer money between bank accounts" << endl;
		cout << "[3] Create new account" << endl;
		cout << "[4] Check times of enter and exit to account" << endl;
		cout << "[5] account setting" << endl;
		cout << "[6] Logout" << endl;
		cout << "[#] ";
		int n;
		cin >> n;
		if (n == 1) {
			auto accounts = u->getAccounts();
			if (accounts.empty()) {
				cout << "You dont have any accounts" << endl;
				continue;
			}
			cout << "------------------------------------------------------------" << endl;
			for (auto a : accounts) {
				cout << "ID: " << a->getId() << endl;
				cout << "Type: ";
				switch (a->getType())
				{
				case mode::SHORTTERM:
					cout << "Short term" << endl;
					break;
				case mode::LONGTERM:
					cout << "Long term" << endl;
					break;
				case mode::GOODLOAN:
					cout << "Good loan" << endl;
					break;
				default:
					cout << "Undefined" << endl;
					break;
				}
				cout << "Status: ";
				switch (a->getSituation())
				{
				case status::ONLINE:
					cout << "Online" << endl;
					break;
				case status::BLOCK:
					cout << "Block" << endl;
					break;
				case status::EXPIRE:
					cout << "Expire" << endl;
					break;
				case status::NOTVERIFY:
					cout << "Not verify" << endl;
					break;
				default:
					cout << "Undefined" << endl;
					break;
				}
				cout << "Balance: " << a->getBalance() << endl;
				cout << "Creation date: ";
				a->getCEDate().first.print(style::YYYY_MM_DD);
				cout << "Expire date: ";
				a->getCEDate().second.print(style::YYYY_MM_DD);
				cout << "------------------------------------------------------------" << endl;
			}
		}
		else if (n == 2) {
			string first, second;
			cout << "First account ID: ";
			cin >> first;
			cout << "Second account ID: ";
			cin >> second;
			double balance;
			cout << "Balance: ";
			cin >> balance;
			bool ans= u->moveMoney(first, second, balance);
			if (ans) cout << "Money transfer success" << endl;
			else cout << "Money transfer faild" << endl;
		}
		else if (n == 3) {
			while (true) {
				try {
					cout << "mode: " << endl;
					cout << "[1] Short term" << endl;
					cout << "[2] Long term" << endl;
					cout << "[3] Good loan" << endl;
					int m;
					do {
						cout << "[#] ";
						cin >> m;
					} while (m <= 0 || m > 3);
					mode type=mode::SHORTTERM;
					switch (m)
					{
					case 1: type = mode::SHORTTERM; break;
					case 2: type: mode::LONGTERM; break;
					case 3: type = mode::GOODLOAN; break;
					}
					cout << "balance: ";
					double balance;
					cin >> balance;
					account* acc = u->craeteNewAccount(type, balance);
					cout << "account ID: " << acc->getId() << endl;
					break;
				}
				catch (personException ex) {
					cout << ex.what() << endl;
				}
				catch (accountException ex) {
					cout << ex.what() << endl;
				}
			}
		}
		else if (n == 4) {
			cout << "------------------------------------------------------------" << endl;
			for (int i = 0; i < u->getTimeOfADs().size() - 1; i++) {
				cout << "Enter Time: ";
				u->getTimeOfADs()[i].first.print(style::YY_MM_DD_HH_MM_SS);
				cout << "Exit Time: ";
				u->getTimeOfADs()[i].second.print(style::YY_MM_DD_HH_MM_SS);
				cout << "------------------------------------------------------------" << endl;
			}
			cout << "Enter Time: ";
			u->getTimeOfADs().back().first.print(style::YY_MM_DD_HH_MM_SS);
			cout << "Exit Time: Notyet" << endl;
			cout << "------------------------------------------------------------" << endl;
		}
		else if (n == 5) {
			while (true) {
				cout << "[1] Change name" << endl;
				cout << "[2] Change birthdate" << endl;
				cout << "[3] Change password" << endl;
				cout << "[4] Back" << endl;
				cout << "[#] ";
				int n;
				cin >> n;
				if (n == 1) {
					cout << "Your name: " << u->getName() <<endl;
					cout << "name(firstName lastName): ";
					string name;
					getline(cin >> ws, name);
					u->setName(name);
				}
				else if (n == 2) {
					cout << "Your birthdate: ";
					u->getBirthDate().print(style::YY_MM_DD);
					date birthDate;
					while (true) {
						try {
							cout << "birthDate(YYYY MM DD): ";
							int year, month, day;
							cin >> ws >> year >> month >> day;
							birthDate = date(year, month, day);
							break;
						}
						catch (dateException ex) {
							cout << ex.what() << endl;
						}
					}
					u->setBirthDate(birthDate);
				}
				else if (n == 3) {
					cout << "password: ";
					string password;
					cin >> ws >> password;
				}
				else if (n == 4) {
					break;
				}
			}
		}
		else if (n == 6) {
			u->logout();
			cout << "bye " << u->getName() << endl;
			break;
		}
	}
}
void adminPanel(admin* u){
	cout << endl;
	cout << "hello " << u->getName() << endl;
	while (true) {
		cout << "[1] Check status of bank accounts" << endl;
		cout << "[2] Transfer money between bank accounts" << endl;
		cout << "[3] Create new account" << endl;
		cout << "[4] Check times of enter and exit to account" << endl;
		cout << "[5] account setting" << endl;
		cout << "[6] Admin manager" << endl;
		cout << "[7] Logout" << endl;
		cout << "[#] ";
		int n;
		cin >> n;
		if (n == 1) {
			auto accounts = u->getAccounts();
			if (accounts.empty()) {
				cout << "You dont have any accounts" << endl;
				continue;
			}
			cout << "------------------------------------------------------------" << endl;
			for (auto a : accounts) {
				cout << "ID: " << a->getId() << endl;
				cout << "Type: ";
				switch (a->getType())
				{
				case mode::SHORTTERM:
					cout << "Short term" << endl;
					break;
				case mode::LONGTERM:
					cout << "Long term" << endl;
					break;
				case mode::GOODLOAN:
					cout << "Good loan" << endl;
					break;
				default:
					cout << "Undefined" << endl;
					break;
				}
				cout << "Status: ";
				switch (a->getSituation())
				{
				case status::ONLINE:
					cout << "Online" << endl;
					break;
				case status::BLOCK:
					cout << "Block" << endl;
					break;
				case status::EXPIRE:
					cout << "Expire" << endl;
					break;
				case status::NOTVERIFY:
					cout << "Not verify" << endl;
					break;
				default:
					cout << "Undefined" << endl;
					break;
				}
				cout << "Balance: " << a->getBalance() << endl;
				cout << "Creation date: ";
				a->getCEDate().first.print(style::YYYY_MM_DD);
				cout << "Expire date: ";
				a->getCEDate().second.print(style::YYYY_MM_DD);
				cout << "------------------------------------------------------------" << endl;
			}
		}
		else if (n == 2) {
			string first, second;
			cout << "First account ID: ";
			cin >> first;
			cout << "Second account ID: ";
			cin >> second;
			double balance;
			cout << "Balance: ";
			cin >> balance;
			bool ans = u->moveMoney(first, second, balance);
			if (ans) cout << "Money transfer success" << endl;
			else cout << "Money transfer faild" << endl;
		}
		else if (n == 3) {
			while (true) {
				try {
					cout << "mode: " << endl;
					cout << "[1] Short term" << endl;
					cout << "[2] Long term" << endl;
					cout << "[3] Good loan" << endl;
					int m;
					do {
						cout << "[#] ";
						cin >> m;
					} while (m <= 0 || m > 3);
					mode type = mode::SHORTTERM;
					switch (m)
					{
					case 1: type = mode::SHORTTERM; break;
					case 2: type: mode::LONGTERM; break;
					case 3: type = mode::GOODLOAN; break;
					}
					cout << "balance: ";
					double balance;
					cin >> balance;
					account* acc = u->craeteNewAccount(type, balance);
					cout << "account ID: " << acc->getId() << endl;
					acc->setSituation(status::ONLINE);
					break;
				}
				catch (personException ex) {
					cout << ex.what() << endl;
				}
				catch (accountException ex) {
					cout << ex.what() << endl;
				}
			}
		}
		else if (n == 4) {
			cout << "------------------------------------------------------------" << endl;
			for (int i = 0; i < u->getTimeOfADs().size() - 1; i++) {
				cout << "Enter Time: ";
				u->getTimeOfADs()[i].first.print(style::YY_MM_DD_HH_MM_SS);
				cout << "Exit Time: ";
				u->getTimeOfADs()[i].second.print(style::YY_MM_DD_HH_MM_SS);
				cout << "------------------------------------------------------------" << endl;
			}
			cout << "Enter Time: ";
			u->getTimeOfADs().back().first.print(style::YY_MM_DD_HH_MM_SS);
			cout << "Exit Time: Notyet" << endl;
			cout << "------------------------------------------------------------" << endl;
		}
		else if (n == 5) {
			while (true) {
				cout << "[1] Change name" << endl;
				cout << "[2] Change birthdate" << endl;
				cout << "[3] Change password" << endl;
				cout << "[4] Back" << endl;
				cout << "[#] ";
				int n;
				cin >> n;
				if (n == 1) {
					cout << "Your name: " << u->getName() << endl;
					cout << "name(firstName lastName): ";
					string name;
					getline(cin >> ws, name);
					u->setName(name);
				}
				else if (n == 2) {
					cout << "Your birthdate: ";
					u->getBirthDate().print(style::YY_MM_DD);
					date birthDate;
					while (true) {
						try {
							cout << "birthDate(YYYY MM DD): ";
							int year, month, day;
							cin >> ws >> year >> month >> day;
							birthDate = date(year, month, day);
							break;
						}
						catch (dateException ex) {
							cout << ex.what() << endl;
						}
					}
					u->setBirthDate(birthDate);
				}
				else if (n == 3) {
					cout << "password: ";
					string password;
					cin >> ws >> password;
				}
				else if (n == 4) {
					break;
				}
			}
		}
		else if (n == 6) {
			while (true) {
				cout << "[1] See all users" << endl;
				cout << "[2] See Application list" << endl;
				cout << "[3] Change My bank accounts" << endl;
				cout << "[4] Back" << endl;
				cout << "[#] ";
				int n;
				cin >> n;
			}
		}
		else if (n == 7) {
			u->logout();
			cout << "bye " << u->getName() << endl;
			break;
		}
	}
}
