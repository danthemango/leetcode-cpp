#include "../../common/common.h"
#include <stack>

class Solution {
public:
    // returns token char if found, else returns ' '
    char getOperator(const std::string& token) {
        if(token.size() != 1) {
            return ' ';
        }

        const char& c = token[0];
        switch(c) {
            case '+':            
            case '-':
            case '/':
            case '*':
                return c;
                break;
            default:
                return ' ';
                break;
        }
    }

    int evalRPN(vector<string>& tokens) {
        std::stack<int> theStack;
        for(const std::string& token : tokens) {
            char op = getOperator(token);
            if(op != ' ') {
                if(theStack.size() < 2) {
                    throw "not enough values in stack";
                }
                int second = theStack.top();
                theStack.pop();
                int first = theStack.top();
                theStack.pop();
                int result;
                
                switch(op) {
                    case '+':
                        result = first + second;
                        break;
                    case '-':
                        result = first - second;
                        break;
                    case '/':
                        result = first / second;
                        break;
                    case '*':
                        result = first * second;
                        break;
                }
                theStack.push(result);
            } else {
                int val = std::atoi(token.c_str());
                theStack.push(val);
            }
        }

        if(theStack.size() != 1) {
            throw "invalid expression";
        } else {
            int result = theStack.top();
            theStack.pop();
            return result;
        }
    }
};