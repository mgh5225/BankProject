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
public:
	const char* what() {
		return "Account Exception";
	}
}accountEX;
class account {
private:
	string createID() {
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
			throw accountEX;
			break;
		}
	}
public:
	account() {
		balance = 0;
		type = mode::SHORTTERM;
		situation = status::NOTVERIFY;
	}
	account(mode type, double balance) {
		if (balance < 0) throw accountEX;
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
	}
	account* operator=(const account& old) {
		if (this != &old) {
			id = old.id;
			balance = old.balance;
			creationDate = old.creationDate;
			expireDate = old.expireDate;
			type = old.type;
			situation = old.situation;
		}
		return this;
	}
	void setBalance(double b) {
		if (*date::getNow() == expireDate) {
			situation = status::EXPIRE;
			throw accountEX;
		}
		if (b > 0 && situation==status::ONLINE) balance = b;
	}
	void setType(mode type) {
		if (*date::getNow() == expireDate) {
			situation = status::EXPIRE;
			throw accountEX;
		}
		int delta = date::deltaTime(creationDate, *date::getNow());
		this->type = type;
		balance += balance * getProfit() * delta;
		creationDate = *date::getNow();
	}
	void setSituation(status situation) {
		if (*date::getNow() == expireDate) {
			situation = status::EXPIRE;
			throw accountEX;
		}
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
		if (creationDate == expireDate) throw accountEX;
		int delta = date::deltaTime(creationDate, *date::getNow());
		if (delta > 0) {
			balance += balance * getProfit() * delta;
		}
	}
};
vector<account*> account::accounts;
#endif