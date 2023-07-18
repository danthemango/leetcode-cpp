#include "../../common/common.h"

class Solution {
public:
    int longestSubarray(vector<int>& nums) {

       // iterate over the array and keep a count of of the number of 1's of the last 2 sequences
       // the count shall be size of those 2 sequences added together, and if it is larger than the max count, update it
       // if we never saw any 0's, return count-1
       // and run the check one more time at the very end in case we end on a 1

        int maxCount = 0;
        int count1 = 0;
        int count2 = 0;
        bool saw0 = false;

        for(unsigned int i = 0; i < nums.size(); i++) {
            const int& num = nums[i];
            if(num == 1) {
                ++count2;
            } else {
                saw0 = true;
                int curCount = count1 + count2;
                if(maxCount < curCount) {
                    maxCount = curCount;
                }
                count1 = count2;
                count2 = 0;
            }
        }

        if(!saw0) {
            return count2-1;
        }
       
        {
            int curCount = count1 + count2;
            if(maxCount < curCount) {
                maxCount = curCount;
            }
            count1 = count2;
            count2 = 0;
        }

        return maxCount;
    }
};