#pragma once

#include "status.h"
#include "videoStatus.h"
#include "imgStatus.h"

class StatusFactory {
public:

	//The class that uses this function must delete the dynamic allocation
	static Status* createNewStatus(char type, string text, string nameOfFile = "\0", int color = 1);

};

class colorForStatusException : public exception
{
	string excep;

public:
	colorForStatusException()
	{
		excep = "Invalid color input\n\n";
	}

	const char* what() const
	{
		return excep.c_str();
	}
};

class emptyTextForStatusException : public exception
{
	string excep;

public:
	emptyTextForStatusException()
	{
		excep = "Text status can not be empty\n\n";
	}

	const char* what() const
	{
		return excep.c_str();
	}
};

class emptyFileNameForStatusException : public exception
{
	string excep;

public:
	emptyFileNameForStatusException()
	{
		excep = "File name of pic/video can not be empty\n\n";
	}

	const char* what() const
	{
		return excep.c_str();
	}
};

