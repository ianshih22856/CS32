//Given two positive integers m and n such that m<n, the greatest common divisor of m and n is the
//same as the greatest common divisor of m and n-m.

//4, 10
#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool balanced(const string &exp)
{
    stack<char> chars;
    for (int i = 0; i < exp.size(); i++)
    {
        if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[')
            chars.push(exp[i]);
        if (exp[i] == ')' && chars.top() != '(')
            return false;
        if (exp[i] == '}' && chars.top() != '{') 
            return false;
        if (exp[i] == ']' && chars.top() != '[')
            return false;
        if (exp[i] == ')' || exp[i] == '}' || exp[i] == ']')
            chars.pop();
    }
    return true;
}

int main()
{
    string arr[5] = {"(2+4)*6", "[(2+4)*{15 - 20}]", "({12+30]]", "(({{[[<<<_*_>>>]]}}))", "(((( )))))))))))"};
    //bbnbn
    for (int i = 0; i < 5; i++)
    {
        if (balanced(arr[i]))
            cout << "balanced" << endl;
        else 
            cout << "not balanced" << endl;
    }
}