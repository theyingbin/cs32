#include "provided.h"
#include <string>
#include <vector>
#include "HashTable.h"
using namespace std;

// Helper functions
template<typename KeyType>
unsigned int computeHash(KeyType key);

unsigned int computeHash(string s){
	unsigned int total = 0;
	for (int i = 0; i < s.size(); i++){
		total = total + (i + 1) * s[i];
	}
	return total;
}

unsigned int computeHash(unsigned short s){
	return static_cast<unsigned int>(s);
}

void Compressor::compress(const string& s, vector<unsigned short>& numbers)
{
	unsigned int cap = s.size() / 2 + 512;
	if (cap > 16384){
		cap = 16384;
	}
	unsigned int buckets = 2 * cap;				// Max load factor must be 0.5
	HashTable<string, unsigned short> hasher(buckets, cap);

	for (unsigned short j = 0; j <= 255; j++){
		string s(1, static_cast<char>(j));
		hasher.set(s, j, true);
	}

	unsigned short nextFreeID = 256;
	string runSoFar = "";
	numbers.clear();
	for (int i = 0; i < s.size(); i++){
		string curChar(1, s[i]);
		string expandedRun = runSoFar + curChar;
		unsigned short x;
		if (hasher.get(expandedRun, x)){
			runSoFar = expandedRun;
			continue;
		}
		hasher.get(runSoFar, x);
		numbers.push_back(x);
		if (x > 255){
			hasher.touch(runSoFar);			// Touch handles whether or not runSoFar maps to a permanent item
		}
		runSoFar = "";
		unsigned short cv;
		hasher.get(curChar, cv);
		numbers.push_back(cv);
		if (!hasher.isFull()){
			hasher.set(expandedRun, nextFreeID);
			nextFreeID++;
		}
		else{
			unsigned short temp;
			string tempS;
			hasher.discard(tempS, temp);
			hasher.set(expandedRun, temp);
		}
	}
	if (runSoFar.size() != 0){
		unsigned short x;
		hasher.get(runSoFar, x);
		numbers.push_back(x);
	}
	numbers.push_back(cap);
}

bool Compressor::decompress(const vector<unsigned short>& numbers, string& s)
{
	if (numbers.size() == 0){
		return false;
	}
	int cap = numbers[numbers.size() - 1];
	int buckets = 2 * cap;
	HashTable<unsigned short, string> hasher(buckets, cap);
	for (unsigned short j = 0; j < 256; j++){
		string st(1, static_cast<char>(j));
		hasher.set(j, st, true);
	}
	unsigned short nextFreeID = 256;
	string runSoFar = "";
	s = "";
	for (int i = 0; i < numbers.size() - 1; i++){
		unsigned short us = numbers[i];
		if (us <= 255){
			string temp;
			hasher.get(us, temp);
			s += temp;
			if (runSoFar.size() == 0){
				runSoFar = temp;
				continue;
			}
			else{
				string expandedRun = runSoFar + temp;
				if (!hasher.isFull()){
					hasher.set(nextFreeID, expandedRun);
					nextFreeID++;
				}
				else{
					string dummy;
					unsigned short dummyTwo;
					hasher.discard(dummyTwo, dummy);
					hasher.set(dummyTwo, expandedRun);
				}
				runSoFar = "";
				continue;
			}
		}
		else{
			string association;
			if (!hasher.get(us, association)){
				return false;
			}
			else{
				hasher.touch(us);
				s += association;
				runSoFar = association;
				continue;
			}
		}
	}
	return true;
}
