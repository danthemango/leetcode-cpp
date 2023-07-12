#include "../../common/common.h"

std::string vector2string(std::vector<int> inputStringList)
{
    stringstream ss;
    ss << '[';
    bool first = true;
    for (const int & num : inputStringList)
    {
        if (!first)
        {
            ss << ',';
        }
        else
        {
            first = false;
        }

        ss << num;
    }
    ss << ']';

    std::string result;
    ss >> result;
    return result;
}

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        /*
            create three arrays,
            the value at index i of array1 will be equal to the product of all values to the left of nums[i]
            the value at index i of array2 will be equal to the product of all values to the right of nums[i]
            the value at index i of array3 will be equal to array1[i] * array2[i]
              and will be the result
        */
        vector<int> result;
        result.reserve(nums.size());
        if(nums.size() < 2) {
            return result;
        }

        vector<int> array1;
        array1.resize(nums.size());
        vector<int> array2;
        array2.resize(nums.size());
        {
            int i = 0;
            int j = nums.size() - 1;
            int result1 = 1;
            int result2 = 1;
            array1[i] = result1;
            array2[j] = result2;
            ++i;
            --j;
            while(i < nums.size()) {
                result1 *= nums[i-1];
                result2 *= nums[j+1];
                array1[i] = result1;
                array2[j] = result2;
                ++i;
                --j;
            }
        }

        for(int i = 0; i < nums.size(); i++) {
            result.push_back(array1[i] * array2[i]);
        }

        return result;
    }
};