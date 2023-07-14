#include "TVVString.h"
#include "textParse.h"
#include "codeParse.h"
#include <string>
#include <iostream>

TVVString::TVVString() { }

TVVString::TVVString(std::vector<std::vector<std::string>> _val) : val(_val) { }

std::vector<std::vector<std::string>>& TVVString::get() {
    return val;
}

bool TVVString::operator==(const std::vector<std::vector<std::string>>& other) {
    if(this->val.size() != other.size()) {
        return false;
    }
    for(unsigned int i = 0; i < this->val.size(); i++) {
        const auto& mySubArr = this->val[i];
        const auto& otherSubArr = other[i];
        if(mySubArr.size() != otherSubArr.size()) {
            return false;
        }
        for(unsigned int j = 0; j < mySubArr.size(); j++) {
            const auto& myVal = mySubArr[j];
            const auto& otherVal = otherSubArr[j];
            if(myVal != otherVal) {
                return false;
            }
        }
    }
    return true;
}

bool TVVString::operator==(const TVVString &other) {
    return *this == other.val;
}

bool TVVString::tryParse(const std::string &input) {
    unsigned int i = 0;

    if(!textParse::tryParseNextChar(input, i, '[')) {
        return false;
    }

    bool first = true;
    this->val.clear();
    while(i < input.size()) {
        if(textParse::tryParseNextChar(input, i, ']')) {
            return true;
        }
        if(first) {
            first = false;
        } else if(!textParse::tryParseNextChar(input, i, ',')){
            return false;
        }

        std::vector<std::string> subArr;
        if(!codeParse::tryParseVectorString(input, i, subArr)) {
            return false;
        }
        this->val.push_back(subArr);
    }
    return false;
}

std::string vectorString2String(std::vector<std::string> arr) {
    std::string result;
    result.push_back('[');
    bool first = true;
    for(const std::string& str : arr) {
        if(!first) {
            result.push_back(',');
        } else {
            first = false;
        }
        result.push_back('"');
        result.append(str);
        result.push_back('"');
    }
    result.push_back(']');
    return result;
}

std::string vectorVectorString2String(std::vector<std::vector<std::string>> arrArr) {
    std::string result;
    result.push_back('[');
    bool first = true;
    for(const auto& subArr : arrArr) {
        if(!first) {
            result.push_back(',');
        } else {
            first = false;
        }
        result.append(vectorString2String(subArr));
    }
    result.push_back(']');
    return result;
}

std::ostream &operator<<(std::ostream &os, TVVString &t) {
    os << vectorVectorString2String(t.val);
    return os;
}
