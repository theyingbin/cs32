#include "Multiset.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
	Multiset first;
	assert(first.empty());
	assert(first.size() == 0);
	assert(first.insert("cumin"));
	assert(first.insert("turmeric"));
	assert(first.insert("cumin"));
	assert(first.insert("coriander"));
	assert(first.insert("cumin"));
	assert(first.insert("turmeric"));
	assert(first.size() == 6 && first.uniqueSize() == 3);
	assert(first.count("turmeric") == 2);
	assert(first.count("cumin") == 3);
	assert(first.count("coriander") == 1);
	assert(first.count("cardamom") == 0);

	Multiset second(first);
	Multiset third;
	assert(second.size() == 6 && second.uniqueSize() == 3);
	assert(second.count("turmeric") == 2);
	assert(second.count("cumin") == 3);
	assert(second.count("coriander") == 1);
	assert(second.count("cardamom") == 0);
	assert(second.erase("coriander"));
	assert(second.count("coriander") == 0);
	assert(second.eraseAll("turmeric") == 2);
	assert(!second.contains("turmeric"));
	assert(second.contains("cumin"));
	for (int i = 0; i < 3; i++)
	{
		assert(second.insert("cardamom"));
	}
	ItemType val;
	assert(second.get(0, val) == 3);
	assert(val == "cardamom");

	third = first;
	assert(third.size() == 6 && third.uniqueSize() == 3);
	assert(third.count("turmeric") == 2);
	assert(third.count("cumin") == 3);
	assert(third.count("coriander") == 1);
	assert(third.count("cardamom") == 0);

	assert(third.size() == 6 && third.uniqueSize() == 3);
	assert(third.count("turmeric") == 2);
	assert(third.count("cumin") == 3);
	assert(third.count("coriander") == 1);
	assert(third.count("cardamom") == 0);

	assert(second.count("turmeric") == 0);
	assert(second.count("cumin") == 3);
	assert(second.count("coriander") == 0);
	assert(second.count("cardamom") == 3);

	third.swap(second);

	assert(second.size() == 6 && second.uniqueSize() == 3);
	assert(second.count("turmeric") == 2);
	assert(second.count("cumin") == 3);
	assert(second.count("coriander") == 1);
	assert(second.count("cardamom") == 0);

	assert(third.count("turmeric") == 0);
	assert(third.count("cumin") == 3);
	assert(third.count("coriander") == 0);
	assert(third.count("cardamom") == 3);

	Multiset fourth;
	combine(second, third, fourth);
	assert(fourth.count("turmeric") == 2);
	assert(fourth.count("cumin") == 6);
	assert(fourth.count("coriander") == 1);
	assert(fourth.count("cardamom") == 3);

	combine(third, second, fourth);
	assert(fourth.count("turmeric") == 2);
	assert(fourth.count("cumin") == 6);
	assert(fourth.count("coriander") == 1);
	assert(fourth.count("cardamom") == 3);

	Multiset fifth;
	subtract(second, third, fifth);
	assert(fifth.count("turmeric") == 2);
	assert(fifth.count("cumin") == 0);
	assert(fifth.count("coriander") == 1);
	assert(fifth.count("cardamom") == 0);

	subtract(third, second, fifth);
	assert(fifth.count("turmeric") == 0);
	assert(fifth.count("cumin") == 0);
	assert(fifth.count("coriander") == 0);
	assert(fifth.count("cardamom") == 3);

	combine(second, third, second);
	assert(second.count("turmeric") == 2);
	assert(second.count("cumin") == 6);
	assert(second.count("coriander") == 1);
	assert(second.count("cardamom") == 3);

	combine(second, third, third);
	assert(third.count("turmeric") == 2);
	assert(third.count("cumin") == 9);
	assert(third.count("coriander") == 1);
	assert(third.count("cardamom") == 6);

	subtract(third, second, second);
	assert(second.count("turmeric") == 0);
	assert(second.count("cumin") == 3);
	assert(second.count("coriander") == 0);
	assert(second.count("cardamom") == 3);

	subtract(third, second, third);
	assert(third.count("turmeric") == 2);
	assert(third.count("cumin") == 6);
	assert(third.count("coriander") == 1);
	assert(third.count("cardamom") == 3);
}

int main()
{
	test();
	cout << "Passed all tests" << endl;
}