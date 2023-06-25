#include <string>
#include <iostream>
#include <vector>

int main() {
    std::vector<std::string> myStrings {"this", "is", "just", "a", "test"};
    for(const auto& myString : myStrings) {
        std::cout << myString << std::endl;
    }
}
