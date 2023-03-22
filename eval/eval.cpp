#include "Set.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;
int InfixToPostfix(const string infix, string& postfix, stack<char> operatorStack);
void evaluatePostfix(const string postfix, stack<char> operandStack, char& finalresult, const Set& trueValues, const Set& falseValues);
int evaluate(string infix, const Set& trueValues, const Set& falseValues, string& postfix, bool& result)
{
    stack<char> characterStack;
    if (InfixToPostfix(infix, postfix, characterStack) == 1)
        return 1;
    for (int i = 0; i < infix.size(); i++)
    {
        char inf = infix[i];
        if (isalpha(inf))
        {
            if (!trueValues.contains(inf) && !falseValues.contains(inf))
                return 2;
            if (trueValues.contains(inf) && falseValues.contains(inf))
                return 3;
        }
    }
    char temp;
    evaluatePostfix(postfix, characterStack, temp, trueValues, falseValues);
    if (temp == '1')
        return 1;
    if (trueValues.contains(temp))
    {
        result = true;
    }
    else if (falseValues.contains(temp))
    {
        result = false;
    }
    return 0;
}
int InfixToPostfix(const string infix, string& postfix, stack<char> operatorStack)
{
    postfix = "";
    while (!operatorStack.empty())
        operatorStack.pop();
    for (int i = 0; i < infix.size(); i++)
    {
        char ch = infix[i];
        switch(ch)
        {
            case '(':
                operatorStack.push(ch);
                break;
            case ')':
                if (i == 0 || infix[i - 1] == '(')
                    return 1;
                while (operatorStack.top() != '(')
                {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.pop();
                break;
            case '&': case '|': case '!':
                if (i == 0)
                    return 1;
                while (!operatorStack.empty() && operatorStack.top() != '(')     
                {
                    if (ch <= operatorStack.top())
                        break;
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                if (infix[i - 1] == '(')
                    return 1;
                operatorStack.push(ch);
                break;
            default:
                if (islower(ch))
                {
                    postfix += ch;
                    break;  
                }
                else if (ch == ' ')
                    break;
                else if(!isalpha(ch) || isupper(ch))
                    return 1;
                break;
        }
    }
    while (!operatorStack.empty())
    {
        postfix += operatorStack.top();
        operatorStack.pop();
    }
    return 0;
}
void evaluatePostfix(const string postfix, stack<char> operandStack, char& finalresult, const Set& trueValues, const Set& falseValues)
{
    if (postfix.size() < 1)
    {
        finalresult = '1';
        return;
    }
    if (postfix.size() == 1)
    {
        if (falseValues.contains(postfix[0]))
            falseValues.get(0,finalresult);
        else
            trueValues.get(0,finalresult);
        return;
    }
    while (!operandStack.empty())
        operandStack.pop();
    for (int i = 0; i < postfix.size(); i++)
    {
        char ch = postfix[i];
        if (islower(ch))
            operandStack.push(ch);
        else
        {
            char result;
            if (ch == '!')
            {
                char operand = operandStack.top();
                operandStack.pop();
                if (trueValues.contains(operand))
                    falseValues.get(0,result);
                else
                    trueValues.get(0,result);
            }
            else
            {
                char operand2 = operandStack.top();
                operandStack.pop();
                if (operandStack.empty())
                {
                    finalresult = '1';
                    return;
                }
                char operand1 = operandStack.top();
                operandStack.pop();
                if (ch == '&')
                {
                    if (trueValues.contains(operand1) && trueValues.contains(operand2))
                        trueValues.get(0,result);
                    else
                        falseValues.get(0,result);
                }
                else if (ch == '|')
                {
                    if (falseValues.contains(operand1) && falseValues.contains(operand2))
                        falseValues.get(0,result);
                    else
                        trueValues.get(0,result);
                }
                        
            }
            operandStack.push(result);
        }
    }
    finalresult = operandStack.top();
    operandStack.pop();
    if (!operandStack.empty())
    {
        finalresult = '1';
        return;
    }
}