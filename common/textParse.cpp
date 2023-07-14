#include "textParse.h"
#include <sstream>

namespace textParse {
    int getDigit(char c) {
        return c - '0';
    }
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
    bool tryParseChar(const std::string& input, unsigned int& i, const char& c) {
        if(i < input.size() && input[i] == c) {
            i++;
            return true;
        } else {
            return false;
        }
    }
    bool skipSpace(std::string input, unsigned int& i) {
        bool skipped = false;
        while(i < input.size() && isSpace(input[i])) {
            skipped = true;
            i++;
        }
        return skipped;
    }
    bool tryParseNextChar(const std::string& input, unsigned int& i, char c) {
        skipSpace(input, i);
        return tryParseChar(input, i, c);
    }
    bool tryParseString(const std::string& input, unsigned int& i, const std::string& str) {
        unsigned int resetI = i;
        for(unsigned int j = 0; j < str.size(); j++) {
            if(!tryParseChar(input, i, str[j])) {
                i = resetI;
                return false;
            }
        }

        return true;
    }
    bool tryParseNextString(const std::string& input, unsigned int& i, const std::string& str) {
        unsigned int resetI = i;
        skipSpace(input, i);
        if(tryParseString(input, i, str)) {
            return true;
        } else {
            i = resetI;
            return false;
        }
    }
    bool tryParseNextStrings(const std::string& input, unsigned int& i, const std::vector<std::string>& strList) {
        unsigned int resetI = i;
        for(const std::string& str : strList) {
            if(!tryParseNextString(input, i, str)) {
                i = resetI;
                return false;
            }
        }
        return true;
    }
    bool tryParseInt(const std::string& input, unsigned int& i, int& out_int) {
        unsigned int resetI = i;

        if(i >= input.size()) {
            i = resetI;
            return false;
        }

        // check for negative numbers
        int sign = 1;
        if(tryParseNextChar(input, i, '-')) {
            sign = -1;
        }

        if(!std::isdigit(input[i])) {
            i = resetI;
            return false;
        }

        out_int = 0;
        while(i < input.size() && std::isdigit(input[i])) {
            out_int *= 10;
            out_int += getDigit(input[i]);
            i++;
        }
        out_int *= sign;

        return true;
    }
    bool tryParseInt(const std::string& input, int& out_int) {
        unsigned int i = 0;
        return tryParseInt(input, i, out_int);
    }
    bool tryParseNextInt(const std::string& input, unsigned int& i, int& out_int) {
        skipSpace(input, i);
        return tryParseInt(input, i, out_int);
    }

    std::string stdin2String() {
        std::string result;
        std::string line;
        while (std::getline(std::cin, line)) {
            result.append(line);
            result.push_back('\n');
        }
        return result;
    }
    std::string file2String(std::ifstream& ifile) {
        std::string result;
        std::string line;
        while(std::getline(ifile, line)) {
            result.append(line + '\n');
        }
        return result;
    }
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

    std::string vectorInt2String(std::vector<int> arr)
    {
        std::string result;
        result.push_back('[');
        bool first = true;
        for (const int& val : arr)
        {
            if (!first)
            {
                result.push_back(',');
            }
            else
            {
                first = false;
            }

            result.push_back('"');
            result.append(std::to_string(val));
            result.push_back('"');
        }
        result.push_back(']');

        return result;
    }

    std::string vectorString2string(std::vector<std::string> inputStringList)
    {
        std::string result;
        result.push_back('[');
        bool first = true;
        for (const std::string &inputString : inputStringList)
        {
            if (!first)
            {
                result.push_back(',');
            }
            else
            {
                first = false;
            }

            result.push_back('"');
            result.append(inputString);
            result.push_back('"');
        }
        result.push_back(']');

        return result;
    }

    std::string vectorVectorInt2String(std::vector<std::vector<int>> arrArr)
    {
        std::string result;
        result.push_back('[');
        bool first = true;
        for (const auto &subArr : arrArr)
        {
            if (!first)
            {
                result.push_back(',');
            }
            else
            {
                first = false;
            }
            result.append(vectorInt2String(subArr));
        }
        result.push_back(']');
        return result;
    }
}
