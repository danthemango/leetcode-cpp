#include "../../TVVInt.h"
#include <vector>
#include <string>
#include <iostream>

// returns true if parsing the result was possible
bool canParse(std::string val) {
    TVVInt result;
    if(!result.tryParse(val)) {
        std::cerr << "could not parse: \"" << val << "\"" << std::endl;
        return false;
    } else {
        std::cout << result << std::endl;
        return true;
    }
}

int main() {
    // create a list of values to parse, and exit if any fail
    std::vector<std::string> vals {
        "[]",
        "[[]]",
        "[[1]]",
        "[[1,2]]",
        "[[1,2],[]]",
        "[[1,2],[3,4]]",
        "[[1,2, 3,4]]"
    };

    for(const std::string& val : vals) {
        if(!canParse(val)) {
            return 1;
        }
    }
    return 0;
}