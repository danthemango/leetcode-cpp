#include "TString.h"
#include "codeParse.h"

/* testtype string type handler */
TString::TString() { }

TString::TString(bool _val) {
    val = _val;
}

std::string& TString::get() {
    return val;
}

bool TString::operator==(const std::string& other) {
    return this->val == other;
}

bool TString:: operator==(const TString& other) {
    return this->val == other.val;
}

bool TString::tryParse(const std::string& input) {
    int i = 0;
    return codeParse::tryParseStringVal(input, i, this->val);
}

std::ostream & operator<<(std::ostream& os, TString& t) {
    os << "\"" << t.val << "\"";
    return os;
}
