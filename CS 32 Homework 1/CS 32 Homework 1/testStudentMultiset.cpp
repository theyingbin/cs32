#include "StudentMultiset.h"
#include <string>
#include <iostream>
#include <cassert>

using namespace std;

void test()
{
	StudentMultiset x;
	x.add(50);
	x.add(50);
	x.add(40);
	x.add(30);
	x.add(30);
	x.add(30);
	x.add(60);
	assert(x.size() == 7);
	x.print();
}
int main()
{
	test();
	cout << "Passed all tests" << endl;
}