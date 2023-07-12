#include "TBool.h"
#include "textParse.h"
#include <iostream>

TBool::TBool() { }

TBool::TBool(bool _val) {
    val = _val;
}

bool& TBool::get() {
    return val;
}

bool TBool::operator==(const bool& other) {
    return this->val == other;
}

bool TBool::operator==(const TBool& other) {
    return this->val == other.val;
}

bool TBool::tryParse(const std::string& input) {
    unsigned int i = 0;
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

std::ostream& operator<<(std::ostream& os, TBool& t) {
    if(t.val == true) {
        os << "true";
    } else {
        os << "false";
    }
    return os;
}
