#include "../../common/common.h"

class Solution {
public:
    // update the largest palindrome starting at starting index si and ending index ei, working outward
    void longestPalindrome(string& s, int& si, int& ei) {
        while(si-1 >= 0 && ei < s.size() && s[si-1] == s[ei+1]) {
            --si;
            ++ei;
        }
    }

    string substringFromIndices(string& s, const int& si, const int& ei) {
        int diff = ei - si + 1;
        if(diff == 0) {
            return "";
        } else {
            return s.substr(si, diff);
        }
    }

    // updates the indices to the new ones if the difference is larger
    void updateMaxI(int& si, int& ei, const int& newSI, const int& newEI) {
        int newDiff = newEI - newSI;
        int oldDiff = ei - si;
        if(newDiff > oldDiff) {
            si = newSI;
            ei = newEI;
        }
    }

    string longestPalindrome(string s) {
        if(s.size() <= 1) {
            return s;
        }
        // starting index
        int si = 0;
        // ending index
        int ei = 0;

        // get the largest odd-sized palindromic substring
        {
            // center index
            int ci = 1;
            while(ci < s.size()-1) {
                int csi = ci;
                int cei = ci;
                longestPalindrome(s, csi, cei);
                // if these indices are further apart than the result, update result
                updateMaxI(si, ei, csi, cei);
                ++ci;
            }
        }

        // get the largest even-sized palindromic substring
        {
            // center-left index
            int cli = 0;
            while(cli <= s.size()-2) {
                int csi = cli;
                int cei = cli+1;
                if(s[csi] != s[cei]) {
                    ++cli;
                    continue;
                }
                longestPalindrome(s, csi, cei);
                // if these indices are further apart than the result, update result
                updateMaxI(si, ei, csi, cei);
                ++cli;
            }
        }

        return substringFromIndices(s, si, ei);
    }
};
