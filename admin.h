#ifndef admin_H
#define admin_H
#include "person.h"
class admin :public person {
public:
	admin():person(){}
	~admin(){}
	admin(string name, date birthDate, string username, string password):person(name,birthDate,username,password) {}
	admin(const admin& old):person(old){}
	vector<person*> getUsers() {
		vector<person*> users;
		for (auto p : persons) {
			if (!dynamic_cast<admin*>(p)) users.push_back(p);
		}
		return users;
	}
	vector<pair<person*, account*>> getAllAccounts(){
		vector<pair<person*, account*>>list;
		for (auto u : getUsers()) {
			for (auto a : u->getAccounts()) {
				list.push_back(pair<person*,account*>(u,a));
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
	vector<pair<person*, account*>> getAccountsByCondition(bool (*con)(account* acc)) {
		vector<pair<person*, account*>>list;
		for (auto u : getUsers()) {
			for (auto a : u->getAccounts()) {
				if(con(a))list.push_back(pair<person*, account*>(u, a));
			}
		}
		return list;
	}
	static void saveToFile() {
		ofstream stream("persons",ios_base::binary);
		if (!stream.is_open()) { return; }
		for (auto p : persons) {
			stream << p->getId() << endl;
			if (dynamic_cast<admin*>(p)) stream << 1 << endl;
			else stream << 0 << endl;
			stream << p->getTimeOfADs().size() << endl;
			stream << p->getAccounts().size() << endl;
			ofstream stream2(p->getId(), ios_base::binary);
			if (!stream2.is_open()) continue;
			stream2.write((char*)p, sizeof(*p));
			for (auto t : p->getTimeOfADs()) {
				stream2.write((char*)&t, sizeof(pair<date, date>));
			}
			for (auto a : p->getAccounts()) {
				stream2.write((char*)a, sizeof(account));
			}
			stream2.close();
		}
		stream.close();
	}
	static void readFromFile() {
		ifstream stream("persons", ios_base::binary);
		if (!stream.is_open()) { return; }
		while (true) {
			string id;
			int mode;
			int sizeOfTime;
			int sizeOfAcc;
			stream >> id;
			stream >> mode;
			stream >> sizeOfTime;
			stream >> sizeOfAcc;
			if (stream.eof()) break;
			ifstream stream2(id, ios_base::binary);
			if (!stream2.is_open()) continue;
			admin* p = new admin;
			if (mode == 1) stream2.read((char*)p, sizeof(admin));
			else stream2.read((char*)p, sizeof(person));
			p->timeOfADs = new vector<pair<date, date>>;
			for (int i = 0; i < sizeOfTime; i++) {
				pair<date, date> time;
				stream2.read((char*)& time, sizeof(pair<date, date>));
				p->timeOfADs->push_back(time);
			}
			p->accounts = new vector<account*>;
			for (int i = 0; i < sizeOfAcc; i++) {
				account* acc=new account;
				stream2.read((char*)acc, sizeof(account));
				p->accounts->push_back(new account(*acc));
			}
			if(mode==1) persons.push_back(new admin(*p));
			else persons.push_back(new person(*p));
			stream2.close();
		}
		stream.close();
	}
};
#endif