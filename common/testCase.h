#ifndef TESTCASE_H
#define TESTCASE_H

#include "common.h"
#include "codeParse.h"
#include <iostream>


    /* a list of known argument input types which are converted to a class that handles it for test cases */
    std::map<std::string,std::string> knownTypes {
        {"string", "TString"},
        {"int", "TInt"},
        {"bool", "TBool"},
        {"vector<int>", "TVectorInt"},
        {"Node*", "TNodePtr"},
        {"vector<string>", "TVectorString"}
    };

    /*
        returns true if the given type is known    
    */
    bool isKnownType(const codeParse::VarType& varType) {
        return knownTypes.find(varType.toString()) != knownTypes.end();
    }

    /*
        accepts a type string as input and 
        returns true if it is a recognized type
        and fills the out with the corresponding testCase type as a string
    */
    bool tryParseTestType(const std::string& inTypeString, std::string& out_testTypeString) {
        codeParse::VarType varType;
        if(!varType.tryParse(inTypeString)) {
            std::cerr << "Error (testCase.h): could not parse type: " << inTypeString << endl;
            return false;
        }
        if(!isKnownType(varType)) {
            std::cerr << "Error (testCase.h): type not yet implemented: " << inTypeString << endl;
            return false;
        }
        out_testTypeString = knownTypes[varType.toString()];
        return true;
    }

bool tryParseVal(const std::string& input, int& i, std::string& out_val);

/*
    open the readme file
    check if it starts with 'Example n:', or 'Input:', or 'Output:'
    if it does, create a new test runner object and add it to the list
*/

/*
    if the line has a string starts with the pattern 'Example n:'
    with an integer n, we will fill out_int with that value
    and returns true
*/
bool tryParseExample(const std::string& input, int& out_int) {
    int i = 0;
    if(!tryParseNextString(input, i, "Example") || !tryParseInt(input, i, out_int) || !tryParseNextChar(input, i, ':')) {
        return false;
    }
}

bool isInputKeySymbol(const char& c) {
    return std::isupper(c) || std::islower(c) || c == '_';
}

bool tryParseInputKey(const std::string& input, int& i, std::string& out_key) {
    int resetI = i;
    skipSpace(input, i);
    std::string key;
    while(i < input.size() && isInputKeySymbol(input[i])) {
        key.push_back(input[i]);
        i++;
    }

    if(key.size() == 0) {
        i = resetI;
        return false;
    } else {
        out_key = key;
        return true;
    }
}

bool tryParseStringVal(const std::string& input, int& i, std::string& out_val) {
    int resetI = i;
    if(!tryParseNextChar(input, i, '"')) {
        i = resetI;
        return false;        
    }

    out_val = "\"";
    while(i < input.size()) {
        if(tryParseChar(input, i, '"')) {
            out_val.push_back('"');
            return true;
        } else if(tryParseString(input, i, "\\\"")) {
            out_val.append("\\\"");
        } else {
            out_val.push_back(input[i]);
            ++i;
        }
    }
    out_val = "";
    i = resetI;
    return false;
}

bool tryParseNull(const std::string& input, int& i, std::string& out_val){
    int resetI = i;
    if(tryParseNextString(input, i, "null")) {
        out_val = "null";
        return true;
    } else {
        i = resetI;
        return false;
    }
}

bool tryParseBool(const std::string& input, int& i, std::string& out_val) {
    int resetI = i;
    if(tryParseNextString(input, i, "true")) {
        out_val = "true";
        return true;
    } else if(tryParseNextString(input, i, "false")) {
        out_val = "false";
        return true;
    } else {
        i = resetI;
        return false;
    }
}

bool tryParseIntVal(const std::string& input, int& i, std::string& out_val) {
    int num;
    int resetI = i;
    if(!tryParseInt(input, i, num)) {
        i = resetI;
        return false;
    }
    out_val = to_string(num);
    return true;
}

/*
    returns true if we have an array of values
*/
bool tryParseArrVal(const std::string& input, int& i, std::string& out_val) {

    int resetI = i;
    if(!tryParseNextChar(input, i, '[')) {
        i = resetI;
        return false;
    }

    std::vector<std::string> vals;

    bool first = true;
    while(i < input.size()) {
        if(!first) {
            if(!tryParseNextChar(input, i, ',')) {
                break;
            }
        } else {
            first = false;
        }

        std::string val;
        if(!tryParseVal(input, i, val)) {
            break;
        } else {
            vals.push_back(val);
        }
    }

    if(!tryParseNextChar(input, i, ']')) {
        i = resetI;
        return false;
    } else {
        out_val.append("[");
        bool first = true;
        for(const auto& val : vals) {
            if(!first) {
                out_val.push_back(',');
            } else {
                first = false;
            }
            out_val.append(val);
        }
        out_val.append("]");
        return true;
    }
}

bool tryParseVal(const std::string& input, int& i, std::string& out_val) {
    int resetI = i;

    if(tryParseStringVal(input, i, out_val)) {
        return true;
    } else if(tryParseIntVal(input, i, out_val)) {
        return true;
    } else if(tryParseArrVal(input, i, out_val)) {
        return true;
    } else if(tryParseNull(input, i, out_val)) {
        return true;
    } else if(tryParseBool(input, i, out_val)) {
        return true;
    } else {
        i = resetI;
        return false;
    }
}

/**
 * returns true if we could fetch one key-value pair from input
*/
bool tryParseInputKeyVal(const std::string& input, int& i, std::string& out_key, std::string& out_val) {
    int resetI = i;
    if(!tryParseInputKey(input, i, out_key) || !tryParseNextChar(input, i, '=')) {
        i = resetI;
        return false;
    }

    if(!tryParseVal(input, i, out_val)) {
        i = resetI;
        return false;
    }

    return true;
}

// returns true if the string starts with 'Input:'
// updating i to the end of the pattern
bool tryParseInputLine(const std::string& input, int& i, std::map<std::string, std::string>& valMap) {

    int resetI = i;
    if(!tryParseNextString(input, i, "Input: ")) {
        i = resetI;
        return false;
    }

    bool first = true;
    while(i < input.size()) {
        if(!first) {
            // expect a new value after a comma
            if(!tryParseNextChar(input, i, ',')) {
                return true;
            }
        } else {
            first = false;
        }

        std::string val;
        std::string key;
        if(tryParseInputKeyVal(input, i, key, val)) {
            valMap[key] = val;
        } else {
            break;
        }
    }
    return true;
}

bool tryParseInputLine(const std::string& input, std::map<std::string, std::string>& valMap) {
    int i = 0;
    return tryParseInputLine(input, i, valMap);
}

bool tryParseOutputLine(const std::string& input, int& i, std::string& out_val) {
    int resetI = i;
    if(!tryParseNextString(input, i, "Output: ")) {
        i = resetI;
        return false;
    }

    if(!tryParseVal(input, i, out_val)) {
        i = resetI;
        return false;
    }

    return true;
}

bool tryParseOutputLine(const std::string& input, std::string& out_val) {
    int i = 0;
    return tryParseOutputLine(input, i, out_val);
}

class TestCase {
    public:
    int num;
    std::map<std::string, std::string> input;
    std::string expected;

    friend ostream & operator<<(ostream& os, TestCase& t);
};

ostream& operator<<(ostream& os, TestCase& testCase) {
    os << "Test case " << testCase.num << endl;
    for(const auto& pair : testCase.input) {
        os << "<- " << pair.first << ": " << pair.second << endl;
    }
    os << "-> " << testCase.expected << endl;
}

// creates a list of testcases from input
std::vector<std::shared_ptr<TestCase>> getTestCases(std::shared_ptr<std::istream> in) {
    std::vector<std::shared_ptr<TestCase>> result;
    std::shared_ptr<TestCase> testCase;
    std::string line;

    while (std::getline(*in, line)) {
        int num;
        if(tryParseExample(line, num)) {
            testCase = std::shared_ptr<TestCase> (new TestCase());
            testCase->num = num;
            result.push_back(testCase);
        }

        tryParseInputLine(line, testCase->input);
        tryParseOutputLine(line, testCase->expected);
    }
    return result;
}

std::shared_ptr<std::istream> getStream(int argc, char** argv) {
    // either open the file or use stdin as input
    std::shared_ptr<std::istream> ifile = std::shared_ptr<std::ifstream> (new std::ifstream(argv[1]));
    if (argc > 1) {
        if (ifile) {
            return ifile;
        } else {
            throw "could not open file";
        }
    } else {
        ifile = std::shared_ptr<std::istream> (&std::cin);
        return ifile;
    }
}

std::shared_ptr<std::istream> getStream(const std::string& filename) {
    return std::shared_ptr<std::ifstream> (new std::ifstream(filename));
}

/*
    Test Case types
*/

/*
    testcase int type
*/
class TInt {
    public:
    int val;
    int get() {
        return val;
    }

    bool tryParse(const std::string& input) {
        return tryParseInt(input, val);
    }

    bool operator==(const TInt& other) {
        return this->val == other.val;
    }

    friend ostream & operator<<(ostream& os, TInt& t) {
        os << t.val;
        return os;
    }
};

class TVectorString {
    public:
    std::vector<std::string> val;
    TVectorString() { }
    TVectorString(std::vector<std::string> _val) : val(_val) {}

    bool operator==(TVectorString& other) {

        if(val.size() != other.val.size()) {
            return false;
        }

        for(int i = 0; i < val.size(); i++) {
            if(val[i] != other.val[i]) {
                return false;
            }
        }
        return true;
    }

    // returns true if there was a quote-delimited string value in input at pos i
    // updating i to the char after a successful parse
    // updating out_val with the string contents
    bool tryParseStringValue(const std::string& input, int& i, std::string& out_val) {

        bool inString = false;

        std::string result;
        while(true) {
            if(i >= input.size()) {
                return false;
            }
            
            char c = input[i];

            if(inString) {
                if(c == '"') {
                    out_val = result;
                    ++i;
                    return true;
                } else {
                    result.push_back(c);
                }
            } else if(c == '"') {
                inString = true;
            } else if(!isSpace(c)) {
                // found a non-string value before the start of the string
                // it is something other than a string value
                return false;
            }

            ++i;
        }
        return false;
    }

    bool tryParse(const std::string& input) {
        int i = 0;
        if(!tryParseNextChar(input, i, '[')) {
            return false;
        }
        bool inString = false;
        bool isFirst = true;

        while(i < input.size()) {
            if(tryParseNextChar(input, i, ']')) {
                return true;
            }

            if(!isFirst) {
                if(!tryParseNextChar(input, i, ',')) {
                    return false;
                }
            } else {
                isFirst = false;
            }

            std::string nextVal;
            if(!tryParseStringValue(input, i, nextVal)) {
                return false;
            }
            val.push_back(nextVal);
        }
        return false;
    }

    friend std::ostream & operator<<(std::ostream& os, TVectorString& t) {
        os << '[';
        bool first = true;
        for(const std::string& val : t.val) {
            if(!first) {
                os << ',';
            } else {
                first = false;
            }
            os << '"';
            os << val;
            os << '"';
        }
        os << ']';
        return os;
    }
};

/*
    testcase vector type
*/
class TVectorInt {
    public:
    std::vector<int> val;

    TVectorInt() { }

    TVectorInt(std::vector<int> _val) {
        val = _val;
    }

    std::vector<int>& get() {
        return val;
    }

    bool operator==(const vector<int>& other) {
        if(val.size() != other.size()) {
            return false;
        }
        int i = 0;
        while(i < val.size() && i < other.size()) {
            if(val[i] != other[i]) {
                return false;
            }
            ++i;
        }
        return true;
    }

    bool operator==(const TVectorInt& other) {
        return *this == other.val;
    }

    bool tryParse(const std::string& input) {
        return textParse::tryParseVectorInt(input, val);
    }

    friend ostream & operator<<(ostream& os, TVectorInt& t) {
        os << '[';
        bool first = true;
        for(const int& num : t.val) {
            if(!first) {
                os << ',';
            } else {
                first = false;
            }
            os << num;
        }
        os << ']';
    }
};

/* testtype boolean handler */
class TBool {
    public:
    bool val;

    TBool() { }

    TBool(bool _val) {
        val = _val;
    }

    bool& get() {
        return val;
    }

    bool operator==(const bool& other) {
        return this->val == other;
    }

    bool operator==(const TBool& other) {
        return this->val == other.val;
    }

    bool tryParse(const std::string& input) {
        int i = 0;
        if(textParse::tryParseNextString(input, i, "true")) {
            this->val = true;
            return true;
        } else if(textParse::tryParseNextString(input, i, "false")) {
            this->val = false;
            return true;
        } else {
            return false;
        }
    }

    friend ostream & operator<<(ostream& os, TBool& t) {
        if(t.val == true) {
            os << "true";
        } else {
            os << "false";
        }
        return os;
    }
};

/* testtype string type handler */
class TString {
    public:
    std::string val;

    TString() { }

    TString(bool _val) {
        val = _val;
    }

    std::string& get() {
        return val;
    }

    bool operator==(const std::string& other) {
        return this->val == other;
    }

    bool operator==(const TString& other) {
        return this->val == other.val;
    }

    bool tryParse(const std::string& input) {
        int i = 0;
        return tryParseStringVal(input, i, this->val);
        
    }

    friend ostream & operator<<(ostream& os, TString& t) {
        os << "\"" << t.val << "\"";
        return os;
    }
};

#endif // TESTCASE_H
