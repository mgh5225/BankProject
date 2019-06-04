#ifndef admin_H
#define admin_H
#include"person.h"
#include"user.h"
class admin :public person {
public:
	admin(string name, date birthDate, string username, string password):person(name,birthDate,username,password) {}
	vector<user*> getPersons() {
		vector<user*> users;
		for (auto p : persons) {
			if (dynamic_cast<user*>(p)) users.push_back(dynamic_cast<user*>(p));
		}
		return users;
	}
	vector<pair<user*, account*>> getApplicationList(){
		vector<pair<user*, account*>> list;
		for (auto a : applicationList) {
			list.push_back(pair<user*, account*>(dynamic_cast<user*>(a.first), a.second));
		}
		return list;
	}
};
#endif