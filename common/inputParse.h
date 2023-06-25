#ifndef INPUTPARSE_H
#define INPUTPARSE_H

#include "common.h"

/* wrapper around a string which parses input */
class InputParser {
    public:
    // input string
    std::string input;
    // current position in parsing input
    int i;
    // saved position
    int tmpI;


    InputParser(std::string _input) {
        i = 0;
        input = _input;
    }

    /* saves current position temporarily */
    int pos() {
        return i;
    }

    /* recovers saved position */
    void recover(int _i) {
        i = _i;
    }

    /* returns the current char, or a space if we are at the end of input */
    char get() {
        if(i < input.size()) {
            return input[i];
        } else {
            return ' ';
        }
    }

    /* increments the input position */
    char operator++() {
        char c = get();
        ++i;
        return c;
    }

    /*
        returns true if we are at the end of the input
    */
    bool atEnd() {
        return i >= input.size();
    }

    bool isSpace() {
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

    bool skipSpace() {
        while(isSpace()) {
            ++i;
        }
    }

    /*
        returns true if the input has char c at the current position
    */
    bool tryParseChar(const char& c) {
        int _i = pos();
        if(i >= input.size() || input[i] != c) {
            recover(_i);
            return false;
        }
        ++i;
        return true;
    }

    bool tryParseNextChar(const char& c) {
        int _i = pos();
        skipSpace();
        if(!tryParseChar(c)) {
            recover(_i);
            return false;
        }
        return true;
    }

    /* returns true if the given string is in the input */
    bool tryParseString(const std::string& s) {
        if(s.size() > input.size()-i) {
            return false;
        }

        int _i = i;
        int j = 0;

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

    bool tryParseNextString(const std::string& s) {
        int _i = pos();
        skipSpace();
        if(!tryParseString(s)) {
            recover(_i);
            return false;
        }
        return true;
    }

    friend ostream& operator<<(std::ostream& os, InputParser inputParser) {
        os << inputParser.input;
        return os;
    }

};



#endif // INPUTPARSE_H
