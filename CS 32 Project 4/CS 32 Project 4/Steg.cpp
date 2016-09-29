#include "provided.h"
#include <string>
#include <vector>
using namespace std;

bool Steg::hide(const string& hostIn, const string& msg, string& hostOut) 
{
	if (hostIn.size() == 0){
		return false;
	}
	string runSoFar = "";
	vector<string> hold;
	for (int i = 0; i < hostIn.size(); i++){
		if (hostIn[i] == '\n'){
			hold.push_back(runSoFar);
			runSoFar = "";
			continue;
		}
		else if (hostIn[i] == '\r' && hostIn[i + 1] == '\n'){
			hold.push_back(runSoFar);
			runSoFar = "";
			i++;
			continue;
		}
		else{
			runSoFar += hostIn[i];
		}
	}
	if (runSoFar.size() != 0){
		hold.push_back(runSoFar);
		runSoFar = "";
	}
	for (int i = 0; i < hold.size(); i++){
		if (hold[i].size() == 0){
			continue;
		}
		string temp = hold[i];
		while (temp.size() > 0){
			if (temp[temp.size() - 1] == ' ' || temp[temp.size() - 1] == '\t'){
				temp = temp.substr(0, temp.size() - 1);
			}
			else{
				break;
			}
		}
		hold[i] = temp;
	}
	vector<unsigned short> nums;
	Compressor::compress(msg, nums);
	string spaceAndTab = BinaryConverter::encode(nums);
	int numLines = hold.size();
	int numLongLength = spaceAndTab.size() % numLines;
	int longLength = spaceAndTab.size() / numLines + 1;
	int shortLength = spaceAndTab.size() / numLines;
	for (int i = 0; i < hold.size(); i++){
		if (i < numLongLength){
			hold[i] += spaceAndTab.substr(0, longLength);
			spaceAndTab = spaceAndTab.substr(longLength);
			continue;
		}
		else{
			hold[i] += spaceAndTab.substr(0, shortLength);
			spaceAndTab = spaceAndTab.substr(shortLength);
		}
	}
	hostOut = "";
	for (int i = 0; i < hold.size(); i++){
		hostOut = hostOut + hold[i] + "\n";
	}
	return true;
}

bool Steg::reveal(const string& hostIn, string& msg) 
{
	string runSoFar = "";
	vector<string> hold;
	for (int i = 0; i < hostIn.size(); i++){
		if (hostIn[i] == '\n'){
			hold.push_back(runSoFar);
			runSoFar = "";
			continue;
		}
		else if (hostIn[i] == '\r' && hostIn[i + 1] == '\n'){
			hold.push_back(runSoFar);
			runSoFar = "";
			i++;
			continue;
		}
		else{
			runSoFar += hostIn[i];
		}
	}
	if (runSoFar.size() != 0){
		hold.push_back(runSoFar);
		runSoFar = "";
	}
	string total = "";
	for (int i = 0; i < hold.size(); i++){
		string temp = "";
		string& ref = hold[i];
		while (ref.size() > 0){
			if (ref[ref.size() - 1] == ' ' || ref[ref.size() - 1] == '\t'){
				temp = ref[ref.size() - 1] + temp;
				ref = ref.substr(0, ref.size() - 1);
			}
			else{
				break;
			}
		}
		total += temp;
	}
	vector<unsigned short> nums;
	if (!BinaryConverter::decode(total, nums)){
		return false;								// Encountered Error
	}
	if (!Compressor::decompress(nums, msg)){
		return false;								// Encountered Error
	}
	return true;
}
