#include <string>
#include "NullableResult.h"
#include "textParse.h"
#include "codeParse.h"
using textParse::tryParseNextString;

NullableResult::NullableResult() : type(NRType::nrNull) { }
NullableResult::NullableResult(bool _bVal) : type(NRType::nrBool), bVal(_bVal) { }
NullableResult::NullableResult(int _iVal) : type(NRType::nrInt), iVal(_iVal) { }
NullableResult::NullableResult(std::string _sVal) : type(NRType::nrString), sVal(_sVal) { }

// returns a null value result
NullableResult NullableResult::getNull() { 
    NullableResult result;
    result.type = NRType::nrNull;
    return result;
}

bool NullableResult::tryParse(const std::string& input, unsigned int& i) {
    int resetI = i;
    if(textParse::tryParseNextString(input, i, "null")) {
        this->type = NRType::nrNull;
        return true;
    } else if(textParse::tryParseNextString(input, i, "true")) {
        this->type = NRType::nrBool;
        this->bVal = true;
        return true;
    } else if(textParse::tryParseNextString(input, i, "false")) {
        this->type = NRType::nrBool;
        this->bVal = false;
        return true;
    } else if(textParse::tryParseNextInt(input, i, this->iVal)) {
        this->type = NRType::nrInt;
        return true;
    } else if(codeParse::tryParseNextStringValContent(input, i, this->sVal)) {
        this->type = NRType::nrString;
        return true;
    } else {
        i = resetI;
        return false;
    }
}

std::string NullableResult::toString() const {
    if(this->type == NRType::nrNull) {
        return "null";
    } else if(this->type == NRType::nrBool && this->bVal == true) {
        return "true";
    } else if(this->type == NRType::nrBool && this->bVal == false) {
        return "false";
    } else if(this->type == NRType::nrInt) {
        return std::to_string(this->iVal);
    } else if(this->type == NRType::nrString) {
        std::string result;
        result.push_back('"');
        result.append(this->sVal);
        result.push_back('"');
        return result;
    } else {
        throw "unexpected NullableResult type";
    }
}

std::ostream& operator<<(std::ostream& os, NullableResult& nr) {
    os << nr.toString();
    return os;
}

bool NullableResult::operator==(const NullableResult& other) const {
    if(this->type == NRType::nrNull && other.type == NRType::nrNull) {
        return true;
    } else if(this->type != other.type) {
        return false;
    } else if(this->type == NRType::nrBool) {
        return this->bVal == other.bVal;
    } else if(this->type == NRType::nrInt) {
        return this->iVal == other.iVal;
    } else if(this->type == NRType::nrString) {
        return this->sVal == other.sVal;
    } else {
        return false;
    }
}

bool NullableResult::operator!=(const NullableResult& other) const {
    return !(*this == other);
}