#ifndef user_H
#define user_H
#include<map>
#include"person.h"
class user :public person {
	vector<account*> accounts;
	void addProfit() {
		for (auto a : accounts) {
			a->addProfit();
		}
	}
public:
	user(string name, date birthDate, string username, string password) :person(name,birthDate,username,password) {}
	const vector<account*> getAccounts() {
		return accounts;
	}
	bool moveMoney(account* first, account* second, double balance) {
		if (isOnline == code::OFFLINE)return false;
		if (balance < 0) return false;
		if (first->getSituation() != status::ONLINE || second->getSituation() != status::ONLINE) return false;
		if (balance > first->getBalance()) return false;
		first->setBalance(first->getBalance() - balance);
		second->setBalance(second->getBalance() + balance);
		return true;
	}
	account * craeteNewAccount(mode type, double balance) {
		if (isOnline == code::OFFLINE) return nullptr;
		applicationList.push_back(pair<user*,account*>(this,new account(type, balance)));

	}
	vector<pair<string, status>> getAccountsStatus() {
		vector<pair<string, status>> s;
		for (auto a : accounts) {
			s.push_back(pair<string, status>(a->getId(), a->getSituation()));
		}
		for (auto a : applicationList) {
			if(dynamic_cast<user*>(a.first)==this) s.push_back(pair<string, status>(a.second->getId(), a.second->getSituation()));
		}
		return s;
	}
};
#endif
