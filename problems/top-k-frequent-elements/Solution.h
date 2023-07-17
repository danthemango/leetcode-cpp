#include "../../common/common.h"
#include <cassert>

const unsigned int INIT_CAPACITY = 100;

class IntCount {
    public:
    unsigned int count = 0;
    int val;

    IntCount(const unsigned int& _count, const int& _val) : count(_count), val(_val) {}
    IntCount(const int& _val) : count(1), val(_val) {}
    unsigned int operator++() {
        return ++count;
    }
    bool operator<(const IntCount& other) const {
        return this->count < other.count;
    }

    friend ostream& operator<<(ostream& os, IntCount* ic) {
        os << ic->val << " (" << ic->count << ")";
        return os;
    }
};

class CountHeap {
    vector<IntCount*> arr;
    unsigned int capacity;
    unsigned int numElements;

    // sets the capacity
    void setCapacity(const unsigned int& _capacity) {
        capacity = _capacity;
        arr.resize(capacity);
    }

    // grow the heap if the heap is full
    void ensureCapacity() {
        while(capacity <= numElements) {
            setCapacity(capacity * 2);
        }
    }

    unsigned int getParentIdx(const unsigned int& i) {
        return (i-1)/2;
    }

    unsigned int getLeftIdx(const unsigned int& i) {
        return 2*i+1;
    }

    unsigned int getRightIdx(const unsigned int& i) {
        return 2*i+2;
    }

    // returns true if this node is larger than its parent
    bool largerThanParent(const unsigned int& i) {
        // check if root
        if(i == 0) {
            return false;
        }
        unsigned int parentI = getParentIdx(i);
        return *arr[parentI] < *arr[i];
    }

    // returns true if this is the root node
    bool isRoot(const unsigned int& i) {
        return i == 0;
    }

    // returns true if this node index has a left child
    bool hasLeftChild(const unsigned int& i) {
        unsigned int leftI = getLeftIdx(i);
        return leftI < numElements;
    }

    // returns true if this node index has a right child
    bool hasRightChild(const unsigned int& i) {
        unsigned int rightI = getRightIdx(i);
        return rightI < numElements;
    }

    // returns true if the value at index i is smaller than value at index j
    bool smallerThanIdx(const unsigned int& i, const unsigned int& j) {
        return *arr[i] < *arr[j];
    }

    // swaps the elements of the two indices
    void swapIdx(const unsigned int& i, const unsigned int& j) {
        IntCount* tmp = arr[j];
        arr[j] = arr[i];
        arr[i] = tmp;

        // update the index map
        idxMap[arr[i]->val] = i;
        idxMap[arr[j]->val] = j;
    }

    // moves element down the tree from index i, if needed
    void shiftDown(const unsigned int& i) {
        if(hasLeftChild(i)) {
            unsigned int leftI = getLeftIdx(i);
            if(smallerThanIdx(i, leftI)) {
                swapIdx(i, leftI);
            }
        }

        if(hasRightChild(i)) {
            unsigned int rightI = getRightIdx(i);
            if(smallerThanIdx(i, rightI)) {
                swapIdx(i, rightI);
            }
        }

        if(hasLeftChild(i)) {
            unsigned int leftI = getLeftIdx(i);
            shiftDown(leftI);
        }

        if(hasRightChild(i)) {
            unsigned int rightI = getRightIdx(i);
            shiftDown(rightI);
        }
    }

    // moves element up the tree from index i, if needed
    void shiftUp(const unsigned int& i) {
        if(!isRoot(i)) {
            unsigned int parentI = getParentIdx(i);
            if(smallerThanIdx(parentI, i)) {
                swapIdx(parentI, i);
            }
            shiftUp(parentI);
        }
    }

    // int value -> node
    std::map<int, IntCount*> intMap;
    // int value -> idx
    std::map<int, unsigned int> idxMap;

public:
    CountHeap() : numElements(0) {
        setCapacity(INIT_CAPACITY);
    }

    ~CountHeap() {
        for(unsigned int i = 0; i < numElements; i++) {
            delete arr[i];
        }
    }

    // increments the count of an integer seen
    void incVal(int val) {
        if(intMap.find(val) == intMap.end()) {
            ensureCapacity();
            unsigned int index = numElements;
            ++numElements;
            IntCount* intCount = new IntCount(val);
            intMap[val] = intCount; 
            idxMap[val] = index;
            arr[index] = intCount;
            shiftUp(index);
        } else {
            ++*intMap[val];
            unsigned int index = idxMap[val];
            shiftUp(index);
        }
    }

    IntCount* pop() {
        assert(numElements > 0);
        IntCount* result = arr[0];
        swapIdx(numElements-1, 0);
        --numElements;
        // swim to the bottom
        shiftDown(0);
        return result;
    }

    IntCount* top() {
        assert(numElements > 0);
        return arr[0];
    }

    friend ostream& operator<<(ostream& os, CountHeap* h) {
        bool first = true;
        for(unsigned int i = 0; i < h->numElements; i++) {
            IntCount* intCount = h->arr[i];
            if(first) first = false;
            else os << ", ";
            os << intCount;
        }
        os << '\n';
        return os;
    }

    bool empty() {
        return numElements == 0;
    }

    unsigned int size() {
        return numElements;
    }
};

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int> result;
        CountHeap* ch = new CountHeap();
        for(const int& num : nums) {
            ch->incVal(num);
        }

        while(k > 0) {
            IntCount* ic = ch->pop();
            result.push_back(ic->val);
            --k;
            delete ic;
        }

        delete ch;
        return result;
    }
};
