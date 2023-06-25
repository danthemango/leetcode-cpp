#include "../../common/common.h"

class Solution {
public:
    /*
        create a map of found numbers with their indices
        iterate through each element,
        and for each element, get the associated other number needed
        (remainder = target - nums[i])
        if the needed number exists in the map, return the answer:
        - the current index, and the index of the val in the map
        
    */

    // returns a vector of two ints
    vector<int> getDoubleVector(int a, int b) {
        std::vector<int> result;
        result.push_back(b);
        result.push_back(a);
        return result;
    }

    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result;
        // val -> index
        map<int, int> foundNums;
        
        for(int i = 0; i < nums.size(); i++) {
            // remainder
            int rem = target - nums[i];

            if(foundNums.find(rem) != foundNums.end()) {
                // we found the needed number, returns its index
                return getDoubleVector(i, foundNums[rem]);
            }

            // else insert the num into the map
            foundNums[nums[i]] = i;
        }
        return result;
    }
};

