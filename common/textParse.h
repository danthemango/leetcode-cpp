#ifndef TEXTPARSE_H
#define TEXTPARSE_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

/*
    textparse.h
    responsible for simple text parsing functions
*/

namespace textParse {
    int getDigit(char c);

    // TODO parse all whitespace
    bool isSpace(char c);

    // returns true if c is the char in input at i
    // incrementing i if found
    bool tryParseChar(const std::string& input, unsigned int& i, const char& c);

    // increments i until a non-whitespace is found
    bool skipSpace(std::string input, unsigned int& i);

    // returns true if 'c' is the next non-whitespace character in input,
    // after position i
    // updating i if found
    bool tryParseNextChar(const std::string& input, unsigned int& i, char c);

    // returns true if we found string 'str' at index i of input
    // updating i to the next index after the last char in input found
    bool tryParseString(const std::string& input, unsigned int& i, const std::string& str);

    // try parsing a string skipping any spaces
    // setting i to the next char after successful parse
    bool tryParseNextString(const std::string& input, unsigned int& i, const std::string& str);

    // try parsing a sequence of strings ignoring whitespace
    // setting i to the next char after successful parse
    bool tryParseNextStrings(const std::string& input, unsigned int& i, const std::vector<std::string>& strList);

    // returns true if an int can be found at position i of input string
    // and returns the value in out_int
    // and increments i to the char after the pattern
    bool tryParseInt(const std::string& input, unsigned int& i, int& out_int);

    bool tryParseInt(const std::string& input, int& out_int);

    bool tryParseNextInt(const std::string& input, unsigned int& i, int& out_int);

    // fetches all stdin input and returns it as a string
    // (for quick development, not space efficient)
    std::string stdin2String();

    // returns the file contents as a string
    std::string file2String(std::ifstream& ifile);

    // returns all contents of a file to a string
    bool tryGetFileContents(const std::string& filename, std::string& out_contents);

    std::string vectorInt2String(std::vector<int> arr);
    std::string vectorString2string(std::vector<std::string> inputStringList);
    std::string vectorVectorInt2String(std::vector<std::vector<int>> arrArr);
}

#endif // TEXTPARSE_H