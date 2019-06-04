#ifndef person_H
#define person_H
#include<exception>
#include<iostream>
#include<vector>
#include<utility>
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
		bool t = true;
		string chr = "0123456789QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm";
		string temp;
		srand(time(nullptr));
		while (t) {
			temp.clear();
			for (int i = 0; i < 10; i++) {
				temp.push_back(chr[rand() % chr.size()]);
			}
			for (auto p : persons) {
				if (temp == p->id) {
					t = false;
					break;
				}
			}
			if (persons.empty()) break;
		}
		return temp;
	}
protected:
	static vector<person*> persons;
	static vector<pair<person*, account*>>applicationList;
	static person* found(string username) {
		for (auto p : persons) {
			if (username == p->username) return p;
		}
		return nullptr;
	}
	string id;
	string name;
	date birthDate;
	code isOnline;
	string username;
	string password;
	pair<date,date> timeOfAD;
	virtual void addProfit() {}
public:
	person(string name, date birthDate, string username, string password) {
		if (found(username)) throw personEX;
		this->name = name;
		this->id = createID();
		this->birthDate = birthDate;
		this->username = username;
		this->isOnline = code::OFFLINE;
		persons.push_back(this);
	}
	virtual ~person() {}
	static pair<loginCode, person*> login(string username, string userpass) {
		person* p = found(username);
		if (!p) return pair<loginCode, person*>(loginCode::WRONGUSER,nullptr);
		if(p->password!=userpass) return pair<loginCode, person*>(loginCode::WRONGPASS, nullptr);
		p->setIsOnline(code::ONLINE);
		p->timeOfAD.first = *date::getNow();
		if (p->timeOfAD.second != *date::getNow()) {
			p->addProfit();
		}
		return pair<loginCode, person*>(loginCode::SUCCESS, p);
	}
	void logout() {
		timeOfAD.second = *date::getNow();
	}
	static void readFromFile() {

	}
	static void saveToFile() {

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
	pair<date, date> getTimeOfAD() {
		return timeOfAD;
	}
	void setName(string name) {
		this->name = name;
	}
	void setIsOnline(code isOnline) {
		this->isOnline = isOnline;
	}
};
#endif
