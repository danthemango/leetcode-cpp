#ifndef TESTCASE_H
#define TESTCASE_H

#include "common.h"
#include "codeParse.h"
#include <iostream>

/*
    returns true if the given type is known    
*/
bool isKnownType(const codeParse::VarType& varType);

/*
    accepts a type string as input and 
    returns true if it is a recognized type
    and fills the out with the corresponding testCase type as a string
*/
bool tryParseTestType(const std::string& inTypeString, std::string& out_testTypeString);

/*
    if the line has a string starts with the pattern 'Example n:'
    with an integer n, we will fill out_int with that value
    and returns true
*/
bool tryParseExample(const std::string& input, int& out_int);

// TODO: isdigit should only be used after the first char
bool isInputKeySymbol(const char& c);

bool tryParseInputKey(const std::string& input, int& i, std::string& out_key);

bool tryParseStringVal(const std::string& input, int& i, std::string& out_val);

bool tryParseNull(const std::string& input, int& i, std::string& out_val);

bool tryParseBool(const std::string& input, int& i, std::string& out_val);

bool tryParseIntVal(const std::string& input, int& i, std::string& out_val);

/*
    returns true if we have an array of values
*/
bool tryParseArrVal(const std::string& input, int& i, std::string& out_val);

bool tryParseVal(const std::string& input, int& i, std::string& out_val);

/**
 * returns true if we could fetch one key-value pair from input
*/
bool tryParseInputKeyVal(const std::string& input, int& i, std::string& out_key, std::string& out_val);

// returns true if the string starts with 'Input:'
// updating i to the end of the pattern
bool tryParseInputLine(const std::string& input, int& i, std::map<std::string, std::string>& valMap);

bool tryParseInputLine(const std::string& input, std::map<std::string, std::string>& valMap);

bool tryParseOutputLine(const std::string& input, int& i, std::string& out_val);

bool tryParseOutputLine(const std::string& input, std::string& out_val);

class TestCase {
    public:
    int num;
    std::map<std::string, std::string> input;
    std::string expected;

    // returns true if input parameter was set
    bool hasInput(std::string key);

    friend ostream & operator<<(ostream& os, TestCase& t);
};

// creates a list of testcases from input
std::vector<std::shared_ptr<TestCase>> getTestCases(std::shared_ptr<std::istream> in);

std::shared_ptr<std::istream> getStream(int argc, char** argv);

std::shared_ptr<std::istream> getStream(const std::string& filename);

#endif // TESTCASE_H
