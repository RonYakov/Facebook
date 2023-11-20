#include "date.h"


Date::Date(int _day, int _month, int _year)
{
	if (!setDay(_day))
		throw DateDayException(_day);

	if (!setMonth(_month))
		throw DateMonthException(_month);

	if (!setYear(_year))
		throw DateYearException(_year);

}


bool  Date::setDay(int _day)
{
	if (_day >= DAY_MIN && _day <= DAY_MAX)
	{
		day = _day;
		return true;
	}
	return false;
}

bool  Date::setMonth(int _month)
{
	if (_month >= MONTH_MIN && _month <= MONTH_MAX)
	{
		month = _month;
		return true;
	}
	return false;
}

bool  Date::setYear(int _year)
{
	if (_year >= YEAR_MIN && _year <= YEAR_MAX)
	{
		year = _year;
		return true;
	}
	return false;
}

void Date::print()
{
	cout << day << "/" << month << "/" << year;
}

void Date::saveToFile(ofstream& facebookFile)
{
	facebookFile << day << " " << month << " " << year << endl;
}

void Date::loadFromFile(ifstream& facebookFile)
{
	char readEnter;
	facebookFile >> day >>  month >>  year ;
}