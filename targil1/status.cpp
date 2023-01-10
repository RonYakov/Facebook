#include"status.h"
using namespace std;

Status::Status(const string _text) : text(_text)
{
	time(&uploadTime);
}

void Status::printStatus()const
{
	cout << ctime(&uploadTime);
	cout << "Black & white text color\n";
	cout << "------------------------\n";
	cout << text << endl;
	cout << "\n";
}