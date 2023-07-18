#include "TString.h"
#include "codeParse.h"

/* testtype string type handler */
TString::TString() { }

TString::TString(std::string _val) : val(_val) { }

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
    unsigned int i = 0;
    if(!codeParse::tryParseStringVal(input, i, this->val)) {
        return false;
    }
    this->val = this->val.substr(1, this->val.size()-2);
    return true;
}

std::ostream & operator<<(std::ostream& os, TString& t) {
    os << "\"" << t.val << "\"";
    return os;
}
