/*
    accept a readme file as argument,
    and print all testcases therein
*/

#include "../../common/common.h"
#include "../../common/ArgParse.h"
#include "../../common/testCase.h"
#include <fstream>

int main(int argc, char** argv) {
    ArgParse argParse(argc, argv);
    std::string readmeFilename;
    if(!argParse.tryParseArg("-i", readmeFilename)) {
        std::cout << "usage: -i <readme.md>" << std::endl;
    }
    std::shared_ptr<std::ifstream> readmeFile = make_shared<std::ifstream>();
    readmeFile->open(readmeFilename);
    if(!readmeFile->is_open()) {
        std::cerr << "could not open: '" << readmeFilename << "'" << std::endl;
        return 1;
    }
    auto testCases = getTestCases(readmeFile);
    for(const auto& testCase : testCases) {
        std::cout << *testCase << std::endl;
    }
}