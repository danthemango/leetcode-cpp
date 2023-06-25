#include "../../argParse.h"
#include "../../common.h"

int main(int argc, char** argv) {
    ArgParse argParse(argc, argv);
    std::ifstream infile;
    std::ofstream outfile;
    if(argParse.hasHelp()) {
        std::cout << "usage: -i <infile> -o <outfile>" << endl;
        return 0;
    } else if(!argParse.tryParseIOFiles(infile, outfile)) {
        return 1;
    }
    std::string line;
    while(std::getline(infile, line)) {
        outfile << line;
        outfile << '\n';
    }
    infile.close();
    outfile.close();
    std::cout << "Success." << endl;
    return 0;
}
