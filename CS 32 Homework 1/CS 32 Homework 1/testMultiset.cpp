#include "Multiset.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	Multiset ulms;
	assert(ulms.insert(20));
	assert(ulms.insert(10));
	assert(ulms.insert(20));
	assert(ulms.insert(30));
	assert(ulms.insert(20));
	assert(ulms.insert(10));
	assert(ulms.insert(20));
	assert(ulms.insert(40));
	assert(ulms.size() == 8 && ulms.uniqueSize() == 4);
	assert(ulms.count(10) == 2);
	assert(ulms.count(20) == 4);
	assert(ulms.count(30) == 1);
	assert(ulms.count(40) == 1);
	assert(ulms.count(50) == 0);
}

int main()
{
	test();
	cout << "Passed all tests" << endl;
}