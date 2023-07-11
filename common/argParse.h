#ifndef ARGPARSE_H
#define ARGPARSE_H

#include "common.h"

/*
    describe the usage of the program
*/
class ArgParse {
    private:
    int argc;
    char** argv;

    public:
    ArgParse(int _argc, char** _argv);

    // returns true if the string exists somewhere in the command-line arguments list
    bool hasArg(const std::string arg) const;

    // tries to fetch an argument from argv, in the format '<specifier> <value>'
    // for example '-i <file>' will fill <file> as the out <value>
    bool tryParseArg(const std::string& specifier, std::string& out_value);

    // tries to fetch files with the format '-i <infile> -o <outfile>'
    // (sort of like ffmpeg)
    bool tryParseIOFiles(std::ifstream& infile, std::ofstream& outfile);

    bool hasHelp() const;
};

#endif // ARGPARSE_H
