/*
reads a README for a leetcode question
and generates input and expected output cpp data
*/

#include <iostream>
#include <iterator>
#include <string>
#include <regex>
#include <fstream>

int main(int argc, char *argv[]) {
    if(argc < 2) {
        std::cerr << "usage: " << argv[0] << " </path/to/README.md>" << std::endl;
        return 1;
    }
    
    char* filename = argv[1];
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "could not open " << filename << std::endl;
        return 1;
    }

    std::string line;
    std::regex inputRegex("Input: ", std::regex_constants::ECMAScript);
    std::regex outputRegex("Output: ", std::regex_constants::ECMAScript);
    std::regex exampleRegex("Example", std::regex_constants::ECMAScript);

    while (std::getline(file, line)) {
        if (std::regex_search(line, inputRegex)) {
            std::cout << "input: ";
            std::cout << line << std::endl;
        }
        if (std::regex_search(line, outputRegex)) {
            std::cout << "output: ";
            std::cout << line << std::endl;
        }
        if (std::regex_search(line, exampleRegex)) {
            std::cout << "example: ";
            std::cout << line << std::endl;
        }
    }

    file.close();
    return 0;
 
    // std::regex word_regex("(\\w+)");
    // auto words_begin = 
    //     std::sregex_iterator(s.begin(), s.end(), word_regex);
    // auto words_end = std::sregex_iterator();
 
    // std::regex long_word_regex("(\\w{7,})");
    // std::string new_s = std::regex_replace(s, long_word_regex, "[$&]");
    // std::cout << new_s << '\n';

    return 0;
}