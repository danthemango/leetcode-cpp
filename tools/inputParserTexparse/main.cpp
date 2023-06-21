/*
    parse leetcode readmes
*/

#include "../../common/common.h"
#include "../../common/codeParse.h"


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
        //
        return true;
    } else if(tryParseIntVal(input, i, out_val)) {
        //
        return true;
    } else if(tryParseArrVal(input, i, out_val)) {
        // 
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

void readData(std::istream& in) {
    std::string line;
    while (std::getline(in, line)) {
        int exampleNum;
        std::map<std::string, std::string> valMap;
        std::string val;
        if(tryParseExample(line, exampleNum)) {
            cout << line << endl;
            cout << "example num: " << exampleNum << endl;
        } else if(tryParseInputLine(line, valMap)) {
            cout << "input ..." << endl;
        } else if(tryParseOutputLine(line, val)) {
            cout << "output..." << endl;
        }
    }
}

int main(int argc, char** argv) {
    std::ifstream ifile("readme.md");
    readData(ifile);
    return 0; // 

    // either open the file or use stdin as input
    if (argc > 1) {
        std::ifstream ifile(argv[1]);
        if (ifile) {
            readData(ifile);
        } else {
            cerr << "could not open file " << '"' << argv[1] << '"' << endl;
            return 1;
        }
    } else {
        readData(std::cin);
    }
}