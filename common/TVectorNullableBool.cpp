#include "TVectorNullableBool.h"
#include "textParse.h"
using textParse::tryParseNextChar;

TVectorNullableBool::TVectorNullableBool() { }

TVectorNullableBool::TVectorNullableBool(std::vector<NullableBool> _val) : val(_val) { }

std::vector<NullableBool>& TVectorNullableBool::get() {
    return this->val;
}

bool TVectorNullableBool::operator==(const std::vector<NullableBool>& other) {
    if(this->val.size() != other.size()) {
        return false;
    }
    for(unsigned int i = 0; i < this->val.size(); i++) {
        if(this->val[i] != other[i]) {
            return false;
        }
    }
    return true;
}

bool TVectorNullableBool::operator==(const TVectorNullableBool& other) {
    return *this == other.val;
}

bool TVectorNullableBool::tryParse(const std::string& input) {
    unsigned int i = 0;
    if(!tryParseNextChar(input, i, '[')) {
        return false;
    }
    bool first = true;
    while(i < input.size()) {
        if(tryParseNextChar(input, i, ']')) {
            return true;
        }

        if(first) {
            first = false;
        } else if(!tryParseNextChar(input, i, ',')) {
            return false;
        }

        NullableBool nb;
        if(!tryParseNullableBool(input, i, nb)) {
            return false;
        } else {
            this->val.push_back(nb);
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, TVectorNullableBool& t) {
    os << '[';
    bool first = true;
    for(const NullableBool& nb : t.val) {
        if(!first) {
            os << ',';
        } else {
            first = false;
        }
        os << nullableBool2string(nb);
    }
    os << ']';
    return os;
}