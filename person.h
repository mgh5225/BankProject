#ifndef person_H
#define person_H
#include<exception>
#include<iostream>
#include<vector>
#include<utility>
#include<fstream>
#include"date.h"
#include"account.h"
using namespace std;
enum class code {
	ONLINE,
	OFFLINE
};
enum class loginCode {
	SUCCESS,
	WRONGPASS,
	WRONGUSER
};
class personException:public exception {
public:
	const char* what() {
		return "Person Exception";
	}
}personEX;
class person {
private:
	string createID() {
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
			a->addProfit();
		}
	}
public:
	person() {
		isOnline = code::OFFLINE;
		accounts = nullptr;
		timeOfADs = nullptr;
	}
	person(string name, date birthDate, string username, string password) {
		if (found(username)) throw personEX;
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
	virtual ~person() {
		for (auto a : *accounts) {
			delete a;
		}
	}
	static pair<loginCode, person*> login(string username, string password) {
		person* p = found(username);
		if (!p) return pair<loginCode, person*>(loginCode::WRONGUSER,nullptr);
		if(p->password!=password) return pair<loginCode, person*>(loginCode::WRONGPASS, nullptr);
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
	static void readFromFile() {
		ifstream stream("persons.p", ios_base::binary);
		if (stream.is_open()) {
			while (true) {
				string id;
				stream >> id;
				if (stream.eof())break;
				ifstream stream2(id, ios_base::binary);
				if (stream2.is_open()) {
					person* p = new person;
					streamsize size;
					stream >> size;
					stream2.read((char*)p,size);
					p->timeOfADs = new vector<pair<date, date>>;
					p->accounts = new vector<account*>;
					persons.push_back(new person(*p));
					size_t l;
					stream >> l;
					for (int i = 0; i < l; i++) {
						pair<date, date> time;
						stream2.read((char*)& time, sizeof(pair<date, date>));
						p->timeOfADs->push_back(time);
					}
					stream >> l;
					for (int i = 0; i < l; i++) {
						account* acc = new account;
						stream2.read((char*)acc, sizeof(account));
						p->accounts->push_back(new account(*acc));
					}
				}
				stream2.close();
			}
		}
		stream.close();
	}
	static void saveToFile() {
		ofstream stream("persons.p", ios_base::binary);
		if (stream.is_open()) {
			for (auto p : persons) {
				stream << p->id << endl;
				stream << sizeof(*p) << endl;
				stream << p->timeOfADs->size() << endl;
				stream << p->accounts->size() << endl;
				ofstream stream2(p->id, ios_base::binary);
				if (stream2.is_open()) {
					stream2.write((char*)p, sizeof(*p));
					for (auto t : *(p->timeOfADs)) {
						stream2.write((char*)& t, sizeof(pair<date, date>));
					}
					for (auto a : *(p->accounts)) {
						stream2.write((char*)a, sizeof(account));
					}
				}
				stream2.close();
			}
		}
		stream.close();
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
	void setName(string name) {
		this->name = name;
	}
	void setBirthDate(date birthDate) {
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
		if (found(username))throw personEX;
		this->username = username;
	}
	void setPassword(string password) {
		this->password = password;
	}
	const vector<account*> getAccounts() {
		return *accounts;
	}
	bool moveMoney(string f, string s, double balance) {
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
		if (isOnline == code::OFFLINE) throw personEX;
		accounts->push_back(new account(type, balance));
		return accounts->back();
	}

};
vector<person*> person::persons;
#endif