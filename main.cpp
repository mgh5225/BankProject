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
void createAccount(person* p);
void accountSetting(person* p);
void transferMoney(person* p);
void bankAccountSetting(person* p,account* a);
void userPanel(person* u);
void adminPanel(admin* a);
int main(){
	try {
		admin::readFromFile();
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
				admin::saveToFile();
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
	switch (log.first)
	{
	case::loginCode::WRONGUSER:
		cout << "username does not exist" << endl;
		break;
	case loginCode::WRONGPASS:
		cout << "Password is wrong" << endl;
		break;
	case loginCode::SUCCESS:
		if (dynamic_cast<admin*>(log.second)) {
			cout << "Login successfully" << endl;
			adminPanel(dynamic_cast<admin*>(log.second));
		}
		else {
			cout << "username dose not exist" << endl;
		}
		break;
	default:
		break;
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
		cout << "[3] Check times of enter and exit to account" << endl;
		cout << "[4] account setting" << endl;
		cout << "[5] Logout" << endl;
		cout << "[#] ";
		int n;
		cin >> n;
		if (n == 1) {
			auto accounts = u->getAccounts();
			if (accounts.empty()) {
				cout << "You dont have any accounts" << endl;
			}
			else {
				cout << "------------------------------------------------------------" << endl;
				for (int i = 0; i < accounts.size(); i++) {
					cout << "[" << i + 1 << "] " << accounts[i]->getId() << endl;
					cout << "Type: ";
					switch (accounts[i]->getType())
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
					switch (accounts[i]->getSituation())
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
					cout << "Balance: " << accounts[i]->getBalance() << endl;
					cout << "Creation date: ";
					accounts[i]->getCEDate().first.print(style::YYYY_MM_DD);
					cout << "Expire date: ";
					accounts[i]->getCEDate().second.print(style::YYYY_MM_DD);
					cout << "------------------------------------------------------------" << endl;
				}
			}
			cout << "[0] Create new account" << endl;
			cout << "[" << accounts.size() + 1 << "] Back" << endl;
			int m;
			do {
				cout << "[#] ";
				cin >> m;
			} while (m<0 || m>accounts.size() + 1);
			if (m == 0) {
				createAccount(u);
				continue;
			}
			else if (m == accounts.size() + 1) {
				continue;
			}
			m--;
			if (accounts[m]->getSituation() == status::NOTVERIFY || accounts[m]->getSituation() == status::EXPIRE) {
				cout << "You cant change this account" << endl;
				continue;
			}
			bankAccountSetting(u,accounts[m]);
		}
		else if (n == 2) {
			transferMoney(u);
		}
		else if (n == 3) {
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
		else if (n == 4) {
			accountSetting(u);
		}
		else if (n == 5) {
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
		cout << "[3] Check times of enter and exit to account" << endl;
		cout << "[4] Account setting" << endl;
		cout << "[5] Admin manager" << endl;
		cout << "[6] Logout" << endl;
		cout << "[#] ";
		int n;
		cin >> n;
		if (n == 1) {
			auto accounts = u->getAccounts();
			if (accounts.empty()) {
				cout << "You dont have any accounts" << endl;
			}
			else {
				cout << "------------------------------------------------------------" << endl;
				for (int i = 0; i < accounts.size();i++) {
					cout << "["  << i+1 << "] " << accounts[i]->getId() << endl;
					cout << "Type: ";
					switch (accounts[i]->getType())
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
					switch (accounts[i]->getSituation())
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
					cout << "Balance: " << accounts[i]->getBalance() << endl;
					cout << "Creation date: ";
					accounts[i]->getCEDate().first.print(style::YYYY_MM_DD);
					cout << "Expire date: ";
					accounts[i]->getCEDate().second.print(style::YYYY_MM_DD);
					cout << "------------------------------------------------------------" << endl;
				}
			}
			cout << "[0] Create new account" << endl;
			cout << "[" << accounts.size() + 1 << "] Back" << endl;
			int m;
			do {
				cout << "[#] ";
				cin >> m;
			} while (m<0 || m>accounts.size() + 1);
			if (m == 0) {
				createAccount(u);
				continue;
			}
			else if (m == accounts.size() + 1) {
				continue;
			}
			m--;
			bankAccountSetting(u,accounts[m]);
		}
		else if (n == 2) {
			transferMoney(u);
		}
		else if (n == 3) {
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
		else if (n == 4) {
			accountSetting(u);
		}
		else if (n == 5) {
			while (true) {
				cout << "[1] See all users" << endl;
				cout << "[2] See accounts" << endl;
				cout << "[3] See Application list" << endl;
				cout << "[4] Back" << endl;
				cout << "[#] ";
				int n;
				cin >> n;
				if (n == 1) {
					auto users = u->getUsers();
					if (users.empty()) {
						cout << "No user found" << endl;
					}
					else {
						cout << "------------------------------------------------------------" << endl;
						for (int i = 0; i < users.size(); i++) {
							cout << "[" << i + 1 << "] " << users[i]->getId() << endl;
							cout << "Name: " << users[i]->getName() << endl;
							cout << "Birthdate: ";
							users[i]->getBirthDate().print(style::YY_MM_DD);
							cout << "Status: " << (users[i]->getIsOnline() == code::ONLINE ? "Online" : "Offline") << endl;
							cout << "------------------------------------------------------------" << endl;
						}
					}
					cout << "[0] Create new user" << endl;
					cout << "[" << users.size() + 1 << "] Back" << endl;
					int n;
					do {
						cout << "[#] ";
						cin >> n;
					} while (n < 0 || n > users.size()+1);
					if (n == 0) {
						userSignup();
						continue;
					}
					else if (n == users.size() + 1) {
						continue;
					}
					n--;
					while (true) {
						cout << "[1] Show enter and exit time" << endl;
						cout << "[2] Show bank accounts" << endl;
						cout << "[3] Edit profile" << endl;
						cout << "[4] Delete profile" << endl;
						cout << "[5] Back" << endl;
						cout << "[#] ";
						int m;
						cin >> m;
						if (m == 1) {
							if (users[n]->getTimeOfADs().empty()) {
								cout << "User dont login yet" << endl;
								continue;
							}
							cout << "------------------------------------------------------------" << endl;
							for (auto t : users[n]->getTimeOfADs()) {
								cout << "Enter Time: ";
								t.first.print(style::YY_MM_DD_HH_MM_SS);
								cout << "Exit Time: ";
								t.second.print(style::YY_MM_DD_HH_MM_SS);
								cout << "------------------------------------------------------------" << endl;
							}
						}
						else if (m == 2) {
							auto accounts = users[n]->getAccounts();
							if (accounts.empty()) {
								cout << "User dont have any accounts" << endl;
							}
							else {
								cout << "------------------------------------------------------------" << endl;
								for (int i = 0; i < accounts.size(); i++) {
									cout << "[" << i + 1 << "] " << accounts[i]->getId() << endl;
									cout << "Type: ";
									switch (accounts[i]->getType())
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
									switch (accounts[i]->getSituation())
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
									cout << "Balance: " << accounts[i]->getBalance() << endl;
									cout << "Creation date: ";
									accounts[i]->getCEDate().first.print(style::YYYY_MM_DD);
									cout << "Expire date: ";
									accounts[i]->getCEDate().second.print(style::YYYY_MM_DD);
									cout << "------------------------------------------------------------" << endl;
								}
							}
							cout << "[0] Create new account" << endl;
							cout << "[" << accounts.size()+1  << "] Back" << endl;
							int p;
							do {
								cout << "[#] ";
								cin >> p;
							} while (p < 0 || p > accounts.size() + 1);
							if (p == 0) {
								createAccount(users[n]);
								break;
							}
							else if (p == accounts.size() + 1) {
								break;
							}
							p--;
							bankAccountSetting(users[n],accounts[p]);
						}
						else if (m == 3) {
							accountSetting(users[n]);
						}
						else if (m == 4) {
							delete users[n];
							break;
						}
						else if (m == 5) {
							break;
						}
					}
				}
				else if (n == 2) {
				auto accounts = u->getAllAccounts();
				if (accounts.empty()) {
					cout << "We dont have any accounts" << endl;
				}
				else {
					cout << "------------------------------------------------------------" << endl;
					for (int i = 0; i < accounts.size(); i++) {
						cout << "[" << i + 1 << "] " << accounts[i].second->getId() << endl;
						cout << "Type: ";
						switch (accounts[i].second->getType())
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
						switch (accounts[i].second->getSituation())
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
						cout << "Balance: " << accounts[i].second->getBalance() << endl;
						cout << "Creation date: ";
						accounts[i].second->getCEDate().first.print(style::YYYY_MM_DD);
						cout << "Expire date: ";
						accounts[i].second->getCEDate().second.print(style::YYYY_MM_DD);
						cout << "------------------------------------------------------------" << endl;
					}
				}
				cout << "[" << accounts.size() + 1 << "] Back" << endl;
				int p;
				do {
					cout << "[#] ";
					cin >> p;
				} while (p <= 0 || p > accounts.size() + 1);
				if (p == accounts.size() + 1) {
					continue;
				}
				p--;
				bankAccountSetting(accounts[p].first,accounts[p].second);
				}
				else if (n == 3) {
					auto list = u->getApplicationList();
					if (list.empty()) {
						cout << "We dont have any application list" << endl;
					}
					else {
						cout << "------------------------------------------------------------" << endl;
						for (int i = 0; i < list.size(); i++) {
							cout << "[" << i + 1 << "] " << list[i].second->getId() << endl;
							cout << "User ID: " << list[i].first->getId() << endl;
							cout << "Type: ";
							switch (list[i].second->getType())
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
							cout << "Balance: " << list[i].second->getBalance() << endl;
							cout << "Creation date: ";
							list[i].second->getCEDate().first.print(style::YYYY_MM_DD);
							cout << "Expire date: ";
							list[i].second->getCEDate().second.print(style::YYYY_MM_DD);
							cout << "------------------------------------------------------------" << endl;
						}
					}
					cout << "[" << list.size() + 1 << "] Back" << endl;
					int m;
					do {
						cout << "[#] ";
						cin >> m;
					} while (m <= 0 || m > list.size() + 1);
					if (m == list.size() + 1) {
						continue;
					}
					m--;
					cout << "[1] Online this account" << endl;
					cout << "[2] Block this account" << endl;
					cout << "[3] Delete this account" << endl;
					int p;
					do {
						cout << "[#] ";
						cin >> p;
					} while (p < 1 || p > 3);
					switch (p)
					{
					case 1: list[m].second->setSituation(status::ONLINE); break;
					case 2: list[m].second->setSituation(status::BLOCK); break;
					case 3: list[m].first->deleteBankAccount(list[m].second); break;
					}
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
void createAccount(person* p) {
	while (true) {
		try {
			cout << "mode: " << endl;
			cout << "[1] Short term" << endl;
			cout << "[2] Long term" << endl;
			cout << "[3] Good loan" << endl;
			int n;
			do {
				cout << "[#] ";
				cin >> n;
			} while (n <= 0 || n > 3);
			mode type = mode::SHORTTERM;
			switch (n)
			{
			case 1: type = mode::SHORTTERM; break;
			case 2: type= mode::LONGTERM; break;
			case 3: type = mode::GOODLOAN; break;
			}
			cout << "balance: ";
			double balance;
			cin >> balance;
			account* acc = p->craeteNewAccount(type, balance);
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
void accountSetting(person* p) {
	while (true) {
		cout << "[1] Change name" << endl;
		cout << "[2] Change birthdate" << endl;
		cout << "[3] Change password" << endl;
		cout << "[4] Back" << endl;
		cout << "[#] ";
		int n;
		cin >> n;
		if (n == 1) {
			cout << "Your name: " << p->getName() << endl;
			cout << "name(firstName lastName): ";
			string name;
			getline(cin >> ws, name);
			p->setName(name);
		}
		else if (n == 2) {
			cout << "Your birthdate: ";
			p->getBirthDate().print(style::YY_MM_DD);
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
			p->setBirthDate(birthDate);
		}
		else if (n == 3) {
			cout << "password: ";
			string password;
			cin >> ws >> password;
			p->setPassword(password);
		}
		else if (n == 4) {
			break;
		}
	}
}
void transferMoney(person* p) {
	string first, second;
	cout << "First account ID: ";
	cin >> first;
	cout << "Second account ID: ";
	cin >> second;
	double balance;
	cout << "Balance: ";
	cin >> balance;
	bool ans = p->moveMoney(first, second, balance);
	if (ans) cout << "Money transfer success" << endl;
	else cout << "Money transfer faild" << endl;
}
void bankAccountSetting(person* p,account* a) {
	while (true) {
		cout << "[1] Change type" << endl;
		cout << "[2] Change Status" << endl;
		cout << "[3] Delete account" << endl;
		cout << "[4] Back" << endl;
		cout << "[#] ";
		int n;
		cin >> n;
		if (n == 1) {
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
			cout << "New mode: " << endl;
			cout << "[1] Short term" << endl;
			cout << "[2] Long term" << endl;
			cout << "[3] Good loan" << endl;
			int n;
			do {
				cout << "[#] ";
				cin >> n;
			} while (n <= 0 || n > 3);
			mode type = mode::SHORTTERM;
			switch (n)
			{
			case 1: type = mode::SHORTTERM; break;
			case 2: type= mode::LONGTERM; break;
			case 3: type = mode::GOODLOAN; break;
			}
			a->setType(type);
		}
		else if (n == 2) {
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
			cout << "new Status: " << endl;
			cout << "[1] Online" << endl;
			cout << "[2] Block" << endl;
			int n;
			do {
				cout << "[#] ";
				cin >> n;
			} while (n <= 0 || n > 3);
			status situation = status::NOTVERIFY;
			switch (n)
			{
			case 1: situation = status::ONLINE; break;
			case 2: situation = status::BLOCK; break;
			}
			a->setSituation(situation);
		}
		else if (n == 3) {
			p->deleteBankAccount(a);
			break;
		}
		else if (n == 4) {
			break;
		}
	}
}
