#include "date.h"

using namespace std;


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
	if (_day >= 1 && _day <= 31)
	{
		day = _day;
		return true;
	}
	return false;
}

bool  Date::setMonth(int _month)
{
	if (_month >= 1 && _month <= 12)
	{
		month = _month;
		return true;
	}
	return false;
}

bool  Date::setYear(int _year)
{
	if (_year >= 1900 && _year <= 2022)
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