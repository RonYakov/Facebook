#include"status.h"
using namespace std;

Status::Status(const string _text) : text(_text)
{
	time(&uploadTime);
}

Status::Status(const Status& stat)
{
	setText(stat.text);
	uploadTime = stat.uploadTime;
}

void Status::setText(const string _text)
{
	text = _text;
}

void Status::printStatus()const
{
	cout << ctime(&uploadTime);
	cout << "------------------------\n";
	cout << text << endl;
}