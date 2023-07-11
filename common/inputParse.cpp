#include "inputParse.h"

InputParser::InputParser(std::string _input) {
    i = 0;
    input = _input;
}

/* saves current position temporarily */
int InputParser::pos() {
    return i;
}

/* recovers saved position */
void InputParser::recover(int _i) {
    i = _i;
}

/* returns the current char, or a space if we are at the end of input */
char InputParser::get() {
    if(i < input.size()) {
        return input[i];
    } else {
        return ' ';
    }
}

/* increments the input position */
char InputParser::operator++() {
    char c = get();
    ++i;
    return c;
}

/*
    returns true if we are at the end of the input
*/
bool InputParser::atEnd() {
    return i >= input.size();
}

bool InputParser::isSpace() {
    if(i >= input.size()) {
        return false;
    }
    switch(input[i]) {
        case ' ':
        case '\n':
        case '\r':
        case '\t':
            return true;
            break;
        default:
            break;
    }
    return false;
}

bool InputParser::skipSpace() {
    bool foundSpace = false;
    while(isSpace()) {
        foundSpace = true;
        ++i;
    }
    return foundSpace;
}

/*
    returns true if the input has char c at the current position
*/
bool InputParser::tryParseChar(const char& c) {
    int _i = pos();
    if(i >= input.size() || input[i] != c) {
        recover(_i);
        return false;
    }
    ++i;
    return true;
}

bool InputParser::tryParseNextChar(const char& c) {
    int _i = pos();
    skipSpace();
    if(!tryParseChar(c)) {
        recover(_i);
        return false;
    }
    return true;
}

/* returns true if the given string is in the input */
bool InputParser::tryParseString(const std::string& s) {
    if(s.size() > input.size()-i) {
        return false;
    }

    unsigned int _i = i;
    unsigned int j = 0;

    while(j < s.size() && _i < input.size()) {
        if(s[j] != input[_i]) {
            return false;
        }

        ++j;
        ++_i;
    }

    i = _i;
    return true;
}

bool InputParser::tryParseNextString(const std::string& s) {
    int _i = pos();
    skipSpace();
    if(!tryParseString(s)) {
        recover(_i);
        return false;
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, InputParser inputParser) {
    os << inputParser.input;
    return os;
}
