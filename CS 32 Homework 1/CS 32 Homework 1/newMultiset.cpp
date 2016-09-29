#include "newMultiset.h"

Multiset::Multiset(){
	m_maxSize = DEFAULT_MAX_ITEMS;
	m_items = new Item[DEFAULT_MAX_ITEMS];
	m_uniqueSize = 0;
}

Multiset::Multiset(int size){
	m_maxSize=size;
	m_items = new Item[size];
	m_uniqueSize = 0;
}

Multiset::Multiset(const Multiset& other){
	m_uniqueSize = other.m_uniqueSize;
	m_maxSize = other.m_maxSize;
	m_items = new Item[other.m_maxSize];
	for (int i = 0; i < other.m_uniqueSize; i++){
		m_items[i] = other.m_items[i];
	}
}

Multiset& Multiset::operator=(const Multiset& other){
	m_maxSize = other.m_maxSize;
	m_uniqueSize = other.m_uniqueSize;
	delete[] m_items;
	m_items = new Item[other.m_maxSize];
	for (int i = 0; i < other.m_uniqueSize; i++){
		m_items[i] = other.m_items[i];
	}
	return (*this);
}

Multiset::~Multiset(){
	delete[] m_items;
}

bool Multiset::empty() const{
	return m_uniqueSize == 0;
}

int Multiset::size() const{
	int size = 0;
	for (int i = 0; i < m_uniqueSize; i++){
		size += m_items[i].count;
	}
	return size;
}

int Multiset::uniqueSize() const{
	return m_uniqueSize;
}

bool Multiset::insert(const ItemType& value){
	for (int i = 0; i < m_uniqueSize; i++){
		if (m_items[i].object == value){
			m_items[i].count++;
			return true;
		}
	}
	if (m_uniqueSize == m_maxSize){
		return false;
	}
	m_items[m_uniqueSize].object = value;
	m_items[m_uniqueSize].count = 1;
	m_uniqueSize++;
	return true;
}

int Multiset::erase(const ItemType& value){
	for (int i = 0; i < m_uniqueSize; i++){
		if (m_items[i].object == value){
			m_items[i].count--;
			if (m_items[i].count == 0){
				m_items[i] = m_items[m_uniqueSize - 1];
				m_uniqueSize--;
			}
			return 1;
		}
	}
	return 0;
}

int Multiset::eraseAll(const ItemType& value){
	int numErased = 0;
	for (int i = 0; i < m_uniqueSize; i++){
		if (m_items[i].object == value){
			numErased = m_items[i].count;
			m_items[i] = m_items[m_uniqueSize - 1];
			m_uniqueSize--;
		}
	}
	return numErased;
}

bool Multiset::contains(const ItemType& value) const{
	for (int i = 0; i < m_uniqueSize; i++){
		if (m_items[i].object == value){
			return true;
		}
	}
	return false;
}

int Multiset::count(const ItemType& value) const{
	for (int i = 0; i < m_uniqueSize; i++){
		if (m_items[i].object == value){
			return m_items[i].count;
		}
	}
	return 0;
}

int Multiset::get(int i, ItemType& value) const{
	if (i < 0 || i >= m_uniqueSize){
		return 0;
	}
	value = m_items[i].object;
	return m_items[i].count;
}

void Multiset::swap(Multiset& other){
	Multiset temp = *this;
	*this = other;
	other = temp;
}