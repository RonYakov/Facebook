#pragma once
#include <iostream>
#include <string>
#include<fstream>

#pragma warning(disable: 4996)

using std::string;
using namespace std;


class DateDayException : public exception
{
	string excep;

public:
	DateDayException(int day)
	{
		excep = day;
		excep += "Invalid day date, day must be between 1-31\n";
	}

	const char* what() const
	{
		return excep.c_str();
	}
};

class DateMonthException : public exception
{
	string excep;

public:
	DateMonthException(int month)
	{
		excep = month;
		excep += "Invalid month date, month must be between 1-12\n";
	}

	const char* what() const
	{
		return excep.c_str();
	}
};

class DateYearException : public exception
{
	string excep;

public:
	DateYearException(int year)
	{
		excep = year;
		excep += "Invalid year date, year must be between 1900-2022\n";
	}

	const char* what() const
	{
		return excep.c_str();
	}
};

const int DAY_MIN = 1;
const int DAY_MAX = 31;
const int MONTH_MIN = 1;
const int MONTH_MAX = 12;
const int YEAR_MIN = 1900;
const int YEAR_MAX = 2023;

class Date
{
	int day;
	int month;
	int year;

public:
	//cto'r
	Date() = default;
	Date(int _day, int _month, int _year);

	//-------------------------------------------------------------------

	bool setDay(int _day); //The function sets the day
	bool setMonth(int _month);//The function sets the month
	bool setYear(int _year);//The function sets the year

	//-------------------------------------------------------------------

	const Date* getDate() const { return this; } //The function return the whole date
	int getDay() const { return day; }//The function return the day
	int getMonth() const { return month; }//The function return the month
	int getYear() const { return year; }//The function return the year

	//-------------------------------------------------------------------

	void saveToFile(ofstream& facebookFile); // save data to file
	void loadFromFile(ifstream& facebookFile); //load data from file

	void print();//The function prints the date
};