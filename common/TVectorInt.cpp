#include "TVectorInt.h"
#include "codeParse.h"

/* testcase vector type */
TVectorInt::TVectorInt() { }

TVectorInt::TVectorInt(std::vector<int> _val) : val(_val) { }

std::vector<int>& TVectorInt::get() {
    return val;
}

bool TVectorInt::operator==(const std::vector<int>& other) {
    if(val.size() != other.size()) {
        return false;
    }
    unsigned int i = 0;
    while(i < val.size() && i < other.size()) {
        if(val[i] != other[i]) {
            return false;
        }
        ++i;
    }
    return true;
}

bool TVectorInt::operator==(const TVectorInt& other) {
    return *this == other.val;
}

bool TVectorInt::tryParse(const std::string& input) {
    return codeParse::tryParseVectorInt(input, val);
}

std::ostream& operator<<(std::ostream& os, TVectorInt& t) {
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
    return os;
}
