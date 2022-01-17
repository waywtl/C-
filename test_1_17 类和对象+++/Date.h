#define _CRT_SECURE_NO_WARNINGS 1
#pragma once

#include <iostream>
using namespace std;

class Date
{
public:
	Date(int year = 1, int month = 1, int day = 1);
	void Print();
	int GetMonthDay(int year, int month);

	bool operator>(const Date& d);
	bool operator>=(const Date& d);
	bool operator==(const Date& d);
	bool operator<(const Date& d);
	bool operator<=(const Date& d);
	bool operator!=(const Date& d);

	Date& operator+=(int day);
	Date operator+(int day);
	Date& operator-=(int day);
	Date operator-(int day);

	// Ç°ÖÃ++/--   ++d1
	Date& operator++();
	Date& operator--();
	// ºóÖÃ++/--   d1++
	Date operator++(int);
	Date operator--(int);

	int operator-(const Date& d);
	void PrintWeekDay();

private:
	int _year;
	int _month;
	int _day;
};