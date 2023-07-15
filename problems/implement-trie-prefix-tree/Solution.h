#include "../../common/common.h"

class Trie {
    std::map<char, std::shared_ptr<Trie>> subTries;
    bool isWord;
public:
    Trie() : isWord(false) { }

    void insert(string word, unsigned int index) {
        if(word.size() == index) {
            isWord = true;
            return;
        }
        char c = word[index];
        if(subTries.find(c) == subTries.end()) {
            subTries[c] = std::make_shared<Trie>();
        }
        subTries[c]->insert(word, index+1);
    }
    
    void insert(string& word) {
        insert(word, 0);
    }

    bool search(string& word, unsigned int index) {
        if(word.size() == index) {
            return isWord;
        }
        char c = word[index];
        if(subTries.find(c) == subTries.end()) {
            return false;
        } else {
            return subTries[c]->search(word, index+1);
        }
    }
    
    bool search(string& word) {
        return search(word, 0);                
    }
    
    bool startsWith(string& prefix, unsigned int index) {
        if(prefix.size() == index) {
            return true;
        }
        char c = prefix[index];
        if(subTries.find(c) == subTries.end()) {
            return false;
        } else {
            return subTries[c]->startsWith(prefix, index+1);
        }
    }

    bool startsWith(string& prefix) {
        return startsWith(prefix, 0);
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

class Solution {
    public:
    vector<NullableBool> run(vector<string>& commands, vector<vector<string>>& args) {
        std::vector<NullableBool> resultArr;
        Trie* obj = nullptr;
        if(commands.size() != args.size()) {
            throw "number of commands must match number of args";
        }

        for(unsigned int i = 0; i < commands.size(); i++) {
            std::string& command = commands[i];
            std::vector<std::string>& arg = args[i];
            if(command == "Trie") {
                obj = new Trie();
                resultArr.push_back(NullableBool::nbNull);
            } else if(command == "insert") {
                obj->insert(arg[0]);
                resultArr.push_back(NullableBool::nbNull);
            } else if(command == "search") {
                bool boolResult = obj->search(arg[0]);
                NullableBool nbResult;
                if(boolResult) {
                    nbResult = NullableBool::nbTrue;
                } else {
                    nbResult = NullableBool::nbFalse;
                }
                resultArr.push_back(nbResult);
            } else if(command == "startsWith") {
                bool boolResult = obj->startsWith(arg[0]);
                NullableBool nbResult;
                if(boolResult) {
                    nbResult = NullableBool::nbTrue;
                } else {
                    nbResult = NullableBool::nbFalse;
                }
                resultArr.push_back(nbResult);
            }
        }
        if(obj != nullptr) {
            delete obj;
        }
        return resultArr;
    }
};