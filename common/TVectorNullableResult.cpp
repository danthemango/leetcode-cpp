#include "TVectorNullableResult.h"
#include "textParse.h"
using textParse::tryParseNextChar;

TVectorNullableResult::TVectorNullableResult() { }

TVectorNullableResult::TVectorNullableResult(std::vector<NullableResult> _val) : val(_val) { }

std::vector<NullableResult>& TVectorNullableResult::get() {
    return this->val;
}

bool TVectorNullableResult::operator==(const std::vector<NullableResult>& other) const {
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

bool TVectorNullableResult::operator==(const TVectorNullableResult& other) const {
    return *this == other.val;
}

bool TVectorNullableResult::tryParse(const std::string& input) {
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

        NullableResult nr;
        if(!nr.tryParse(input, i)) {
            return false;
        } else {
            this->val.push_back(nr);
        }
    }
    return false;
}

std::ostream& operator<<(std::ostream& os, TVectorNullableResult& t) {
    os << '[';
    bool first = true;
    for(const NullableResult& nr : t.val) {
        if(!first) {
            os << ',';
        } else {
            first = false;
        }
        os << nr.toString();
    }
    os << ']';
    return os;
}