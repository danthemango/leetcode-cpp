#include <vector>
#include <string>
#include "TVectorString.h"
#include "textParse.h"

TVectorString::TVectorString() { }
TVectorString::TVectorString(std::vector<std::string> _val) : val(_val) {}

bool TVectorString::operator==(TVectorString& other) {

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

std::vector<std::string>& TVectorString::get() {
    return this->val;
}

// returns true if there was a quote-delimited string value in input at pos i
// updating i to the char after a successful parse
// updating out_val with the string contents
bool TVectorString::tryParseStringValue(const std::string& input, int& i, std::string& out_val) {
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
        } else if(!textParse::isSpace(c)) {
            // found a non-string value before the start of the string
            // it is something other than a string value
            return false;
        }

        ++i;
    }
    return false;
}

bool TVectorString::tryParse(const std::string& input) {
    int i = 0;
    if(!textParse::tryParseNextChar(input, i, '[')) {
        return false;
    }
    bool inString = false;
    bool isFirst = true;

    while(i < input.size()) {
        if(textParse::tryParseNextChar(input, i, ']')) {
            return true;
        }

        if(!isFirst) {
            if(!textParse::tryParseNextChar(input, i, ',')) {
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

std::ostream& operator<<(std::ostream& os, TVectorString& t) {
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

