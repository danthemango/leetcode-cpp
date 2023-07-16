#include "../../common/common.h"

class Solution {
public:

    // returns true if the substring starting at and including i and ending at j is a palindrome
    int isPalindrome(string& s, int i, int j) {
        if(i == j) {
            return true;
        }

        while(i < j) {
            if(s[i] != s[j]) {
                return false;
            }
            ++i;
            --j;
        }
        return true;
    }

    // counts the substrings starting at and including index i
    int countSubstrings(string& s, int i) {
        int count = 0;
        for(int j = i; j < s.size(); j++) {
            if(isPalindrome(s, i, j)) {
                ++count;
            }
        }
        return count;
    }

    int countSubstrings(string s) {
        int count = 0;
        for(int i = 0;  i < s.size(); i++) {
            count += countSubstrings(s, i);
        }
        return count;
    }
};