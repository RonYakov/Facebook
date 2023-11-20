#pragma once
#include "status.h"

#pragma warning(disable: 4996)

class ImgStatus : public Status
{
	string imgSrc;
	int color; // 0 = black and white, 1 = colourful

public:
	//ctor
	ImgStatus(string text, string _imgSrc, int _color = 1, time_t _time=0);

	//-------------------------------------------------------------------
	
	virtual void printStatus() const override;

	//-------------------------------------------------------------------

	virtual void saveToFile(ofstream& facebookFile);//save data to file

	//-------------------------------------------------------------------
	
	//dtor
	virtual ~ImgStatus() {}

	//-------------------------------------------------------------------

	virtual bool operator==(Status & other) const override
	{
		if (typeid(this) == typeid(other))
			return (Status ::operator==(other) && imgSrc == dynamic_cast<ImgStatus&>(other).imgSrc && color == dynamic_cast<ImgStatus&>(other).color);

		else
			return false;
	}
	virtual bool operator!=(Status& other) const override
	{
		return (!(this->operator==(other)));
	}
};
