#include <string>
#include "NullableBool.h"
#include "textParse.h"
using textParse::tryParseNextString;

std::string nullableBool2string(NullableBool nb) {
    if(nb == NullableBool::nbTrue) {
        return "true";
    } else if(nb == NullableBool::nbFalse) {
        return "false";
    } else if(nb == NullableBool::nbNull) {
        return "null";
    } else {
        throw "nullableBool2string not found";
    }
}

// tries to parse a nullable boolean value,
// returning true if possible
// filling out_nb with the value
bool tryParseNullableBool(const std::string& input, unsigned int& i, NullableBool& out_nb) {
    unsigned int resetI = i;
    if(tryParseNextString(input, i, "true")) {
        out_nb = NullableBool::nbTrue;
        return true;
    } else if(tryParseNextString(input, i, "false")) {
        out_nb = NullableBool::nbFalse;
        return true;
    } else if(tryParseNextString(input, i, "null")) {
        out_nb = NullableBool::nbNull;
        return true;
    } else {
        i = resetI;
        return false;
    }
}