#include "../../common/common.h"

class Coord {
    public:
    Coord(int _c, int _r) : c(_c), r(_r) { }
    int c;
    int r;
};

class Solution {
public:
    // set this row to zeros
    void setRowZ(vector<vector<int>>& matrix, int r) {
        for(int c = 0; c < matrix[r].size(); c++) {
            matrix[r][c] = 0;
        }
    }

    // set this column to zeros
    void setColZ(vector<vector<int>>& matrix, int c) {
        for(int r = 0; r < matrix.size(); r++) {
            matrix[r][c] = 0;
        }
    }

    void setZeroes(vector<vector<int>>& matrix) {
        vector<std::shared_ptr<Coord>> toUpdate;
        for(int r = 0; r < matrix.size(); r++) {
            for(int c = 0; c < matrix[r].size(); c++) {
                if(matrix[r][c] == 0) {
                    auto coord = make_shared<Coord>(c,r);
                    toUpdate.push_back(coord);
                }
            }
        }

        for(const auto& coords : toUpdate) {
            int c = coords->c;
            int r = coords->r;
            setColZ(matrix, c);
            setRowZ(matrix, r);
        }
    }

    vector<vector<int>> setZeroesT(vector<vector<int>>& matrix) {
        setZeroes(matrix);
        return matrix;
    }
};