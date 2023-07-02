#include "../../common/common.h"

const int cacheWidth = 100;
const int cacheHeight = 100;

class Solution {
public:
    int cache[cacheWidth][cacheHeight];
    Solution() {
        // init cache with -1's for invalid value
        for(int m = 0; m < cacheWidth; m++) {
            for(int n = 0; n < cacheHeight; n++) {
                cache[m][n] = -1;
            }
        }
    }
    int uniquePaths(int m, int n) {
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

class SolutionRunner {
    public:
    SolutionRunner(int m, int n, int expected) {
        Solution solution;
        int result = solution.uniquePaths(m,n);
        std::cout << "n = " << n << ", expected = " << expected << ", result = " << result << ": ";
        if(result != expected) {
            std::cout << "Fail." << std::endl;
        } else {
            std::cout << "Success." << std::endl;
        }
    }
};


int main() {
    std::vector<SolutionRunner> solutionRunners {
        {3,7,28},
        {3,2,3},
        {15,15,40116600},
        {17,17,601080390}
    };
}
