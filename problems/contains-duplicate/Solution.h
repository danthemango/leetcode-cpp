#include "../../common/common.h"
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        map<int, bool> vals;
        for(const int& num : nums) {
            if(vals.find(num) != vals.end()) {
                return true;
            } else {
                vals[num] = true;
            }
        } 
        return false;
    }
};
