#include "../../common/common.h"

class Coord {
    public:
    Coord(int _x, int _y) : x(_x), y(_y) { }
    unsigned int x;
    unsigned int y;
    bool operator==(const std::shared_ptr<Coord>& coord) const {
        return coord->x == this->x && coord->y == this->y;
    }
    // returns true if the current coordinate is in the vector
    bool isIn(std::vector<std::shared_ptr<Coord>>& coords) const {
        for(auto& coord : coords) {
            if(*this == coord) {
                return true;
            }
        }
        return false;
    }
};

/*
    start by finding the coordinate of the first char,
    then search each of the possible neighbors for the next char,
    until the end of the string
*/

// a mapping of all chars in a word or board
class CharCount {
    // char -> nbr of times the char has been counted
    std::map<char, unsigned int> counts;
    public:
    CharCount(vector<vector<char>>& board) {
        for(auto row : board) {
            for(const char& col : row) {
                incChar(col);
            }
        }
    }

    CharCount(std::string& word) {
        for(const char& c : word) {
            incChar(c);
        }
    }

    // increment the char value
    void incChar(char c) {
        if(counts.find(c) == counts.end()) {
            counts[c] = 1;
        } else {
            ++counts[c];
        }
    }

    unsigned int getChar(char c) {
        if(counts.find(c) == counts.end()) {
            return 0;
        } else {
            return counts[c];
        }
    }
    
    // returns true if this word count has at least as many counts in each char as other
    bool hasAll(CharCount& other) {
        for(auto& pair : other.counts) {
            char c = pair.first;
            unsigned int count = pair.second;
            if(counts.find(c) == counts.end() || counts[c] < count) {
                return false;
            }
        }
        return true;
    }
};

class Solution {
public:

    // returns a mapping of all 

    static std::vector<std::shared_ptr<Coord>> getNeighbors(vector<vector<char>>& board, const std::shared_ptr<Coord>& coord) {
        auto width = getWidth(board);
        auto height = getHeight(board);
        std::vector<std::shared_ptr<Coord>> result;
        if(coord->x < width - 1) {
            result.push_back(std::make_shared<Coord>(coord->x+1, coord->y));
        }
        if(coord->x > 0) {
            result.push_back(std::make_shared<Coord>(coord->x-1, coord->y));
        }
        if(coord->y < height - 1) {
            result.push_back(std::make_shared<Coord>(coord->x, coord->y+1));
        }
        if(coord->y > 0) {
            result.push_back(std::make_shared<Coord>(coord->x, coord->y-1));
        }
        return result;
    }

    static char getCoord(const vector<vector<char>>& board, const std::shared_ptr<Coord>& coord) {
        return board[coord->y][coord->x];
    }

    static bool exist(vector<vector<char>>& board, const std::string& word, unsigned int index, const std::shared_ptr<Coord>& coord, std::vector<std::shared_ptr<Coord>>& prevCoords) {
        // if this coordinate is in the list of previous coordinates, then we have a turn around happening
        if(coord->isIn(prevCoords)) {
            return false;
        }

        // if we are at the end of the word, then there must not have been any discrepencies
        if(index == word.size()) {
            return true;
        }

        // if the letter at the current index doesn't match the letter on the board, we cannot match the sequence
        char c = getCoord(board, coord);
        if(word[index] != c) {
            return false;
        }

        // check if we are at the last char of a word
        if(index == word.size() - 1) {
            return true;
        }

        // else, check all of the neighbors for the next char in the sequence
        auto neighbors = getNeighbors(board, coord);
        for(auto& neighbor : neighbors) {
            prevCoords.push_back(coord);
            if(exist(board, word, index+1, neighbor, prevCoords)) {
                return true;
            } else {
                prevCoords.pop_back();
            }
        }

        return false;
    }

    static bool exist(vector<vector<char>>& board, const std::string& word, unsigned int index, const std::shared_ptr<Coord>& coord) {
        std::vector<std::shared_ptr<Coord>> prevCoords;
        return exist(board, word, index, coord, prevCoords);
    }

    static unsigned int getHeight(vector<vector<char>>& board) {
        return board.size();
    }

    static unsigned int getWidth(vector<vector<char>>& board) {
        unsigned int width = 0;
        if(getHeight(board) > 0) {
            width = board[0].size();
        }
        return width;
    }

    static bool exist(vector<vector<char>>& board, string word) {
        // check if the number of times a letter appears in the board is equal to or larger than the number of times a letter appears in word
        CharCount boardCounts(board);
        CharCount wordCount(word);
        if(!boardCounts.hasAll(wordCount)) {
            return false;
        }
        
        // check every coordinate on the board for the existence of the word
        unsigned int height = board.size();
        unsigned int width = getWidth(board);
        for(int y = 0; y < height; ++y) {
            for(int x = 0; x < width; ++x) {
                auto coord = std::make_shared<Coord>(x,y);
                if(exist(board, word, 0, coord)) {
                    return true;
                }
            }
        }
        return false;
    }
};