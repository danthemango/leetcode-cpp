#include "../../TVectorInt.h"
#include <vector>
#include <string>

// returns true if parsing the result was possible
bool canParse(std::string val) {
    TVectorInt result;
    if(!result.tryParse(val)) {
        std::cerr << "could not parse" << std::endl;
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
        "[1]",
        "[1,2,3]"
    };

    for(const std::string& val : vals) {
        if(!canParse(val)) {
            return 1;
        }
    }
    return 0;
}