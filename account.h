#ifndef account_H
#define account_H
#include<iostream>
#include<vector>
#include <utility>
#include"date.h"
using namespace std;
enum class mode {
	SHORTTERM,
	LONGTERM,
	GOODLOAN
};
enum class status {
	ONLINE,
	BLOCK,
	EXPIRE,
	NOTVERIFY
};
class accountException :public exception {
	string data;
public:
	const char* what() {
		return data.c_str();
	}
	accountException& operator()(string _data) {
		data = _data;
		return *this;
	}
}accountEX;
class account {
private:
	static string createID() {
		string chr = "0123456789";
		string temp;
		srand(time(nullptr));
		while (true) {
			bool f = false;
			temp.clear();
			for (int i = 0; i < 15; i++) {
				temp.push_back(chr[rand() % chr.size()]);
			}
			if (accounts.empty()) break;
			for (auto a : accounts) {
				if (temp == a->id) {
					f = true;
					break;
				}
			}
			if (!f) break;
		}
		return temp;
	}
	static vector<account*> accounts;
	string id;
	double balance;
	date creationDate;
	date expireDate;
	mode type;
	status situation;
	double getProfit() {
		switch (type){
		case mode::SHORTTERM:
			return 0.1;
		case mode::LONGTERM:
			return 0.15;
		case mode::GOODLOAN:
			return 0;
		default:
			throw accountEX("Type is not define");
			break;
		}
	}
public:
	account() {
		balance = 0;
		type = mode::SHORTTERM;
		situation = status::NOTVERIFY;
	}
	~account() {
		for (int i = 0; i < accounts.size(); i++) {
			if (this == accounts[i]) {
				accounts.erase(accounts.begin() + i);
				break;
			}
		}
	}
	account(mode type, double balance) {
		if (balance < 0) throw accountEX("Balance < 0");
		this->type = type;
		this->balance = balance;
		this->id = createID();
		this->situation = status::NOTVERIFY;
		this->creationDate = *date::getNow();
		this->expireDate= date::getNow()->setYear(creationDate.getYear()+5);
		accounts.push_back(this);
	}
	account(const account& old) {
		id = old.id;
		balance = old.balance;
		creationDate = old.creationDate;
		expireDate = old.expireDate;
		type = old.type;
		situation = old.situation;
		accounts.push_back(this);
	}
	account& operator=(const account& old) {
		throw accountEX("Bad signatur");
	}
	void setBalance(double b) {
		if (situation == status::EXPIRE) throw accountEX("Bank account has been expired");
		if (b >= 0 && situation==status::ONLINE) balance = b;
	}
	void setType(mode type) {
		if (situation == status::EXPIRE) throw accountEX("Bank account has been expired");
		int delta = date::deltaTime(*date::getNow(), creationDate);
		this->type = type;
		setBalance( balance + balance * getProfit() * delta );
		creationDate = *date::getNow();
	}
	void setSituation(status situation) {
		if (this->situation == status::EXPIRE) throw accountEX("Bank account has been expired");
		this->situation = situation;
	}
	string getId() {
		return id;
	}
	double getBalance() {
		return balance;
	}
	status getSituation() {
		return situation;
	}
	mode getType() {
		return type;
	}
	pair<date, date> getCEDate() {
		return pair<date, date>(creationDate, expireDate);
	}
	void addProfit() {
		if (situation == status::EXPIRE) throw accountEX("Bank account has been expired");
		int delta = date::deltaTime(*date::getNow(),creationDate);
		if (delta > 0) {
			setBalance( balance + balance * getProfit() * delta);
		}
	}
	friend void checkExpire();
};
vector<account*> account::accounts;
#endif