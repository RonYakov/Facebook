#pragma once
#include <iostream>
#include<time.h>
#include <string>
#include <fstream>


#pragma warning(disable: 4996)
using std::string;
using namespace std;

class Status
{
protected:
	time_t uploadTime;
	string text;
public:
	//cto'r
	Status(const string _text, time_t _time=0);
	//-------------------------------------------------------------------

	virtual void saveToFile(ofstream &facebookFile);// save data to file

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