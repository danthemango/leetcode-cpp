#ifndef INPUTPARSE_H
#define INPUTPARSE_H

#include <string>
#include <iostream>

/* wrapper around a string which parses input */
class InputParser {
    public:
    // input string
    std::string input;
    // current position in parsing input
    unsigned int i;
    // saved position
    int tmpI;

    InputParser(std::string _input);

    /* saves current position temporarily */
    int pos();

    /* recovers saved position */
    void recover(int _i);

    /* returns the current char, or a space if we are at the end of input */
    char get();

    /* increments the input position */
    char operator++();

    /*
        returns true if we are at the end of the input
    */
    bool atEnd();

    bool isSpace();

    bool skipSpace();

    /*
        returns true if the input has char c at the current position
    */
    bool tryParseChar(const char& c);

    bool tryParseNextChar(const char& c);

    /* returns true if the given string is in the input */
    bool tryParseString(const std::string& s);

    bool tryParseNextString(const std::string& s);

    friend std::ostream& operator<<(std::ostream& os, InputParser inputParser);
};

#endif // INPUTPARSE_H
