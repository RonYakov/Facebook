#pragma once
#include <iostream>
#include<time.h>
#include <string>

using std::string;
using namespace std;

#pragma warning(disable: 4996)

class Status
{
	string text;
	time_t uploadTime;

public:
	//cto'r
	Status(const Status& stat);
	Status(const string _text);

	//-------------------------------------------------------------------

	void setText(const string _text);//The function sets the status text

	//-------------------------------------------------------------------

	const string gesStatus() const { return text; }//The function return the whole status

	//-------------------------------------------------------------------

	void printStatus()const;//The function prints the status

	//-------------------------------------------------------------------

	//distractor
	~Status() {}

	bool operator==(const Status& other) const
	{
		return (this->text == other.text);
	}
	bool operator!=(const Status& other) const
	{
		return (this->text != other.text);
	}
};