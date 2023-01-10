#include "imgStatus.h"

ImgStatus::ImgStatus(string text, string _imgSrc, int _color) :Status(text)
{
	imgSrc = "start ";
	imgSrc += _imgSrc;

	if (_color == 1 || _color == 0)
		color = _color;

}

void ImgStatus::printStatus() const
{
	if (!text.empty())
		Status::printStatus();

	if (color == 0)
		cout << "Black & white Picture\n\n";
	else
		cout << "colourful Picture\n\n";

	system(imgSrc.c_str());
}