#include "TVVInt.h"
#include "textParse.h"
#include "codeParse.h"
#include <string>
#include <iostream>

TVVInt::TVVInt() { }

TVVInt::TVVInt(std::vector<std::vector<int>> _val) : val(_val) { }

std::vector<std::vector<int>>& TVVInt::get() {
    return val;
}

bool TVVInt::operator==(const std::vector<std::vector<int>>& other) {
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

bool TVVInt::operator==(const TVVInt &other) {
    return *this == other.val;
}

bool TVVInt::tryParse(const std::string &input) {
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

        std::vector<int> subArr;
        if(!textParse::tryParseVectorInt(input, i, subArr)) {
            return false;
        }
        this->val.push_back(subArr);
    }
    return false;
}

std::string vectorInt2String(std::vector<int> arr) {
    std::string result;
    result.push_back('[');
    bool first = true;
    for(const int& num : arr) {
        if(!first) {
            result.push_back(',');
        } else {
            first = false;
        }
        result.append(std::to_string(num));
    }
    result.push_back(']');
    return result;
}

std::string vectorVectorInt2String(std::vector<std::vector<int>> arrArr) {
    std::string result;
    result.push_back('[');
    bool first = true;
    for(const auto& subArr : arrArr) {
        if(!first) {
            result.push_back(',');
        } else {
            first = false;
        }
        result.append(vectorInt2String(subArr));
    }
    result.push_back(']');
    return result;
}

std::ostream &operator<<(std::ostream &os, TVVInt &t) {
    os << vectorVectorInt2String(t.val);
    return os;
}