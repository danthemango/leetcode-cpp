#include "../../common/common.h"

const int cacheWidth = 100;
const int cacheHeight = 100;
bool hasInit = false;
int cache[cacheWidth][cacheHeight];

class Solution {
public:
    int uniquePaths(int m, int n) {
        if(!hasInit) {
            for(int m = 0; m < cacheWidth; m++) {
                for(int n = 0; n < cacheHeight; n++) {
                    cache[m][n] = -1;
                }
            }
            hasInit = true;
        }

        if(cache[m][n] != -1) {
            return cache[m][n];
        }
        
        int result;
        if(m == 1 || n == 1) {
            result = 1;
        } else {
            // it is the number of possible paths if choosing to go right
            // plus the number of possible paths if choosing to go down one square
            result = uniquePaths(m-1,n) + uniquePaths(m,n-1);
        }
        cache[m][n] = result;
        return result;
    }
};
