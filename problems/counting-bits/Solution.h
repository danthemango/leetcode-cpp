#include "../../common/common.h"

class Solution {
public:
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