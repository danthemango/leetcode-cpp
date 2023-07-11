#include "../../common/common.h"
#include <map>
#include <queue>

/*
    start by creating a map of course num -> set of prerequisits
    for each course, check if we can finish the course:
    - if the course has no prerequisites, return true
    - create 'toVisit' queue of courses to check
    - while the toVisit queue isn't empty:
        - pop courseNum from the queue
        - if the course has no prerequisites, mark the course as can be completed
        - else if currCourse is equal to courseNum, we have a cycle, return false;
        - else, iterate through the list of prerequisites, adding them to the queue
*/

// keep track of whether a course can be completed
class CourseCache {
    std::map<int, bool> courses;
    public:
    // insert the course into the cache
    void insert(int courseNum) {
        courses[courseNum] = true;
    }

    // return true if this course has been inserted
    bool contains(int courseNum) {
        return courses.find(courseNum) != courses.end();
    }
};

// a set of prerequisits
class Prereqs {
    bool hasCourse(int courseNum) {
        return _mvi.find(courseNum) != _mvi.end();
    }

    void addCourse(int courseNum) {
        std::vector<int> prereqs;
        _mvi[courseNum] = prereqs;
    }

    std::map<int,std::vector<int>> _mvi;

    public:

    std::vector<int>& get(int courseNum) {
        if(!hasCourse(courseNum)) {
            addCourse(courseNum);
        }
        return _mvi[courseNum];
    }

    void add(int courseNum, int prereq) {
        auto& preqs = get(courseNum);
        preqs.push_back(prereq);
    }

    bool has(int courseNum) {
        if(!hasCourse(courseNum)) {
            return false;
        }
        auto& preqs = get(courseNum);
        return preqs.size() != 0;
    }

    void print() {
        for(const auto& mv : _mvi) {
            cout << "pre: " << mv.first << ": ";
            for(const auto& v : mv.second) {
                cout << v << ", ";
            }
            cout << endl;
        }
    }
};

class CourseSet {
    std::map<int, bool> _v;
    public:
    void insert(int courseNum) {
        _v[courseNum] = true;
    }
    bool contains(int courseNum) {
        return _v.find(courseNum) != _v.end();
    }
    void erase(int courseNum) {
        _v.erase(courseNum);
    }
};

// adds item to the queue only if it hasn't already been added
class CourseQueue {
    CourseSet courseSet;
    std::queue<int> courseQueue;
    public:
    void push(int courseNum) {
        if(!courseSet.contains(courseNum)) {
            courseSet.insert(courseNum);
            courseQueue.push(courseNum);
        }
    }
    bool empty() {
        return courseQueue.empty();
    }
    int front() {
        return courseQueue.front();
    }
    void pop() {
        int fc = courseQueue.front();
        courseSet.erase(fc);
        courseQueue.pop();
    }
};

class Edge {
    int pre;
    int post;
    public:
    Edge(int _pre, int _post) : pre(_pre), post(_post) { }
    std::string toString() {
        std::string result;
        result.append(std::to_string(pre));
        result.append("-");
        result.append(std::to_string(post));
        return result;
    }
};

class EdgeSet {
    map<string, bool> myMap;
    public:
    void insert(std::shared_ptr<Edge> edge) {
        myMap[edge->toString()] = true;
    }
    bool contains(std::shared_ptr<Edge> edge) {
        return myMap.find(edge->toString()) != myMap.end();
    }
};

class Solution {
public:
    Prereqs prereqs;
    CourseCache courseCache;

    // returns true if we can finish this course number
    bool canFinish(int courseNum) {

        if(courseCache.contains(courseNum)) {
            return true;
        }

        EdgeSet visited;
        CourseQueue toVisit;
        toVisit.push(courseNum);
        while(!toVisit.empty()) {
            int currCourse = toVisit.front();
            toVisit.pop();

            if(courseCache.contains(currCourse)) {
                continue;
            } else if(!prereqs.has(currCourse)) {
                courseCache.insert(currCourse);
                continue;
            }

            const std::vector<int>& prereqArr = prereqs.get(currCourse);
            for(const int& prereq : prereqArr) {
                auto edge = std::make_shared<Edge>(prereq, currCourse);
                if(courseCache.contains(prereq)) {
                    continue;
                } else if(!prereqs.has(prereq)) {
                    courseCache.insert(prereq);
                    continue;
                } else if(visited.contains(edge)) {
                    return false;
                } else {
                    visited.insert(edge);
                }
                toVisit.push(prereq);
            }
        }

        courseCache.insert(courseNum);
        return true;
    }

    // returns true if we can finish these courses
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        for(const vector<int>& prerequsite : prerequisites) {
            const int& post = prerequsite[0];
            const int& pre = prerequsite[1];
            prereqs.add(post, pre);
        }
        
        for(int i = 0; i < numCourses; i++) {
            if(!canFinish(i)) {
                return false;
            }
        }

        return true;
    }
};