#include "../../common/common.h"

class Solution {
public:
    
    void traverseRight(vector<vector<int>>& matrix, int widthDiff, int& x, int& y, vector<int>& result) {
        for(int i = 0; i < widthDiff; i++) {
            ++x;
            const int& val = matrix[y][x];
            result.push_back(val);
        }
    }
    void traverseDown(vector<vector<int>>& matrix, int heightDiff, int& x, int& y, vector<int>& result) {
        for(int i = 0; i < heightDiff; i++) {
            ++y;
            const int& val = matrix[y][x];
            result.push_back(val);
        }
    }
    void traverseLeft(vector<vector<int>>& matrix, int widthDiff, int& x, int& y, vector<int>& result) {
        for(int i = 0; i < widthDiff; i++) {
            --x;
            const int& val = matrix[y][x];
            result.push_back(val);
        }
    }
    void traverseUp(vector<vector<int>>& matrix, int heightDiff, int& x, int& y, vector<int>& result) {
        for(int i = 0; i < heightDiff; i++) {
            --y;
            const int& val = matrix[y][x];
            result.push_back(val);
        }
    }

    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int height = matrix.size();
        int width = 0;
        if(height > 0) {
            width = matrix[0].size();
        }
        vector<int> result;
        if(width == 0 || height == 0) {
            return result;
        }
        int x = -1;
        int y = 0;
        int widthDiff = width;
        traverseRight(matrix, widthDiff, x, y, result);
        int heightDiff = height;
        while(widthDiff > 0 && heightDiff > 0) {
            if(widthDiff > 0 && heightDiff > 0) {
                --heightDiff;
                traverseDown(matrix, heightDiff, x, y, result);
            }
            if(widthDiff > 0 && heightDiff > 0) {
                --widthDiff;
                traverseLeft(matrix, widthDiff, x, y, result);
            }
            if(widthDiff > 0 && heightDiff > 0) {
                --heightDiff;
                traverseUp(matrix, heightDiff, x, y, result);
            }
            if(widthDiff > 0 && heightDiff > 0) {
                --widthDiff;
                traverseRight(matrix, widthDiff, x, y, result);
            }
        }

        return result;
    }
};