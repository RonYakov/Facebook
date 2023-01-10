#pragma once
#include "status.h"

#pragma warning(disable: 4996)

class ImgStatus : public Status
{
	string imgSrc;
	int color; // 0 = black and white, 1 = colourful

public:

	ImgStatus(string text, string _imgSrc, int _color = 1);

	virtual void printStatus() const override;

	virtual ~ImgStatus() {}

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
