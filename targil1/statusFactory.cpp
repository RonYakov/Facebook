#include "statusFactory.h"

Status* StatusFactory::createNewStatus(char type, string text, string nameOfFile, int color)
{
	if (type == 'T')
	{
		if (text.empty())
			throw emptyTextForStatusException();
		else
		{
			return new Status(text); 
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
			return new ImgStatus(text, nameOfFile, color);
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
			return new VideoStatus(text, nameOfFile, color);
		}
	}
}