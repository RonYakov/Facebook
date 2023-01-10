#include <iostream>
#include "facebook.h"

using namespace std;
#pragma warning(disable: 4996)


void main()
{
	Facebook facebook; //ghghghg

	Status st1("Test 1"), st2("Test 1"), st3("Test 2");

	cout << "_________________________________________________________________\n";
	cout << "Hard coded test to opertor == and != of class status\n\n";
	if (st1 == st2)
	{
		cout << st1.gesStatus() << " is the same as " << st2.gesStatus() << endl;
	}
	if (st1 != st2)
	{
		cout << st1.gesStatus() << " is different than " << st2.gesStatus() << endl;
	}
	if (st1 == st3)
	{
		cout << st1.gesStatus() << " is the same as " << st3.gesStatus() << endl;
	}
	if (st1 != st3)
	{
		cout << st1.gesStatus() << " is different than " << st3.gesStatus() << endl;
	}
}