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
void userPanel(person* u);
void adminPanel(admin* a);
int main(){
	cout << "[ALERT] ALL USERS LOAD FROM FILE AT THE FRIST TIME AND SAVE TO FILE WHEN YOU EXIT THE PROGRAM [ALERT]" << endl;
	person::readFromFile();
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
			person::saveToFile();
			return 0;
		default:
			break;
		}
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
	cout << "username:";
	string username;
	cin >> ws >> username;
	cout << "password:";
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
			cout << "Login successfuly" << endl;
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
	cout << "username:";
	string username;
	cin >> ws >> username;
	cout << "password:";
	string password;
	cin >> ws >> password;
	auto log = person::login(username, password);
	if (dynamic_cast<admin*>(log.second)) {
		switch (log.first)
		{
		case::loginCode::WRONGUSER:
			cout << "username does not exist" << endl;
			break;
		case loginCode::WRONGPASS:
			cout << "Password is wrong" << endl;
			break;
		case loginCode::SUCCESS:
			cout << "Login successfuly" << endl;
			adminPanel(dynamic_cast<admin*>(log.second));
			break;
		default:
			break;
		}
	}
	else {
		cout << "username dose not exist" << endl;
	}
}
void userSignup(){
	cout << endl;
	cout << "name(firstName lastName):";
	string name;
	getline(cin>>ws, name);
	date birthDate;
	while (true) {
		try {
			cout << "birthDate(YYYY MM DD):";
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
			cout << "username:";
			string username;
			cin >> ws >> username;
			cout << "password:";
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
	cout << "name(firstName lastName):";
	string name;
	getline(cin >> ws, name);
	date birthDate;
	while (true) {
		try {
			cout << "birthDate(YYYY MM DD):";
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
			cout << "username:";
			string username;
			cin >> ws >> username;
			cout << "password:";
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
		cout << "[1] Check status of accounts" << endl;
		cout << "[2] Transfer money between bank accounts" << endl;
		cout << "[3] Create new account" << endl;
		cout << "[4] Check times of enter and exit to account" << endl;
		cout << "[5] account setting" << endl;
		cout << "[6] Logout" << endl;
		cout << "[#] ";
		int n;
		cin >> n;
		if (n == 1) {
			auto accounts = u->getAccounts();
			if (accounts.empty()) {
				cout << "You dont have any accounts" << endl;
				continue;
			}
			for (auto a : accounts) {
				cout << "ID: " << a->getId() << endl;
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
				cout << "Balance: " << a->getBalance() << endl;
				cout << "Creation date: ";
				a->getCEDate().first.print(style::YYYY_MM_DD);
				cout << "Expire date: ";
				a->getCEDate().second.print(style::YYYY_MM_DD);
				cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
			}
		}
		else if (n == 2) {

		}
		else if (n == 3) {

		}
		else if (n == 4) {

		}
		else if (n == 5) {

		}
		else if (n == 6) {
			u->logout();
			cout << "bye " << u->getName() << endl;
			break;
		}
	}
}
void adminPanel(admin* a){
	cout << endl;
}
