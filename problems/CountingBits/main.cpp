#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

std::string vector2string(std::vector<int> input) {
    stringstream ss;
    ss << '[';
    bool first = true;
    for(const int& val : input) {
        if(!first) {
            ss << ',';
        } else {
            first = false;
        }

        ss << std::to_string(val);
    }
    ss << ']';

    std::string result;
    ss >> result;
    return result;
}

class Solution {
public:
    int getBitCount(int n) {
        if(n == 0) {
            return 0;
        }

        int count = 0;

        while(n > 0) {
            if(n & 1 == 1) {
                count++;
            }
            n >>= 1;
        }
        return count;
    }

    vector<int> countBits(int n) {
        vector<int> result;
        result.push_back(0);

        // store the largest power of 2 that's lower than i
        vector<int> powerOf2;
        powerOf2.push_back(0);
        powerOf2.push_back(1);
        
        for(int i = 1; i <= n; i++) {
            // using the previously largest power of 2 less than i,
            // check if this one has a higher one
            int prevPow2 = powerOf2[i];
            int currPow2 = prevPow2 * 2 <= i ? prevPow2 * 2 : prevPow2;
            powerOf2.push_back(currPow2);
            int remainder = i - currPow2;
            int bitCount = 1 + result[remainder];
            result.push_back(bitCount);
        }

        return result;
    }
};

/*
Given an integer n, return an array ans of length n + 1 such that for each i (0 <= i <= n), ans[i] is the number of 1's in the binary representation of i.

Example 1:

Input: n = 2
Output: [0,1,1]
Explanation:
0 --> 0
1 --> 1
2 --> 10
Example 2:

Input: n = 5
Output: [0,1,1,2,1,2]
Explanation:
0 --> 0
1 --> 1
2 --> 10
3 --> 11
4 --> 100
5 --> 101
*/

// prints a positive binary number
std::string getBinaryString(int n) {
    std::string result;


    if(n == 0) {
        cout << 0 << endl;
        return "0";
    }

    int mask = 1;
    while(n > 0) {
        result.insert(0, std::to_string(n & mask == 1));
        n >>= 1;
    }

    return result;
}

int main() {
    Solution solution;
    int input = 20;
    std::string expected = "[0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,1,2,2,3,2]";
    std::vector<int> output = solution.countBits(input);
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
