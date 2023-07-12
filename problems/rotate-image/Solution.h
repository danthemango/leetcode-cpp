#include "../../common/common.h"

/*
    nxn matrix
    0,0 -> n-1,0
    0,1 -> n-2,0
    0,2 -> n-3,0
    ...
    0,n-1 -> 0,0

    1,0 -> n-1,1
    1,1 -> n-2,1
    ...
    1,n-1 -> 0,1

    ...

    n-1,0 -> n-1,n-1
    n-1,1 -> n-2,n-1
    ...
    n-1,n-1 -> 0,n-1
*/

class Coord {
    public:
    int c;
    int r;
    Coord(int _c, int _r) : c(_c), r(_r) { }
    std::shared_ptr<Coord> getRotated(int n) {
        int newC = n - 1 - r;
        int newR = c;
        auto result = make_shared<Coord>(newC, newR);
        return result;
    }
    friend std::ostream& operator<<(std::ostream& os, Coord& c) {
        os << "(" << c.c << "," << c.r << ")";
        return os;
    }
};

class Solution {
public:
    void swap(int& a, int& b) {
        int c = a;
        a = b;
        b = c;
    }

    // returns a reference to the element in the matrix at coord
    int& getCoord(vector<vector<int>>& matrix, std::shared_ptr<Coord> coord) {
        return matrix[coord->r][coord->c];
    }

    // swap each element around the
    void rotate4times(vector<vector<int>>& matrix, std::shared_ptr<Coord> coord) {
        int n = matrix.size();
        int tmp = getCoord(matrix, coord);
        for(int i = 0; i < 4; i++) {
            auto newCoord = coord->getRotated(n);
            // cout << *coord << ": " << tmp << " <-> " << *newCoord << ": " << matrix[newCoord->r][newCoord->c] << endl;
            swap(tmp, getCoord(matrix, newCoord));
            coord = newCoord;
        }
    }

    void printMatrix(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for(int r = 0; r < n; ++r) {
            for(int c = 0; c < n; ++c) {
                auto coord = std::make_shared<Coord>(c,r);
                int val = getCoord(matrix, coord);
                std::cout << val << (val >= 10? " " : "  ");
            }
            std::cout << std::endl;
        }
    }

    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        for(int r = 0; r < n/2; ++r) {
            for(int c = r; c < n-r-1; ++c) {
                auto coord = std::make_shared<Coord>(c,r);
                rotate4times(matrix, coord);
            }
        }
    }

    vector<vector<int>> rotateT(vector<vector<int>>& matrix) {
        rotate(matrix);
        return matrix;
    }
};