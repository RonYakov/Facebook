#include"status.h"


Status::Status(const string _text,time_t _time) : text(_text)
{
	if (_time == 0)
		time(&uploadTime);
	else
		uploadTime = _time;
}


void Status::printStatus()const
{
	cout << ctime(&uploadTime);
	cout << "Black & white text color\n";
	cout << "------------------------\n";
	cout << text << endl;
	cout << "\n";
}

void Status::saveToFile(ofstream& facebookFile)
{
	facebookFile << "T" << text <<endl;
	facebookFile << ctime(&uploadTime) << endl;

}