#include "StudentMultiset.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	StudentMultiset sms;
	sms.add(1);
	sms.add(1);
	sms.add(2);
	sms.add(3);
	sms.add(3);
	sms.add(3);
	assert(sms.size() == 6 );
	sms.print();
}
/*
int main()
{
	test();
	cout << "Passed all tests" << endl;
}
*/