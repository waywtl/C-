#define _CRT_SECURE_NO_WARNINGS 1
#include "Date.h"

void TestDate1()
{
	Date d1;
	Date d2(2022, 1, 17);
	Date d3(2022, 1, 116);
	d1.Print();
	d2.Print();
	d3.Print();
}

void TestDate2()
{
	Date d1(2022, 1, 17);
	Date d2 = d1 + 15;
	d2.Print();

	Date d3(2022, 1, 17);
	Date d4 = d3 - 1500;
	d4.Print();
}

void TestDate3()
{
	Date d1(2022, 1, 17);
	Date d2 = --d1;
	Date d3 = d1--;
	d1.Print();
	d2.Print();
	d3.Print();
}

void TestDate4()
{
	Date today(2022, 1, 17);
	Date offerday(2022, 9, 1);
	cout << (offerday - today) << endl;
	cout << (today - offerday) << endl;
	today.PrintWeekDay();
}

int main()
{
	TestDate4();

	return 0;
}