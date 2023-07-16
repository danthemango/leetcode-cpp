#include "../../common/common.h"
#include <cassert>
#include <stack>

class MyQueue {
private:
    // moves all values to s1
    void moveToS1() {
        while(!s2.empty()) {
            int val = s2.top();
            s1.push(val);
            s2.pop();
        }
    }

    void moveToS2() {
        while(!s1.empty()) {
            int val = s1.top();
            s2.push(val);
            s1.pop();
        }
        
    }
public:
    std::stack<int> s1;
    std::stack<int> s2;
    // if true, s1 is the active stack
    bool s1Active = true;

    MyQueue() { }
    
    void push(int x) {
        if(!s1Active) {
            moveToS1();
            s1Active = true;
        }
        s1.push(x);
    }
    
    int pop() {
        if(s1Active) {
            moveToS2();
            s1Active = false;
        }
        int result = s2.top();
        s2.pop();
        return result;
    }
    
    int peek() {
        if(s1Active) {
            moveToS2();
            s1Active = false;
        }
        int result = s2.top();
        return result;
    }
    
    bool empty() {
        return s1.empty() && s2.empty();        
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

class Solution {
    public:
    vector<NullableResult> run(const vector<string>& commands, const vector<vector<int>>& args) const {
        std::vector<NullableResult> resultArr;
        MyQueue* obj = nullptr;
        if(commands.size() != args.size()) {
            throw "number of commands must match number of args";
        }

        for(unsigned int i = 0; i < commands.size(); i++) {
            const std::string& command = commands[i];
            const vector<int>& arg = args[i];
            if(command == "MyQueue") {
                assert(arg.size() == 0);
                obj = new MyQueue();
                resultArr.push_back(NullableResult::getNull());
            } else if(command == "push") {
                assert(arg.size() == 1);
                const int& val = arg[0];
                obj->push(val);
                resultArr.push_back(NullableResult::getNull());
            } else if(command == "pop") {
                assert(arg.size() == 0);
                int ires = obj->pop();
                NullableResult nres(ires);
                resultArr.push_back(nres);
            } else if(command == "peek") {
                assert(arg.size() == 0);
                int ires = obj->peek();
                NullableResult nres(ires);
                resultArr.push_back(nres);
            } else if(command == "empty") {
                assert(arg.size() == 0);
                bool bres = obj->empty();
                NullableResult nres(bres);
                resultArr.push_back(nres);
            } else {
                throw "unrecognized command";
            }
        }
        if(obj != nullptr) {
            delete obj;
        }
        return resultArr;
    }
};