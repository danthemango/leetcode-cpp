#include "../../common/common.h"

// note sure about this one, but it wasn't defined for my compiler
#define uint32_t int

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count = 0; 
        while(n > 0) {
            if(n & 1 == 1) {
                count++;
            }
            n>>=1;
        }
        return count;
    }
};