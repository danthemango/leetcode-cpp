#include "TInt.h"
#include <iostream>
#include <string>
#include <ostream>
#include "textParse.h"
// #include "codeParse.h"

TInt::TInt() { }
TInt::TInt(int _val) : val(_val) { }

int& TInt::get() {
    return val;
}

bool TInt::tryParse(const std::string& input) {
    return textParse::tryParseInt(input, val);
}

bool TInt::operator==(const TInt& other) {
    return this->val == other.val;
}

std::ostream & operator<<(std::ostream& os, TInt& t) {
    os << t.val;
    return os;
}
