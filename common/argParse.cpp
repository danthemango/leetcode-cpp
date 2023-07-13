#include "argParse.h"

/*
    describe the usage of the program
*/
ArgParse::ArgParse(int _argc, char** _argv) : argc(_argc), argv(_argv) {
}

// returns true if the string exists somewhere in the command-line arguments list
bool ArgParse::hasArg(const std::string arg) const {
    for(int i = 1; i < argc; ++i) {
        std::string thisArg(argv[i]);
        if(thisArg == arg) {
            return true;
        }
    }
    return false;
}

// tries to fetch an argument from argv, in the format '<specifier> <value>'
// for example '-i <file>' will fill <file> as the out <value>
bool ArgParse::tryParseArg(const std::string& specifier, std::string& out_value) {
    for(int i = 1; i < argc; i++) {
        std::string thisArg(argv[i]);
        if(thisArg == specifier) {
            if(i+1 >= argc) {
                return false;
            } else {
                out_value = argv[i+1];
                return true;
            }
        }
    }
    return false;
}

bool ArgParse::tryParseIOFileNames(std::string& inFileName, std::string& outFileName) {
    if(!this->tryParseArg("-i", inFileName)) {
        std::cerr << "could not find input filename" << endl;
        return false;
    }
    if(!this->tryParseArg("-o", outFileName)) {
        std::cerr << "could not find output filename" << endl;
        return false;
    }
    return true;
}

// tries to fetch files with the format '-i <infile> -o <outfile>'
// (sort of like ffmpeg)
bool ArgParse::tryParseIOFiles(std::ifstream& infile, std::ofstream& outfile) {
    std::string inFilename;
    std::string outFilename;
    if(!this->tryParseArg("-i", inFilename)) {
        std::cerr << "could not find input filename" << endl;
        return false;
    }
    if(!this->tryParseArg("-o", outFilename)) {
        std::cerr << "could not find output filename" << endl;
        return false;
    }
    infile.open(inFilename);
    if(!infile.is_open()) {
        std::cerr << "could not open infile" << endl;
        return false;
    }
    outfile.open(outFilename);
    if(!outfile.is_open()) {
        std::cerr << "could not open outfile" << endl;
        return false;
    }
    return true;
}

bool ArgParse::hasHelp() const {
    return hasArg("--help") || hasArg("-h");
}
