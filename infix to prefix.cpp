// infix to postfix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include"stackarray.h"
#include<sstream>
using namespace std;
string tobereturn;
bool flag = false;
void higherpriority(char value,stackarray<char>& object, stackarray<string>& );
void samepriority(char value,stackarray<char>& object, stackarray<string>& );
void lowerpriority(char value,stackarray<char>& object, stackarray<string>&);
string prefix(string&);
int evaluationofprefix();
int main()
{
	string input;
	getline(cin, input, '\n');
	tobereturn=prefix(input);
	cout << tobereturn<<endl;
	cout <<evaluationofprefix();
}
string prefix(string& input)
{
	stackarray<char> object;
	stackarray<string>operands;
	for (size_t i = 0; i < input.length(); i++)
	{
		if (isalpha(input[i]) || isdigit(input[i]))
		{
			operands.push(string{input[i]});
		}
		else if (input[i] == '*' || input[i] == '+' || input[i] == '-' || input[i] == '/' || input[i] == '(')
		{
			if (object.empty())
			{
				object.push(input[i]);
			}
			else if (input[i] == '(')
				object.push(input[i]);
			else
				lowerpriority(input[i], object,operands);
		}
		else if (input[i] == ')')
		{
			if (!object.empty())
			{

				while (object.top() != '(')
				{
					string left, right, tobepush;
					right = operands.top(); operands.pop();
					left = operands.top(); operands.pop();
					tobepush = string{ object.top() } + left + right;
					operands.push(tobepush);
					object.pop();
				}
				object.pop();
			}
		}

	}
	while (!object.empty())
	{
		string left, right, tobepush;
		right = operands.top(); operands.pop();
		left = operands.top(); operands.pop();
		tobepush = string{object.top() } + left + right;
		operands.push(tobepush);
		object.pop();
	}
	return operands.top();
}
int evaluationofprefix()
{
	stackarray<string>obj;
	for (int i =tobereturn.length()-1; i >=0; i--)
	{
		if (isdigit(tobereturn[i]))
			obj.push(string{tobereturn[i]});
		else if (tobereturn[i] == '+')
		{
			int value1 = stoi(obj.top(), nullptr, 10);
			obj.pop();
			int value2 = stoi(obj.top(), nullptr, 10);
			obj.pop();
			value1 = value1 + value2;
			obj.push(std::to_string(value1));
		}
		else if (tobereturn[i] == '-')
		{
			int value1 = stoi(obj.top(), nullptr, 10);
			obj.pop();
			int value2 = stoi(obj.top(), nullptr, 10);
			obj.pop();
			value1 = value1 - value2;
			obj.push(std::to_string(value1));
		}
		else if (tobereturn[i] == '*')
		{
			int value1 = stoi(obj.top(), nullptr, 10);
			obj.pop();
			int value2 = stoi(obj.top(), nullptr, 10);
			obj.pop();
			value1 = value1 * value2;
			obj.push(std::to_string(value1));
		}
		else if (tobereturn[i] == '/')
		{
			int value1 = stoi(obj.top(), nullptr, 10);
			obj.pop();
			int value2 = stoi(obj.top(), nullptr, 10);
			obj.pop();
			value1 = value1 / value2;
			obj.push(std::to_string(value1));
		}
	}
	return  stoi(obj.top(), nullptr, 10);
}
void higherpriority(char value, stackarray<char>& object,stackarray<string>&operands)
{
	while (flag != true)
	{
		string left, right, tobepush;
		right = operands.top(); operands.pop();
		left = operands.top(); operands.pop();
		tobepush = string{object.top() } + left + right;
		operands.push(tobepush);
		object.pop();
		lowerpriority(value, object,operands);
	}
}
void samepriority(char value, stackarray<char>& object, stackarray<string>& operands)
{
	string left, right,tobepush;
	right = operands.top(); operands.pop();
	left= operands.top(); operands.pop();
	tobepush = string{ object.top() } + left + right; object.pop();
	operands.push(tobepush);
	object.push(value);
	flag = true;
}
void lowerpriority(char value, stackarray<char>& object, stackarray<string>& operands)
{
	flag = false;
	if (value == object.top())
		samepriority(value, object, operands);
	else if (object.top() == '(')
	{
		object.push(value);
		flag = true;
	}
	else if (value == '*' &&  object.top()=='/')
		samepriority(value, object, operands);
	else if (value == '/' && object.top()=='*')
	{
		samepriority(value, object, operands);
		
    }
	else if (value == '+' && object.top()=='-')
		samepriority(value, object,operands);
	else if (value == '-' && object.top() == '+')
	{
		samepriority(value, object, operands);
	}
	
	else if (value == '*' && '*' < object.top())
	{
		object.push('*');
		flag = true;
	}
	else if (value == '/' && '/' > object.top())
	{
		object.push('/');
		flag = true;
	}
	else
	{
		higherpriority(value, object,operands);
	}
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
