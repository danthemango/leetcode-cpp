#include "../../common/common.h"

class Solution {
public:
    // returns true if every letter in the magazine appears at least as many times
    // as it appears in the ransom note
    bool canConstruct(string ransomNote, string magazine) {
        int cacheR[26];
        int cacheM[26];
        for(int i = 0; i < 26; i++) {
            cacheR[i] = 0;
            cacheM[i] = 0;
        }
        for(int i = 0; i < ransomNote.size(); i++) {
            char c = ransomNote[i];
            int idx = c - 'a';
            cacheR[idx]++;
        }
        for(int i = 0; i < magazine.size(); i++) {
            char c = magazine[i];
            int idx = c - 'a';
            cacheM[idx]++;
        }
        for(int i = 0; i < 26; i++) {
            if(cacheR[i] > cacheM[i]) {
                return false;
            }
        }
        return true;
    }
};