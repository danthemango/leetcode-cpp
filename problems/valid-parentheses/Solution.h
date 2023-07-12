#include "../../common/common.h"
#include <stack>

class Solution {
public:
    // returns a matching parenthesis
    char getMatching(char c) {
        switch(c) {
            case '[':
                return ']';
            case '(':
                return ')';
            case '{':
                return '}';
            case ']':
                return '[';
            case ')':
                return '(';
            case '}':
                return '{';
        }
        return ' '; // err
    }

    // check if the char is opening parenthesis
    bool isOpening(char c) {
        return c == '(' || c == '[' || c == '{';
    }
    bool isClosing(char c) {
        return c == ')' || c == ']' || c == '}';
    }

    bool isValid(string s) {
        std::stack<char> found;
        for(const char& c : s) {
            if(isClosing(c)) {
                char opening_c = getMatching(c);
                if(found.size() == 0) {
                    // nothing in the stack
                    return false;
                } else {
                    char curr = found.top();
                    found.pop();
                    if(curr != opening_c) {
                        // non-matching paranthesis found 
                        return false;
                    }
                }
            } else if(isOpening(c)) {
                // put opening parenthesis on stack
                found.push(c);
            } else {
                // invalid symbol found
                throw "invalid symbol";
            }
        }

        // if the stack isn't empty, we have extraneous symbols
        return found.size() == 0;
    }
};
