#ifndef MULTISET_INCLUDED
#define MULTISET_INCLUDED

#include <iostream>
#include <string>

typedef std::string ItemType;

class Multiset
{
public:
	Multiset();
	Multiset(const Multiset& copy);
	Multiset& operator=(const Multiset& other);
	~Multiset();
	bool empty() const;
	int size() const;
	int uniqueSize() const;
	bool insert(const ItemType& value);
	int erase(const ItemType& value);
	int eraseAll(const ItemType& value);
	bool contains(const ItemType& value) const;
	int count(const ItemType& value) const;
	int get(int i, ItemType& value) const;
	void swap(Multiset& other);
private:
	struct Node{
		ItemType value;
		int numItems; // Indicates how many repititions of this value are in the multiset
		Node* prev;   // Points to the Node that comes before the current one in a LinkedList
		Node* next;   // Points to the Node that comes after the current one in a LinkedList
	};
	Node* head;  // The head pointer of the LinkedList
	Node* tail;  // The tail pointer of the LinkedList
	int doErase(bool all, const ItemType& value);  // Helper function for erase and eraseAll
};

void subtract(const Multiset& ms1, const Multiset& ms2, Multiset& result);
void combine(const Multiset& ms1, const Multiset& ms2, Multiset& result);

#endif