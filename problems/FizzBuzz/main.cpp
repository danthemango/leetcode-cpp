#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<string> fizzBuzz(int n) {
        vector<string> result;
        for(int i = 1; i <=n; i++) {
            if(i % 15 == 0) {
                result.push_back("FizzBuzz");
            } else if(i % 3 == 0) {
                result.push_back("Fizz");
            } else if(i % 5 == 0) {
                result.push_back("Buzz");
            } else {
                result.push_back(to_string(i));
            }
        }
        return result; 
    }
};

/*
Given an integer n, return a string array answer (1-indexed) where:

answer[i] == "FizzBuzz" if i is divisible by 3 and 5.
answer[i] == "Fizz" if i is divisible by 3.
answer[i] == "Buzz" if i is divisible by 5.
answer[i] == i (as a string) if none of the above conditions are true.
*/

/*
Example 1:

Input: n = 3
Output: ["1","2","Fizz"]
Example 2:

Input: n = 5
Output: ["1","2","Fizz","4","Buzz"]
Example 3:

Input: n = 15
Output: ["1","2","Fizz","4","Buzz","Fizz","7","8","Fizz","Buzz","11","Fizz","13","14","FizzBuzz"]
*/

std::string vector2string(std::vector<std::string> inputStringList) {
    stringstream ss;
    ss << '[';
    bool first = true;
    for(const std::string& inputString : inputStringList) {
        if(!first) {
            ss << ',';
        } else {
            first = false;
        }

        ss << '"' << inputString << '"';
    }
    ss << ']';

    std::string result;
    ss >> result;
    return result;
}

int main() {
    Solution solution;
    int input = 15;
    std::string expected = "[\"1\",\"2\",\"Fizz\",\"4\",\"Buzz\",\"Fizz\",\"7\",\"8\",\"Fizz\",\"Buzz\",\"11\",\"Fizz\",\"13\",\"14\",\"FizzBuzz\"]";
    std::vector<std::string> output = solution.fizzBuzz(input);
    std::string outputString = vector2string(output);
    cout << "input: " << input << endl;
    cout << "output: " << outputString << endl;
    cout << "expected: " << expected << endl;
    if(expected != outputString) {
        cout << "Fail." << endl;
    } else {
        cout << "Success" << endl;
    }
}
