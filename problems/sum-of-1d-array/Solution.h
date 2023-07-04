#include "../../common/common.h"

class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        vector<int> result;
        if(nums.size() == 0) {
            return result;
        }
        int sum = nums[0];
        result.push_back(nums[0]);
        for(int i = 1; i < nums.size(); i++) {
            sum += nums[i];
            result.push_back(sum);
        }
        return result;
    }
};