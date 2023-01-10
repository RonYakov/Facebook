#include "videoStatus.h"

VideoStatus::VideoStatus(string text, string _vidoeSrc, int _color) : Status(text)
{
	videoSrc = "start ";
	videoSrc += videoSrc;

	if (_color == 1 || _color == 0)
		color = _color;

}

void VideoStatus::printStatus() const
{
	if (!text.empty())
		Status::printStatus();

	if (color == 0)
		cout << "Black & white Video\n\n";
	else 
		cout << "colourful Video\n\n";
	system(videoSrc.c_str());
}