/*
    adds the header guards based on header filename.
    e.g. if the filename is 'header.h' then add
        #ifndef HEADER_H
        #define HEADER_H
        ...
        #endif // HEADER_H
    to the top and bottom of the file
*/

#include <cstdio>
#include "common.h"
using namespace std;
using namespace textParse;

/*
    returns true if symbol may be part of a headerFilename or a directory
    note: needs to be updated, but we will accept any alphanumeric symbols 
    underscores or dots for now
*/
bool isFileChar(const char & c) {
    return std::isalnum(c) || c == '_' || c == '.';
}

/*
    returns true if we found a sequence of symbols which may be a file or directory name
    a headerFilename is 1 or more fileChar characters
    updating i on a successful parse
*/
bool tryParseFilename(const std::string input, int& i, std::string& out_headerFilename) {
    std::string headerFilename;
    int resetI = i;
    while(i < input.size() && isFileChar(input[i])) {
        headerFilename.push_back(input[i]);
        i++;
    }

    if(headerFilename.size() == 0) {
        i = resetI;
        return false;
    } else {
        out_headerFilename = headerFilename;
        return true;
    }
}

// returns true if the input ends with the pattern
bool endsWith(const std::string& input, const std::string& pattern) {
    if(pattern.size() == 0) {
        return true;
    }
    int i = input.size() - 1;
    int j = pattern.size() - 1;
    while(i >= 0 && j >= 0) {
        if(input[i] != pattern[j]) {
            return false;
        }
        --i;
        --j;
    }
    return true;
}

/*
    returns true on successfully parsing a header headerFilename,
    filling its headerPath and headerFilename parts
    expected input value: header.h or header.hpp
*/
bool tryParseHeaderPath(const std::string input, int& i, std::string& out_headerPath, std::string& out_headerFilename) {
    int resetI = i;
    std::string headerPath;
    std::string headerFilename;

    while(tryParseFilename(input, i, headerFilename)) {
        if(tryParseChar(input, i, '/')) {
            headerPath.append(headerFilename);
            headerPath.push_back('/');
            headerFilename = "";
        }
    }

    if(headerFilename.size() == 0 || !endsWith(headerFilename, ".h")) {
        i = resetI;
        return false;
    } else {
        out_headerPath = headerPath;
        out_headerFilename = headerFilename;
        return true;
    }
}

// accepts a headerFilename and returns a parsed header name
// for ifndef statement
// i.e. "header.h" -> "HEADER_H"
std::string getParsedHeaderName(std::string headerFilename) {
    std::string headerName;
    int i = 0;
    while(headerFilename[i] != '\0') {
        char c = headerFilename[i];
        if(std::islower(c)) {
            headerName.push_back(c - 'a' + 'A');
        } else if(c == '.') {
            headerName.push_back('_');
        } else {
            headerName.push_back(c);
        }
        i++;
    }
    return headerName;
}

void modifyFile() {
    std::string headerFilename = ".tmp";
    ofstream ofile;
    ofile.open(headerFilename);
    if(!ofile.is_open()) {
        cout << "could not open file for writing: " << '"' << headerFilename << '"' << endl;
        return;
    }
    ofile << "new addition nbr 1" << endl;
    ofile.close();
}

void printFile(const std::string headerFilename) {
    ifstream ifile;
    ifile.open(headerFilename);
    if(!ifile.is_open()) {
        cout << "could not open file for reading: " << '"' << headerFilename << '"' << endl;
        return;
    } else {
        while(!ifile.eof()) {
            std::string buf;
            getline(ifile, buf);
            cout << buf << endl;
        }
    }
    ifile.close();
}

/*
    returns true if this line has a specific 'define' macro
*/
bool hasDefine(const std::string& input, const std::string& defineName) {
    int i = 0;
    if (!tryParseNextChar(input, i, '#') || !tryParseNextString(input, i, "define") || tryParseNextChar(input, i, ' ')) {
        return false;
    }

    std::string containDefine = "";
    while(i < input.size() && (std::islower(input[i]) || std::isupper(input[i]) || std::isdigit(input[i]) || input[i] == '_')) {
        containDefine.push_back(input[i]);
        i++;
    }
    return containDefine == defineName;
}

// returns true if the header file already has the define macro
bool fileHasDefine(const std::string& filepath, const std::string& defineName) {
    ifstream ifile;
    ifile.open(filepath);
    if(!ifile.is_open()) {
        cerr << "could not open file for reading: " << '"' << filepath << '"' << endl;
        return false;
    }
    while(!ifile.eof()) {
        std::string buf;
        getline(ifile, buf);
        if(hasDefine(buf, defineName)) {
            ifile.close();
            return true;
        }
    }
    ifile.close();
    return false;
}

/*
    open a file to temporarily write to, let's call it '.tmp',
    if it already exists, quit and print error message,
    open the header file for reading,
    - check if the ifndef directive already exists
    write the start of the ifndef directive,
    write the contents of the header to it,
    then write the endif directive,
    copy '.tmp' over to the header file
*/
int main(int argc, char** argv) {

    // ensure we have the header headerFilePath
    if(argc < 2) {
        cerr << "usage: " << argv[0] << " <header.h>" << endl;
        return 1;
    }

    // parse the header directory and name
    std::string headerFilePath = argv[1];
    std::string headerPath;
    std::string headerFilename;
    int i = 0;
    if(!tryParseHeaderPath(headerFilePath, i, headerPath, headerFilename)) {
        cout << "could not find header" << endl;
        return 1;
    }

    std::string headerName = getParsedHeaderName(headerFilename);
    if(fileHasDefine(headerFilePath, headerName)) {
        cerr << "Header already has the define macro." << endl;
        return 1;
    }

    cout << "writing to .tmp ..." << endl;
    // open header file
    ifstream ifile;
    ifile.open(headerFilePath);
    if(!ifile.is_open()) {
        cerr << "could not open file for reading: " << '"' << headerFilePath << '"' << endl;
        return 1;
    }

    // open temp file
    std::string tmpFilepath = ".tmp";
    ofstream ofile;
    ofile.open(tmpFilepath);
    if(!ofile.is_open()) {
        cerr << "could not open tmp file for writing: " << '"' << tmpFilepath << '"' << endl;
        return 1;
    }

    // write ifndef, define, header contents, and endif to the tmp file
    ofile << "#ifndef " << headerName << endl;
    ofile << "#define " << headerName << endl << endl;
    while(!ifile.eof()) {
        std::string buf;
        getline(ifile, buf);
        ofile << buf << endl;
    }
    ifile.close();
    ofile << endl << "#endif // " << headerName;
    ofile.close();

    cout << "copying back ..." << endl;
    ifile.open(tmpFilepath);
    if(!ifile.is_open()) {
        cerr << "could not open tmp file: " << '"' << tmpFilepath << '"' << endl;
        return 1;
    }

    ofile.open(headerFilePath);
    if(!ofile.is_open()) {
        cerr << "could not open file for reading: " << '"' << headerFilePath << '"' << endl;
        return 1;
    }

    while(!ifile.eof()) {
        std::string buf;
        getline(ifile, buf);
        ofile << buf << endl;
    }
    ifile.close();
    ofile.close();

    if(std::remove(tmpFilepath.c_str()) != 0) {
        cerr << "could not remove tmp file" << endl;
        return 1;
    } else {
        cout << "done." << endl;
        return 0;
    }
}