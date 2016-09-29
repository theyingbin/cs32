#include "provided.h"
#include <string>
#include <vector>
using namespace std;

const size_t BITS_PER_UNSIGNED_SHORT = 16;

string convertNumberToBitString(unsigned short number);
bool convertBitStringToNumber(string bitString, unsigned short& number);

string BinaryConverter::encode(const vector<unsigned short>& numbers)
{
	string code = "";
	for (size_t i = 0; i < numbers.size(); i++){
		code += convertNumberToBitString(numbers[i]);
	}
	string realMessage = "";
	for (int i = 0; i < code.size(); i++){
		if (code[i] == '0'){
			realMessage += ' ';
		}
		else if (code[i] == '1'){
			realMessage += '\t';
		}
	}
	return realMessage;
}

bool BinaryConverter::decode(const string& bitString,
	vector<unsigned short>& numbers)
{
	if (bitString.size() % 16 != 0){
		return false;
	}
	for (int i = 0; i < bitString.size(); i++){
		if (bitString[i] != ' ' && bitString[i] != '\t')
			return false;
	}
	numbers.clear();
	string s = "";
	for (int i = 0; i < bitString.size(); i++){
		if (bitString[i] == ' ')
			s += '0';
		else
			s += '1';
	}
	for (int i = 0; i < s.size(); i += BITS_PER_UNSIGNED_SHORT){
		unsigned short temp;
		if (!convertBitStringToNumber(s.substr(i, BITS_PER_UNSIGNED_SHORT), temp) ){
			return false;
		}
		numbers.push_back(temp);
	}
	return true;
}

string convertNumberToBitString(unsigned short number)
{
	string result(BITS_PER_UNSIGNED_SHORT, '0');
	for (size_t k = BITS_PER_UNSIGNED_SHORT; number != 0; number /= 2)
	{
		k--;
		if (number % 2 == 1)
			result[k] = '1';
	}
	return result;
}

bool convertBitStringToNumber(string bitString, unsigned short& number)
{
	if (bitString.size() != BITS_PER_UNSIGNED_SHORT)
		return false;
	number = 0;
	for (size_t k = 0; k < bitString.size(); k++)
	{
		number *= 2;
		if (bitString[k] == '1')
			number++;
		else if (bitString[k] != '0')
			return false;
	}
	return true;
}
