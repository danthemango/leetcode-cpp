#include "../../common/common.h"

class Solution {
public:
    bool isAnagram(string s, string t) {
        int cacheS[26];
        int cacheT[26];
        if(s.size() != t.size()) {
            return false;
        }
        for(int i = 0; i < 26; i++) {
            cacheS[i] = 0;
            cacheT[i] = 0;
        }
        for(const char& c : s) {
            cacheS[c - 'a']++;
        }
        for(const char& c : t) {
            cacheT[c - 'a']++;
        }
        for(int i = 0; i < 26; i++) {
            if(cacheS[i] != cacheT[i]) {
                return false;
            }
        }
        return true;
    }
};
