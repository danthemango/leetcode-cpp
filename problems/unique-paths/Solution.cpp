#include "../../common/common.h"

class MapPtrMap {
    std::map<int, std::shared_ptr<std::map<int,int>>> mMap;
    public:
    MapPtrMap(){}
    void print() {
        std::cout << "printing all: " << std::endl;
        for(const auto& mmapPair : mMap) {
            const auto mmap = *mmapPair.second;
            const int& m = mmapPair.first;
            for(const auto& nMapPair : mmap) {
                const int& result = nMapPair.second;
                const int& n = nMapPair.first;
                std::cout << "m = " << m << " n = " << n << " result = " << result << std::endl;
            }
        }
    }

    void put(int m, int n, int result) {
        if(mMap.find(m) == mMap.end()) {
            mMap[m] = std::make_shared<std::map<int,int>>();
        }
        auto nMap = mMap[m];
        (*nMap)[n] = result;
    }
    bool has(int m, int n) {
        if(mMap.find(m) == mMap.end()) {
            return false;
        }
        auto nMap = *mMap[m];
        if(nMap.find(n) == nMap.end()) {
            return false;
        }
        return true;
    }
    int get(int m, int n) {
        if(mMap.find(m) == mMap.end()) {
            return -1;
        }
        auto nMap = *mMap[m];
        if(nMap.find(n) == nMap.end()) {
            return -2;
        }
        return nMap[n];
    }
};

class Solution {
public:
    MapPtrMap mapPtrMap;
    int uniquePaths(int m, int n) {
        if(mapPtrMap.has(m,n)) {
            return mapPtrMap.get(m,n);
        } else if(mapPtrMap.has(n,m)) {
            return mapPtrMap.get(n,m);
        }
        
        int result;
        if(m == 1 || n == 1) {
            result = 1;
        } else {
            // it is the number of possible paths if choosing to go right
            // plus the number of possible paths if choosing to go down one square
            result = uniquePaths(m-1,n) + uniquePaths(m,n-1);
        }
        mapPtrMap.put(m,n,result);
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
