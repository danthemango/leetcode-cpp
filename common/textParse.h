#ifndef TEXTPARSE_H
#define TEXTPARSE_H

/*
    textparse.h
    responsible for simple text parsing functions
*/

#include "common.h"

namespace textParse {

    /*
        returns true if we have letter
    */
    bool isChar(const char & c) {
        return std::islower(c) || std::isupper(c);
    }

    // returns true if the value is a digit
    bool isDigit(char c) {
        return c >= '0' && c <= '9';
    }

    int getDigit(char c) {
        return c - '0';
    }

    // TODO parse all whitespace
    bool isSpace(char c) {
        switch(c) {
            case ' ':
            case '\n':
            case '\t':
                return true;
                break;
            default:
                return false;
                break;
        }
    }

    // returns true if c is the char in input at i
    // incrementing i if found
    bool tryParseChar(const std::string& input, int& i, const char& c) {
        if(i < input.size() && input[i] == c) {
            i++;
            return true;
        } else {
            return false;
        }
    }

    // increments i until a non-whitespace is found
    bool skipSpace(std::string input, int& i) {
        bool skipped = false;
        while(i < input.size() && isSpace(input[i])) {
            skipped = true;
            i++;
        }
        return skipped;
    }

    // returns true if 'c' is the next non-whitespace character in input,
    // after position i
    // updating i if found
    bool tryParseNextChar(const std::string& input, int& i, char c) {
        skipSpace(input, i);
        return tryParseChar(input, i, c);
    }

    // returns true if we found string 'str' at index i of input
    // updating i to the next index after the last char in input found
    bool tryParseString(const std::string& input, int& i, const std::string& str) {
        int resetI = i;
        for(int j = 0; j < str.size(); j++) {
            if(!tryParseChar(input, i, str[j])) {
                i = resetI;
                return false;
            }
        }

        return true;
    }

    // try parsing a string skipping any spaces
    // setting i to the next char after successful parse
    bool tryParseNextString(const std::string& input, int& i, const std::string& str) {
        int resetI = i;
        skipSpace(input, i);
        if(tryParseString(input, i, str)) {
            return true;
        } else {
            i = resetI;
            return false;
        }
    }

    // try parsing a sequence of strings ignoring whitespace
    // setting i to the next char after successful parse
    bool tryParseNextStrings(const std::string& input, int& i, const std::vector<std::string>& strList) {
        int resetI = i;
        for(const std::string& str : strList) {
            if(!tryParseNextString(input, i, str)) {
                i = resetI;
                return false;
            }
        }
        return true;
    }

    // returns true if an int can be found at position i of input string
    // and returns the value in out_int
    // and increments i to the char after the pattern
    bool tryParseInt(const std::string& input, int& i, int& out_int) {
        int resetI = i;

        if(i >= input.size()) {
            i = resetI;
            return false;
        }

        // check for negative numbers
        int sign = 1;
        if(tryParseNextChar(input, i, '-')) {
            sign = -1;
        }

        if(!isDigit(input[i])) {
            i = resetI;
            return false;
        }

        out_int = 0;
        while(i < input.size() && isDigit(input[i])) {
            out_int *= 10;
            out_int += getDigit(input[i]);
            i++;
        }
        out_int *= sign;

        return true;
    }

    bool tryParseInt(const std::string& input, int& out_int) {
        int i = 0;
        return tryParseInt(input, i, out_int);
    }

    bool tryParseNextInt(const std::string& input, int& i, int& out_int) {
        skipSpace(input, i);
        tryParseInt(input, i, out_int);
    }

    bool tryParseVectorInt(const std::string& input, int& i, std::vector<int>& out_vector) {
        int resetI = i;
        std::vector<int> result;
        if(!tryParseNextChar(input, i, '[')) {
            i = resetI;
            return false;
        }

        // keep parsing ints until we see the closing brace
        bool first = true;
        while(i < input.size()) {
            if(tryParseNextChar(input, i, ']')) {
                out_vector = result;
                return true;
            }

            if(!first) {
                if(!tryParseNextChar(input, i, ',')) {
                    i = resetI;
                    return false;
                }
            } else {
                first = false;
            }

            int intVal;
            if(tryParseNextInt(input, i, intVal)) {
                result.push_back(intVal);
            } else {
                // invalid value found
                i = resetI;
                return false;
            }

        }

        // error: end of input with no closing brace
        i = resetI;
        return false;
    }

    bool tryParseVectorInt(const std::string& input, std::vector<int>& out_vector) {
        int i = 0;
        return tryParseVectorInt(input, i, out_vector);
    }

    // fetches all stdin input and returns it as a string
    // (for quick development, not space efficient)
    std::string stdin2String() {
        std::string result;
        std::string line;
        while (std::getline(std::cin, line)) {
            result.append(line);
            result.push_back('\n');
        }
        return result;
    }

    // returns the file contents as a string
    std::string file2String(std::ifstream& ifile) {
        std::string result;
        std::string line;
        while(std::getline(ifile, line)) {
            result.append(line + '\n');
        }
        return result;
    }

    // returns all contents of a file to a string
    bool tryGetFileContents(const std::string& filename, std::string& out_contents) {
        std::ifstream ifile(filename);
        if(!ifile) {
            return false;
        }
        out_contents = "";
        std::string line;
        while(std::getline(ifile, line)) {
            out_contents.append(line + '\n');
        }
        return true;
    }
}

#endif // TEXTPARSE_H