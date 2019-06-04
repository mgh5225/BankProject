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
	date(){}
	date(int year, int month, int day, int hour = 0, int min = 0, int sec = 0) {
		setYear(year);
		setMonth(month);
		setDay(day);
		setHour(hour);
		setMin(min);
		setSec(sec);
	}
	date(const date& old) {
		setYear(old.year);
		setMonth(old.month);
		setDay(old.day);
		setHour(old.hour);
		setMin(old.min);
		setSec(old.sec);
	}
	date& setYear(int y) {
		if (y > 2000) year = y;
		else throw dateEX;
	}
	date& setMonth(int m) {
		if (m > 0 && m < 13) month = m;
		else throw dateEX;
	}
	date& setDay(int d) {
		int mon[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
		if (d > 0 && d <= mon[month - 1]) day = d;
		else throw dateEX;
	}
	date& setHour(int h) {
		if (h >= 0 && h < 24) hour = h;
		else throw dateEX;
	}
	date& setMin(int m) {
		if (m >= 0 && m < 60) min = m;
		else throw dateEX;
	}
	date& setSec(int s) {
		if (s >= 0 && s < 60) sec = s;
		else throw dateEX;
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
		return new date(now->tm_year, now->tm_mon, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec);
	}
	static int deltaTime(date first, date second) {
		tm fTime;
		fTime.tm_year = first.year;
		fTime.tm_mon = first.month;
		fTime.tm_mday = first.day;
		tm sTime;
		sTime.tm_year = second.year;
		sTime.tm_mon = second.month;
		sTime.tm_mday = second.day;
		return difftime(mktime(&fTime), mktime(&sTime)) / 86400;
	}
	bool operator==(date& obj) {
		return year == obj.year && month == obj.month && day == obj.day;
	}
	bool operator!=(date& obj) {
		return !(year == obj.year && month == obj.month && day == obj.day);
	}
};
#endif

