#include "videoStatus.h"

VideoStatus::VideoStatus(string text, string _vidoeSrc, int _color, time_t _time) : Status(text, _time)
{
	videoSrc = _vidoeSrc;

	if (_color == 1 || _color == 0)
		color = _color;

}

void VideoStatus::printStatus() const
{
	string helper = "start ";
	helper += videoSrc;

	if (!text.empty())
		Status::printStatus();

	if (color == 0)
		cout << "Black & white Video\n\n";
	else 
		cout << "colourful Video\n\n";
	system(helper.c_str());
}

void VideoStatus::saveToFile(ofstream& facebookFile)
{
	facebookFile << "V" << text << endl;
	facebookFile << ctime(&uploadTime) << endl;
	facebookFile << videoSrc << " " << color << endl;
}