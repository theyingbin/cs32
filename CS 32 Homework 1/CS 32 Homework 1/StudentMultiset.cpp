#include "StudentMultiset.h"
#include <iostream>

StudentMultiset::StudentMultiset(){
	// Default constuct a Multiset
	return;
}

bool StudentMultiset::add(unsigned long id){
	return items.insert(id);
}

int StudentMultiset::size() const{
	return items.size();
}

void StudentMultiset::print() const{
	for (int i = 0; i < items.uniqueSize(); i++){
		unsigned long temp;
		int n = items.get(i, temp);
		for (int i = 0; i < n; i++){
			std::cout << temp << std::endl;
		}
	}
}