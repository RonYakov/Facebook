#pragma once
#include <iostream>
#include<time.h>
#include <string>

using std::string;
using namespace std;

#pragma warning(disable: 4996)

class Status
{
	time_t uploadTime;

protected:
	string text;
public:
	//cto'r
//	Status(const Status& stat);
	Status(const string _text);

	//-------------------------------------------------------------------


	//-------------------------------------------------------------------

	const string getStatus() const { return text; }//The function return the whole status

	//-------------------------------------------------------------------

	virtual void printStatus() const;//The function prints the status

	//-------------------------------------------------------------------

	//distractor
	virtual ~Status() {}

	virtual bool operator==(Status& other) const
	{
		return (this->text == other.text);
	}
	virtual bool operator!=(Status& other) const
	{
		return (this->text != other.text);
	}
};