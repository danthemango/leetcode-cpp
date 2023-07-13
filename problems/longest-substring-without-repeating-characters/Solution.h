#include "../../common/common.h"

class CharMap {
    public:
    std::map<char, bool> myMap;

    void put(char c) {
        myMap[c] = true;
    }

    // returns true if the char has been inserted already
    bool has(char c) {
        return myMap.find(c) != myMap.end();
    }

    // remove char from mymap
    void erase(char c) {
        myMap.erase(c);        
    }
};

/*
    create charmap
    set size = 0
    set startI = 0
    set endI = 0
    while endI < s.size()
    - if the char at endI is in the charMap
        - while the char at endI is in charMap and startI < endI
            - remove the char at startI from charMap
            - decrement size
            - increment startI
    - else
        - add the char at endI to the charMap
        - increment the size and increment endI
        - if the size is larger than the max, update max
    return the max
*/

class Solution {
public:
    // returns the longest substring of unique chars in s
    int lengthOfLongestSubstring(string s) {
        CharMap charMap;
        int size = 0;
        int max = 0;
        int startI = 0;
        int endI = 0;
        while(endI < s.size()) {
            if(charMap.has(s[endI])) {
                while(charMap.has(s[endI]) && startI < endI) {
                    charMap.erase(s[startI]);
                    --size;
                    ++startI;
                }
            } else {
                charMap.put(s[endI]);
                ++size;
                ++endI;
                if(size > max) {
                    max = size;
                }
            }
        }
        return max;
    }
};
