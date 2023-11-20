#include "imgStatus.h"

ImgStatus::ImgStatus(string text, string _imgSrc, int _color, time_t _time) :Status(text, _time)
{
	imgSrc = _imgSrc;

	if (_color == 1 || _color == 0)
		color = _color;

}

void ImgStatus::printStatus() const
{
	string helper = "start ";
	helper += imgSrc;
	if (!text.empty())
		Status::printStatus();

	if (color == 0)
		cout << "Black & white Picture\n\n";
	else
		cout << "colourful Picture\n\n";

	system(helper.c_str());
}

void ImgStatus::saveToFile(ofstream& facebookFile)
{
	facebookFile << "I" << Status::getStatus() << endl;
	facebookFile << ctime(&uploadTime) << endl;
	facebookFile << imgSrc << " " << color<<endl;
}