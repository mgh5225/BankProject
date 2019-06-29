#ifndef date_H
#define date_H
#include<exception>
#include<iostream>
#include <ctime>
using namespace std;
enum class style {
	YY_MM_DD,
	YYYY_MM_DD,
	HH_MM_SS,
	YY_MM_DD_HH_MM_SS
};
class dateException:public exception {
public:
	const char* what() {
		return "Date Exception";
	}
}dateEX;
class date {
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;
public:
	date() {
		year = 0;
		month = 0;
		day = 0;
		hour = 0;
		min = 0;
		sec = 0;
	}
	date(int year, int month, int day, int hour = 0, int min = 0, int sec = 0) :date() {
		setYear(year);
		setMonth(month);
		setDay(day);
		setHour(hour);
		setMin(min);
		setSec(sec);
	}
	date(const date& old) :date() {
		setYear(old.year);
		setMonth(old.month);
		setDay(old.day);
		setHour(old.hour);
		setMin(old.min);
		setSec(old.sec);
	}
	date& operator=(const date& obj){
		if (this != &obj) {
			setYear(obj.year);
			setMonth(obj.month);
			setDay(obj.day);
			setHour(obj.hour);
			setMin(obj.min);
			setSec(obj.sec);
		}
		return *this;
	}
	date& setYear(int y) {
		if (y > 1900) year = y;
		else throw dateEX;
		return *this;
	}
	date& setMonth(int m) {
		if (m > 0 && m < 13) month = m;
		else throw dateEX;
		return *this;
	}
	date& setDay(int d) {
		int mon[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		if (d > 0 && d <= mon[month - 1]) day = d;
		else throw dateEX;
		return *this;
	}
	date& setHour(int h) {
		if (h >= 0 && h < 24) hour = h;
		else throw dateEX;
		return *this;
	}
	date& setMin(int m) {
		if (m >= 0 && m < 60) min = m;
		else throw dateEX;
		return *this;
	}
	date& setSec(int s) {
		if (s >= 0 && s < 60) sec = s;
		else throw dateEX;
		return *this;
	}
	int getYear() {
		return year;
	}
	int getMonth() {
		return month;
	}
	int getDay() {
		return day;
	}
	int getHour() {
		return hour;
	}
	int getMin() {
		return min;
	}
	int getSec() {
		return sec;
	}
	void print(style m) {
		switch (m)
		{
		case style::YY_MM_DD:
			cout << year % 100 << "/" << month << "/" << day << endl;
			break;
		case style::YYYY_MM_DD:
			cout << year << "/" << month << "/" << day << endl;
			break;
		case style::HH_MM_SS:
			cout << hour << ":" << min << ":" << sec << endl;
			break;
		case style::YY_MM_DD_HH_MM_SS:
			cout << year % 100 << "/" << month << "/" << day << " " << hour << ":" << min << ":" << sec << endl;
			break;
		default:
			break;
		}
	}
	static date* getNow() {
		std::time_t t = std::time(0);
		std::tm* now = std::localtime(&t);
		return new date(now->tm_year+1900, now->tm_mon+1, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec);
	}
	static int deltaTime(date first, date second) {
		tm fTime = {};
		fTime.tm_year = first.year-1900;
		fTime.tm_mon = first.month-1;
		fTime.tm_mday = first.day;
		tm sTime = {};
		sTime.tm_year = second.year-1900;
		sTime.tm_mon = second.month-1;
		sTime.tm_mday = second.day;
		return (mktime(&fTime)-mktime(&sTime)) / 86400;
	}
	bool operator==(date& obj) {
		return year == obj.year && month == obj.month && day == obj.day;
	}
	bool operator!=(date& obj) {
		return !(year == obj.year && month == obj.month && day == obj.day);
	}
	bool operator>=(date& obj) {
		return deltaTime(*this,obj) >= 0;
	}
};
#endif