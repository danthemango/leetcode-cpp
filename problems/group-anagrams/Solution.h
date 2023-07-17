#include "../../common/common.h"

class Solution {
public:
    // returns a map key which uniquely identifies the count of the number of times each char appears in the string
    std::string getCountKey(std::string& str) {
        std::map<char, unsigned int> countMap;

        for(const char& c : str) {
            if(countMap.find(c) == countMap.end()) {
                countMap[c] = 1;
            } else {
                ++countMap[c];
            }
        }

        std::string result;
        for(auto& pair : countMap) {
            const char& c = pair.first;
            unsigned int& count = pair.second;
            result.push_back(c);
            result.append(std::to_string(count));
        }
        return result;
    }

    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // one anagram string -> anagram string list
        std::map<std::string, std::vector<std::string>> anagramSet;

        // for each string
        for(std::string& str : strs) {
            std::string key = getCountKey(str);
            if(anagramSet.find(key) == anagramSet.end()) {
                std::vector<std::string> arr;
                arr.push_back(str);
                anagramSet[key] = arr;
            } else {
                std::vector<std::string>& arr = anagramSet[key];
                arr.push_back(str);
            }
        }

        // create a vector of anagram set values
        std::vector<std::vector<std::string>> result;
        for(auto& pair : anagramSet) {
            std::vector<std::string>& item = pair.second;
            result.push_back(item);
        }

        return result;
    }
};
