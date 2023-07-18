#include "../../common/common.h"
class Solution {
public:
    vector<vector<int>> cache;

    void initCache(int size) {
        cache.resize(size+1);
        for(vector<int>& row : cache) {
            row.resize(size+1);
            for(int& col : row) {
                col = -1;
            }
        }
    }

    // return the lcs starting at index i1 of text1 and i2 of text2
    int longestCommonSubsequence(string& text1, string& text2, unsigned int i1, unsigned int i2) {
        if(i1 >= text1.size() || i2 >= text2.size()) {
            return 0;
        }
        int cached = cache[i1][i2];
        if(cached != -1) {
            return cached;
        }
        
        int maxLcs = 0;
        // either this char is part of the subsequence, or it is not
        if(text1[i1] == text2[i2]) {
            maxLcs = 1 + longestCommonSubsequence(text1, text2, i1+1, i2+1);
        }
        int lcs;
        lcs = longestCommonSubsequence(text1, text2, i1+1, i2);
        if(lcs > maxLcs) {
            maxLcs = lcs;
        }
        lcs = longestCommonSubsequence(text1, text2, i1, i2+1);
        if(lcs > maxLcs) {
            maxLcs = lcs;
        }

        cache[i1][i2] = maxLcs;
        return maxLcs;
    }

    int longestCommonSubsequence(string text1, string text2) {
        int maxSize = std::max(text1.size(), text2.size());
        initCache(maxSize);
        return longestCommonSubsequence(text1, text2, 0, 0);
    }
};