#include <string>
#include <stack>
#include <iostream>
#include <cassert>

using namespace std;

bool isOperator(char c);
bool isOperand(char c);
bool precedence(char ch, char stackTop);
void toPostfix(string infix, string& postfix);
int toNum(char c);
bool checkValid(string infix);


int evaluate(string infix, const bool values[], string& postfix, bool& result)
{
	if (!checkValid(infix)){
		return 1;
	}
	toPostfix(infix, postfix);
	stack<bool> operands;
	bool special = false;
	for (int i = 0; i < postfix.size(); i++){
		if (isOperand(postfix[i])){
			bool currentOperand = values[toNum(postfix[i])];
			operands.push(currentOperand);
		}
		else if (postfix[i] == '!'){
			if (!operands.empty()){
				bool temp = operands.top();
				operands.pop();
				operands.push(!temp);
			}
		}
		else if (postfix[i] == '&'){
			bool v2 = operands.top();
			operands.pop();
			bool v1 = operands.top();
			operands.pop();
			operands.push( v1 && v2 );
		}
		else{                                     // Means postfix[i] == '|' 
			bool v2 = operands.top();
			operands.pop();
			bool v1 = operands.top();
			operands.pop();
			operands.push(v1 || v2);
		}
		result = operands.top();
	}
	return 0;
}

void toPostfix(string infix, string& postfix){
	stack<char> operators;
	postfix = "";
	for (int i = 0; i < infix.size(); i++){
		if (infix[i] == ' '){
			continue;
		}
		if (infix[i] >= '0' && infix[i] <= '9'){
			postfix += infix[i];
		}
		if (infix[i] == '('){
			operators.push(infix[i]);
		}
		if (infix[i] == ')'){
			while (!operators.empty()){
				char c = operators.top();
				operators.pop();
				if (c == '('){
					continue;
				}
				else{
					postfix += c;
				}
			}
		}
		if (isOperator(infix[i])){
			if (operators.empty()){
				operators.push(infix[i]);
			}
			else{
				while(!operators.empty() && precedence(infix[i], operators.top())){
					postfix += operators.top();
					operators.pop();
				}
				operators.push(infix[i]);
				continue;
			}
		}
	}
	while (!operators.empty()){
		postfix += operators.top();
		operators.pop();
	}
}

bool checkValid(string infix){
	if (infix.size() == 0){
		return false;
	}
	if (infix[0] == '|' || infix[0] == '&' || infix[0] == ')'){
		return false;
	}
	int counterOne = 0;				// Counter of char '('
	int counterTwo = 0;				// Counter of char ')'
	char lastChar = '\0';
	for (int i = 0; i < infix.size(); i++){
		// Skip spaces
		if (infix[i] == ' '){
			continue;
		}
		// after | or & or ( or ! there has to be digit, (, or !
		if (lastChar == '|' || lastChar == '&' || lastChar == '(' || lastChar == '!'){
			if (infix[i] != '(' && infix[i] != '!' && !isOperand(infix[i])){
				return false;
			}
		}
		// after ) or digit, there has to be & or | or )
		if (lastChar == ')' || isOperand(lastChar)){
			if (infix[i] != '&' && infix[i] != '|' && infix[i] != ')'){
				return false;
			}
		}
		if (infix[i] == '('){
			counterOne++;
		}
		if (infix[i] == ')'){
			counterTwo++;
		}
		// # of ) must never be greater than # of ( at any point in time
		if (counterTwo > counterOne){
			return false;
		}
		lastChar = infix[i];
	}
	// Last character must be either a number or )
	// Number of open and closed parenthesis must match
	if (lastChar != ')' && !isOperand(lastChar)){
		return false;
	}
	if (counterTwo != counterOne){
		return false;
	}
	return true;
}

bool isOperand(char c){
	if (c >= '0' && c <= '9')
		return true;
	return false;
}

bool isOperator(char c){
	if (c == '&' || c == '!' || c == '|'){
		return true;
	}
	return false;
}

int toNum(char c){
	switch (c){
	case '0':
		return 0;
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '4':
		return 4;
	case '5':
		return 5;
	case '6':
		return 6;
	case '7':
		return 7;
	case '8':
		return 8;
	case '9':
		return 9;
	}
	return -1;
}

bool precedence(char ch, char stackTop){
	if (stackTop == '!'){
		return true;
	}
	if (stackTop == '&'){
		if (ch == '!'){
			return false;
		}
		return true;
	}
	if (stackTop == '|'){
		if (ch == '!' || ch == '&'){
			return false;
		}
		return true;
	}
	return false;
}
