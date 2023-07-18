#include "../../common/common.h"

class Solution {
public:
    // next expected number -> num
    map<int, int> next2num;
    // previous expected number -> num
    map<int, int> prev2num;
    // num -> sequence id
    map<int, int> num2seqID;
    // sequence id -> count
    map<int, int> seqID2count;
    // next sequence id -> prev sequence id
    map<int, int> nextSeq2prevSeq;

    // add the next expected number to the maps
    void addNext(int num) {
        next2num[num+1] = num;
    }

    // add the previously expected number to the maps
    void addPrev(int num) {
        prev2num[num-1] = num;
    }

    // increment the count of this sequence
    // and returns the resulting count
    int incSeqCount(int seqID) {
        int count = 1;
        if(seqID2count.find(seqID) == seqID2count.end()) {
            seqID2count[seqID] = count;
        } else {
            count = ++seqID2count[seqID];
        }
        return count;
    }

    // returns true if this number has a sequence ID
    bool hasSeqId(int num) {
        return num2seqID.find(num) != num2seqID.end();
    }

    // returns true if the previous number is part of a sequence
    bool hasPrevSeqID(int num) {
        return hasSeqId(num-1);
    }

    // returns true if the next number is part of a sequence
    bool hasNextSeqID(int num) {
        return hasSeqId(num+1);
    }

    // returns the id of the previous sequence
    int getPrevSeqID(int num) {
        return num2seqID[num-1];
    }

    // returns the id of the previous sequence
    int getNextSeqID(int num) {
        return num2seqID[num+1];
    }

    // marks this number as part of its own sequence (sequence length of 1)
    void createSeqID(int num) {
        num2seqID[num] = num;
    }

    // mark number as part of a sequence
    void addNum2Seq(int num, int seqID) {
        num2seqID[num] = seqID;
    }

    // returns true if this sequence has another connected previous sequence
    bool hasPrevConSeq(int seqID) {
        return nextSeq2prevSeq.find(seqID) != nextSeq2prevSeq.end();
    }

    // returns the id of the previous connected sequence before this sequence
    int getPrevConSeqID(int seqID) {
        return nextSeq2prevSeq[seqID];
    }

    // returns the id of this sequence's earliest connected sequence
    int getEarliestSeqID(int num) {
        int seqID = getPrevSeqID(num);
        while(hasPrevConSeq(seqID)) {
            seqID = getPrevConSeqID(seqID);
        }
        return seqID;
    }

    // mark this sequence as connected to a previous sequence
    void connectSeq(int nextSeqID, int prevSeqID) {
        nextSeq2prevSeq[nextSeqID] = prevSeqID;
    }

    // adds the count of the next sequence id to the count of the previous sequence id
    // and returns the resulting count
    int add2prev(int nextSeqID, int prevSeqID) {
        seqID2count[prevSeqID] += seqID2count[nextSeqID];
        return seqID2count[prevSeqID];
    }

    int longestConsecutive(vector<int>& nums) {
        cout << "longestConsecutive" << endl;

        /*
            O(n*log(n)) time solution (map read and write I assume is O(log(n)) time)

            mark the previous and next expected values:
            for each number
            - mark the next expected value in a map
            - mark the previous expected value in a map

            set maxcount to 0
            look for previous and next expected values, and create sequence ids to correspond to a sequence of values
            for each number:
            - set count to 0
            - if it has a sequence id, skip it
            - else if there is no previous sequence id and no next sequence id,
                - create sequence id for num = num
                - inc count of sequence id and update count
            - else if there is a previous sequence id but not a next sequence id,
                - add it to the earliest previous sequence id (get prevSeqID while it exists)
                - inc count of sequence id and update count
            - else if there is a next sequence id but not a previous sequence id
                - add it to the next sequence id and update count
                - inc count of sequence id
            - else if there is a prev and a next seq id
                - add it to the earliest previous sequence id
                - inc count of prev seq id
                - add next sequence count to previous sequence count
                - update count
            - if count > maxcount update maxcount
        */

        for (const int& num : nums) {
            addNext(num);
            addPrev(num);
        }

        int maxCount = 0;
        for(const int& num : nums) {
            if(hasSeqId(num)) {
                continue;
            }

            bool hasPrev = hasPrevSeqID(num);
            bool hasNext = hasNextSeqID(num);
            int count;
            if(!hasPrev && !hasNext) {
                int seqID = num;
                createSeqID(seqID);
                count = incSeqCount(seqID);
            } else if(!hasNext) {
                int seqID = getEarliestSeqID(num);
                count = incSeqCount(seqID);
                addNum2Seq(num, seqID);
            } else if(!hasPrev) {
                int seqID = getNextSeqID(num);
                count = incSeqCount(seqID);
                addNum2Seq(num, seqID);
            } else {
                int prevSeqID = getEarliestSeqID(num);
                int nextSeqID = getNextSeqID(num);
                incSeqCount(prevSeqID);
                addNum2Seq(num, prevSeqID);
                connectSeq(nextSeqID, prevSeqID);
                count = add2prev(nextSeqID, prevSeqID);
            }
            maxCount = count > maxCount ? count : maxCount;                
        }

        return maxCount;
    }
};
