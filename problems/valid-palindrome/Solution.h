#include "../../common/common.h"

class Solution {
public:
    std::string getOnlyLower(std::string s) {
        std::string result;
        for(char c : s) {
            char lc = std::tolower(c);
            if(std::isalnum(lc)) {
                result.push_back(lc);
            }
        }
        return result;
    }

    bool isPalindrome(string s) {
        std::string ls = getOnlyLower(s);
        int i = 0;
        int j = ls.size()-1;
        while(i < j) {
            if(ls[i] != ls[j]) {
                return false;
            }
            ++i;
            --j;
        }
        return true;
    }
};