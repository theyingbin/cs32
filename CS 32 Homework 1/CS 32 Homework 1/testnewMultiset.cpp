#include "newMultiset.h"
#include <string>
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	Multiset sms;
	assert(sms.insert("cumin"));
	assert(sms.insert("turmeric"));
	assert(sms.insert("turmeric"));
	assert(sms.insert("cumin"));
	assert(sms.insert("coriander"));
	assert(sms.insert("cumin"));
	assert(sms.insert("turmeric"));
	assert(sms.insert("cardamom"));
	assert(sms.size() == 8 && sms.uniqueSize() == 4);
	assert(sms.count("turmeric") == 3);
	assert(sms.count("cumin") == 3);
	assert(sms.count("coriander") == 1);
	assert(sms.count("cardamom") == 1);
	assert(sms.count("cardamom!!!!!") == 0);
	Multiset x(50);
}

int main()
{
	test();
	cout << "Passed all tests" << endl;
}