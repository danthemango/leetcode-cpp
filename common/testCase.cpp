#include "testCase.h"
using namespace textParse;

/* a list of known argument input types which are converted to a class that handles it for test cases */
std::map<std::string,std::string> knownTypes {
    {"string", "TString"},
    {"int", "TInt"},
    {"bool", "TBool"},
    {"vector<int>", "TVectorInt"},
    {"Node*", "TNodePtr"},
    {"TreeNode*", "TTreeNode"},
    {"vector<string>", "TVectorString"},
    {"ListNode*", "TListNode"},
    {"uint32_t", "TInt"}, // <- not sure about this one
    {"vector<vector<int>>", "TVVInt"},
    {"vector<ListNode*>", "TVectorListNode"}
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
        std::cerr << "Error (testCase.cpp): could not parse type: " << inTypeString << endl;
        return false;
    }
    if(!isKnownType(varType)) {
        std::cerr << "Error (testCase.cpp): type not yet implemented: " << inTypeString << endl;
        return false;
    }
    out_testTypeString = knownTypes[varType.toString()];
    return true;
}

/*
    if the line has a string starts with the pattern 'Example n:'
    with an integer n, we will fill out_int with that value
    and returns true
*/
bool tryParseExample(const std::string& input, int& out_int) {
    unsigned int i = 0;
    if(!tryParseNextString(input, i, "Example") || !tryParseInt(input, i, out_int) || !tryParseNextChar(input, i, ':')) {
        return false;
    }
    return true;
}

// TODO: isdigit should only be used after the first char
bool isInputKeySymbol(const char& c) {
    return std::isupper(c) || std::islower(c) || c == '_' || std::isdigit(c);
}

bool tryParseInputKey(const std::string& input, unsigned int& i, std::string& out_key) {
    unsigned int resetI = i;
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

bool tryParseStringVal(const std::string& input, unsigned int& i, std::string& out_val) {
    unsigned int resetI = i;
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

bool tryParseNull(const std::string& input, unsigned int& i, std::string& out_val){
    int resetI = i;
    if(tryParseNextString(input, i, "null")) {
        out_val = "null";
        return true;
    } else {
        i = resetI;
        return false;
    }
}

bool tryParseBool(const std::string& input, unsigned int& i, std::string& out_val) {
    unsigned int resetI = i;
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

bool tryParseIntVal(const std::string& input, unsigned int& i, std::string& out_val) {
    int num;
    unsigned int resetI = i;
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
bool tryParseArrVal(const std::string& input, unsigned int& i, std::string& out_val) {

    unsigned int resetI = i;
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

bool tryParseVal(const std::string& input, unsigned int& i, std::string& out_val) {
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
bool tryParseInputKeyVal(const std::string& input, unsigned int& i, std::string& out_key, std::string& out_val) {
    unsigned int resetI = i;
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
bool tryParseInputLine(const std::string& input, unsigned int& i, std::map<std::string, std::string>& valMap) {

    unsigned int resetI = i;
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
    unsigned int i = 0;
    return tryParseInputLine(input, i, valMap);
}

bool tryParseOutputLine(const std::string& input, unsigned int& i, std::string& out_val) {
    unsigned int resetI = i;
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
    unsigned int i = 0;
    return tryParseOutputLine(input, i, out_val);
}

// returns true if input parameter was set
bool TestCase::hasInput(std::string key) {
    return input.find(key) != input.end();
}

std::ostream & operator<<(std::ostream& os, TestCase& t) {
    os << "Test case " << t.num << endl;
    for(const auto& pair : t.input) {
        os << "<- " << pair.first << ": " << pair.second << endl;
    }
    os << "-> " << t.expected << endl;
    return os;
}

// creates a list of testcases from input
std::vector<std::shared_ptr<TestCase>> getTestCases(std::shared_ptr<std::istream> in) {
    std::vector<std::shared_ptr<TestCase>> result;
    auto testCase = std::make_shared<TestCase>();
    std::string line;

    while (std::getline(*in, line)) {
        int num;

        if(tryParseExample(line, num)) {
            testCase = std::make_shared<TestCase>();
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
