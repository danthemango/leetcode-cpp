#include "../../common/common.h"

// https://leetcode.com/problems/missing-number
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        bool cache[10001];
        for(int i = 0; i <= 10000; i++) {
            cache[i] = false;
        }
        for(const int& n : nums) {
            cache[n] = true;
        }
        for(int i = 0; i <= 10000; i++) {
            if(!cache[i]) {
                return i;
            }
        }
        return -1;
    }
};
