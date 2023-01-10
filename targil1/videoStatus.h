#pragma once

#include "status.h"

#pragma warning(disable: 4996)

class VideoStatus : public Status
{
	string videoSrc;
	int color; // 0 = black and white, 1 = colourful

public:

	VideoStatus(string text, string _vidoeSrc, int _color = 1);

	virtual void printStatus() const override;

	virtual ~VideoStatus() {}

	virtual bool operator==(Status& other) const override
	{
		if (typeid(this) == typeid(other))
			return (Status ::operator==(other) && videoSrc == dynamic_cast<VideoStatus&>(other).videoSrc && color == dynamic_cast<VideoStatus&>(other).color);

		else
			return false;
	}

	virtual bool operator!=(Status& other) const override
	{
			return (!(this->operator==(other)));
	}
};

