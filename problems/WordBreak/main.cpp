#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <map>

using namespace std;

/*
Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of one or more dictionary words.

Note that the same word in the dictionary may be reused multiple times in the segmentation.

Example 1:

Input: s = "leetcode", wordDict = ["leet","code"]
Output: true
Explanation: Return true because "leetcode" can be segmented as "leet code".

Example 2:

Input: s = "applepenapple", wordDict = ["apple","pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
Note that you are allowed to reuse a dictionary word.

Example 3:

Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: false
 

Constraints:

1 <= s.length <= 300
1 <= wordDict.length <= 1000
1 <= wordDict[i].length <= 20
s and wordDict[i] consist of only lowercase English letters.
All the strings of wordDict are unique.
*/

/*
create a map of the words in the dictionary
*/
class WordMap {
    public:
    map<string, bool> iMap;
    // add word to map
    void add(string word) {
        iMap[word] = true;
    }
    // return true if the word is in the map
    bool hasWord(string word) {
        return iMap.find(word) != iMap.end();
    }
};

/* save the results for each run of wordBreak int values */
class ResultsMemo {
    public:
    map<int, map<int, bool>> memo;

    void saveMemo(int p1, int p2, bool result) {
        memo[p1][p2] = result;
    }

    // returns true if result is in the memo
    bool hasMemo(int p1, int p2) {
        return memo.find(p1) != memo.end() && memo[p1].find(p2) != memo[p1].end();        
    }

    bool getMemo(int p1, int p2) {
        return memo[p1][p2];
    }
};

class Solution {
public:
    /*
        start by creating map 'wordMap' of the strings in the wordDict
        Use start position p1 and end position p2
        let string sStart be the string created between p1 and p2, inclusively
        if p2 is at the last letter of s
        - return true iff sStart is a word in wordMap
        else if sStart is not in wordMap
        - return true if a wordBreak may be created with a larger sStart (re-run with p2+1)
        else if sStart is in wordMap
        - return true if a wordBreak may be created with the remainder of the input string
        - (re-run with p1 = p2+1 and p2 = p1)
    */

    WordMap wordMap;
    ResultsMemo resultsMemo;

    bool wordBreak(string s, int p1, int p2) {
        if(resultsMemo.hasMemo(p1, p2)) {
            return resultsMemo.getMemo(p1, p2);
        }

        bool result;

        if(p2 >= s.size()) {
            result = false;
        } else {
            string sStart = s.substr(p1, p2+1-p1);

            if(p2 == s.size()-1) {
                result = wordMap.hasWord(sStart);
            } else if(!wordMap.hasWord(sStart)) {
                result = wordBreak(s, p1, p2+1);
            } else {
                result = wordBreak(s, p2+1, p2+1) || wordBreak(s, p1, p2+1);
            }
        }
        resultsMemo.saveMemo(p1, p2, result);
        return result;
    }

    bool wordBreak(string s, vector<string>& wordDict) {
        for(string& word : wordDict) {
            wordMap.add(word);
        }
        return wordBreak(s, 0, 0);
    }
};

std::string vector2string(std::vector<std::string> inputStringList) {
    stringstream ss;
    ss << '[';
    bool first = true;
    for (const std::string &inputString : inputStringList)
    {
        if (!first)
        {
            ss << ',';
        }
        else
        {
            first = false;
        }

        ss << '"' << inputString << '"';
    }
    ss << ']';

    std::string result;
    ss >> result;
    return result;
}

struct SolutionInput {
    // input string
    string s;
    // input word dictionary
    vector<string> wordDict;
    // expected return result
    bool exp;
};

void runSolution(SolutionInput& si) {
    Solution solution;
    bool result = solution.wordBreak(si.s, si.wordDict);
    cout << "input: " << si.s << ", " << vector2string(si.wordDict) << endl;
    cout << "result: " << result << endl;
    cout << (result == si.exp ? "Success." : "Fail.") << endl;
}

int main() {
    vector<SolutionInput> solutionInputs{
        {"leetcode", {"leet", "code"}, true},
        {"applepenapple", {"apple", "pen"}, true},
        {"catsandog", {"cats", "dog", "sand", "and", "cat"}, false},
        {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab", {"a", "aa", "aaa", "aaaa", "aaaaa", "aaaaaa", "aaaaaaa", "aaaaaaaa", "aaaaaaaaa", "aaaaaaaaaa"}, false},
    };

    for(SolutionInput& si : solutionInputs) {
        runSolution(si);
    }
}
