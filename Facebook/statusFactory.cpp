#include "statusFactory.h"


Status* StatusFactory::createNewStatus(char type, string text, time_t time, string nameOfFile, int color)
{
	if (type == 'T')
	{
		if (text.empty())
			throw emptyTextForStatusException();
		else
		{
				return new Status(text, time);
		}
	}
	else if (type == 'I')
	{
		if (nameOfFile.empty())
			throw emptyFileNameForStatusException();

		else if (color != 1 && color != 0)
			throw colorForStatusException();

		else
		{
			return new ImgStatus(text, nameOfFile, color, time);
		}
	}

	else if (type == 'V')
	{
		if (nameOfFile.empty())
			throw emptyFileNameForStatusException();

		else if (color != 1 && color != 0)
			throw colorForStatusException();

		else
		{
			return new VideoStatus(text, nameOfFile, color, time);
		}
	}
}


Status* StatusFactory::loadFromFile(ifstream& facebookFile)
{
	tm tm;
	time_t time;
	string strTime, text, nameOfFile;
	char type,readSpace;
	int color;

	facebookFile >> type; 
	getline(facebookFile,text);
	getline(facebookFile, strTime);
	istringstream ss(strTime);
	ss >> get_time(&tm, "%a %b %d %H:%M:%S %Y");
	//auto time_point = chrono::system_clock::from_time_t(std::mktime(&tm));
	//time = chrono::system_clock::to_time_t(time_point);
	time = mktime(&tm);

	if (type == 'I' || type == 'V')
	{
		facebookFile >> nameOfFile >> color;
		return createNewStatus(type, text, time, nameOfFile, color);
	}

	return createNewStatus(type, text, time);
}