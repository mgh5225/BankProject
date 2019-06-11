#ifndef admin_H
#define admin_H
#include"person.h"
class admin :public person {
public:
	admin(string name, date birthDate, string username, string password):person(name,birthDate,username,password) {}
	vector<person*> getUsers() {
		vector<person*> users;
		for (auto p : persons) {
			if (!dynamic_cast<admin*>(p)) users.push_back(p);
		}
		return users;
	}
	vector<pair<person*, account*>> getAccounts(){
		vector<pair<person*, account*>> list;
		for (auto u : getUsers()) {
			for (auto a : u->getAccounts()) {
			list.push_back(pair<person*, account*>(u, a));
			}
		}
		return list;
	}
	vector<pair<person*, account*>> getApplicationList() {
		vector<pair<person*, account*>> list;
		for (auto u : getUsers()) {
			for (auto a : u->getAccounts()) {
				if(a->getSituation()==status::NOTVERIFY) list.push_back(pair<person*, account*>(u,a));
			}
		}
		return list;
	}
};
#endif