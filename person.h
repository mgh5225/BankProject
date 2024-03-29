#ifndef person_H
#define person_H
#include <exception>
#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include "date.h"
#include "account.h"
using namespace std;
enum class code {
	ONLINE,
	OFFLINE,
	BLOCK
};
enum class loginCode {
	SUCCESS,
	WRONGPASS,
	WRONGUSER
};
class personException:public exception {
	string data;
public:
	const char* what() {
		return data.c_str();
	}
	personException& operator()(string _data) {
		data = _data;
		return *this;
	}
}personEX;
class person {
private:
	static string createID() {
		string chr = "0123456789QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";
		string temp;
		srand(time(nullptr));
		while (true) {
			bool f = false;
			temp.clear();
			for (int i = 0; i < 10; i++) {
				temp.push_back(chr[rand() % chr.size()]);
			}
			if (persons.empty()) break;
			for (auto p : persons) {
				if (temp == p->id) {
					f = true;
					break;
				}
			}
			if (!f) break;
		}
		return temp;
	}
protected:
	static person* found(string username) {
		for (auto p : persons) {
			if (username == p->username) return p;
		}
		return nullptr;
	}
	static vector<person*> persons;
	string id;
	string name;
	date birthDate;
	code isOnline;
	string username;
	string password;
	vector<account*>* accounts;
	vector<pair<date,date>>* timeOfADs;
	virtual void addProfit() {
		for (auto a : *accounts) {
			try {
				a->addProfit();
			}
			catch (accountException ex) {
				cout << ex.what() << endl;
			}
		}
	}
public:
	person() {
		isOnline = code::OFFLINE;
		accounts = new vector<account*>;
		timeOfADs = new vector<pair<date, date>>;
	}
	person(string name, date birthDate, string username, string password) {
		if (found(username)) throw personEX("Username exist");
		this->id = createID();
		this->name = name;
		this->birthDate = birthDate;
		this->username = username;
		this->password = password;
		this->isOnline = code::OFFLINE;
		this->timeOfADs = new vector<pair<date, date>>;
		this->accounts = new vector<account*>;
		persons.push_back(this);
	}
	person(const person& old) {
		id = old.id;
		name = old.name;
		birthDate = old.birthDate;
		isOnline = old.isOnline;
		username = old.username;
		password = old.password;
		accounts = new vector<account*>(*old.accounts);
		timeOfADs = new vector<pair<date, date>>(*old.timeOfADs);
	}
	person& operator=(const person& old) {
		throw personEX;
	}
	virtual ~person() {
		for (auto a : *accounts) {
			delete a;
		}
		delete accounts;
		delete timeOfADs;
		for (int i = 0; i < persons.size();i++) {
			if (this == persons[i]) {
				persons.erase(persons.begin() + i);
				break;
			}
		}
		remove(id.c_str());
	}
	static pair<loginCode, person*> login(string username, string password) {
		person* p = found(username);
		if (!p) return pair<loginCode, person*>(loginCode::WRONGUSER,nullptr);
		if(p->password!=password) return pair<loginCode, person*>(loginCode::WRONGPASS, nullptr);
		if (p->isOnline == code::BLOCK) throw personEX("Your account has been blocked");
		if (p->isOnline == code::ONLINE) p->logout();
		if (!p->timeOfADs->empty() && p->timeOfADs->back().second != *date::getNow()) {
			p->addProfit();
		}
		p->timeOfADs->push_back(pair<date, date>(*date::getNow(),*date::getNow()));
		p->setIsOnline(code::ONLINE);
		return pair<loginCode, person*>(loginCode::SUCCESS, p);
	}
	void logout() {
		if(isOnline==code::ONLINE)
			setIsOnline(code::OFFLINE);
	}
	string getId() {
		return id;
	}
	string getName() {
		return name;
	}
	date getBirthDate() {
		return birthDate;
	}
	code getIsOnline() {
		return isOnline;
	}
	vector<pair<date, date>> getTimeOfADs() {
		return *timeOfADs;
	}
	const vector<account*> getAccounts() {
		return *accounts;
	}
	void setName(string name) {
		if (isOnline == code::BLOCK) throw personEX("Your account has been blocked");
		this->name = name;
	}
	void setBirthDate(date birthDate) {
		if (isOnline == code::BLOCK) throw personEX("Your account has been blocked");
		this->birthDate = birthDate;
	}
	void setIsOnline(code isOnline) {
		this->isOnline = isOnline;
		switch (isOnline)
		{
		case code::ONLINE:
			timeOfADs->back().first = *date::getNow();
			break;
		case code::OFFLINE:
			timeOfADs->back().second = *date::getNow();
;			break;
		default:
			break;
		}
	}
	void setUsername(string username) {
		if (isOnline == code::BLOCK) throw personEX("Your account has been blocked");
		if (found(username))throw personEX("Username exist");
		this->username = username;
	}
	void setPassword(string password) {
		if (isOnline == code::BLOCK) throw personEX("Your account has been blocked");
		this->password = password;
	}
	bool moveMoney(string f, string s, double balance) {
		if (isOnline == code::BLOCK) throw personEX("Your account has been blocked");
		if (isOnline == code::OFFLINE)return false;
		if (balance < 0) return false;
		account * first=nullptr,* second=nullptr;
		for (auto a : *accounts) {
			if (a->getId() == f && !first) first = a;
			else if (a->getId() == s && !second) second = a;
			else break;
		}
		if (!first || !second) return false;
		if (first->getSituation() != status::ONLINE || second->getSituation() != status::ONLINE) return false;
		if (balance > first->getBalance()) return false;
		first->setBalance(first->getBalance() - balance);
		second->setBalance(second->getBalance() + balance);
		return true;
	}
	account * craeteNewAccount(mode type, double balance) {
		if (isOnline == code::BLOCK) throw personEX("Your account has been blocked");
		accounts->push_back(new account(type, balance));
		return accounts->back();
	}
	void deleteBankAccount(account* a) {
		if (isOnline == code::BLOCK) throw personEX("Your account has been blocked");
		for (int i = 0; i < accounts->size(); i++) {
			if (a == (*accounts)[i]) {
				accounts->erase(accounts->begin() + i);
				delete a;
				break;
			}
		}
	}
};
vector<person*> person::persons;
#endif