# leetcode-cpp

Some Leetcode problems solved with C++, with an
automatically generated Solution class testcase parser and runner.

Problem Runner
--------------
To run the testcases for a problem, first install Make and g++, then run:
- `make common`
- `make tools`
- `cd problems`
- `make makefiles`
- `cd <problem-name>` to enter the specific problem directory
- then cd into any of the problem directories and run `make` to build and execute the runner program

How this works (solution runner generator)
------------------------------------------
- after completing the 'readme.md' and 'Solution.h' files inside of a problem directory, the `make` command does the following:
    - Solution.h -> SolutionFunc.json
        - Using the program under tools/solution2json, we parse a 'Solution.h' file for the solution class,
        the solution function is assumed to be the last public function inside of the class.
        The program then builds a 'SolutionFunc.json' file which includes information of the argument names,
        argument types, and return type expected from that function.
    - SolutionFunc.json -> runner.cpp
        - The program under tools/json2runner accepts the 'SolutionFunc.json', and builds a 'runner.cpp' which will run the solution function.
    - runner.cpp + readme.md -> test case result
        - runner.cpp reads readme.md, and runs the solution function using the specified test case specifications.
        - the readme.md file must have three lines that begin with the following text, in-order, for each of the following in-order for each test case:
            - "Example N:" where N is an integer for the test case number
            - "Input: arg1 = val1, arg2 = val2, ..." which specifies the solution function argument names and values for this test case
            - "Output: val" which is the expected solution function return value for this test case
        - the input and output values are then transformed using a wrapper class, which parses the test case values into argument and return types that the solution function will accept, which are printed to the screen printed, then checked for success or failure
        - for example "Input: list = [1,2,3]" can be transformed into a `vector<int>`, `ListNode*`, `TreeNode*`, or other value types as needed
- wrapper classes
    - every type which is passed to/from a solution function must have a wrapper class implemented under 'common/', such as:
        - string -> TString
        - TreeNode* -> TTreeNode
        - vector<int> -> TVectorInt
        - and so on ... 
    - each of them requires a "get", "operator==", "tryParse", and "operator<<" function to be implemented to parse, check, and print the values
    - The list of known types and wrapper classes are specified inside of 'common/testCase.cpp'

Adding New Leetcode Problem
---------------------------
To create a functional problem directory called 'longest-common-subsequence' for example:
- run `cd problems`
- run `bash createNew.sh longest-common-subsequence` which will print out the following:
```
mkdir longest-common-subsequence
creating new files:
C:\Users\dan\Dropbox\practice\leetcode-cpp\problems\longest-common-subsequence\Solution.h
C:\Users\dan\Dropbox\practice\leetcode-cpp\problems\longest-common-subsequence\readme.md
```
- then write the solution class in 'Solution.h' and the testcases in 'readme.md'
- test the solution by running `make`


My Problem List
---------------
Linked List
- [x] reverse-linked-list
- [x] linked-list-cycle
- [x] merge-two-sorted-lists
- [x] merge-k-sorted-lists
- [x] remove-nth-node-from-end-of-list
- [x] reorder-list

Matrix
- [x] set-matrix-zeroes
- [x] spiral-matrix
- [x] rotate-image
- [x] word-search

String
- [x] longest-substring-without-repeating-characters
- [ ] Longest Repeating Character Replacement - https://leetcode.com/problems/longest-repeating-character-replacement/
- [ ] Minimum Window Substring - https://leetcode.com/problems/minimum-window-substring/
- [x] valid-anagram
- [x] group-anagrams
- [x] valid-parentheses
- [x] Valid Palindrome 
- [x] longest-palindromic-substring
- [x] Palindromic Substrings
- [ ] encode-and-decode-strings (premium)

Tree
- [x] maximum-depth-of-binary-tree
- [x] same-tree
- [x] invert-binary-tree
- [ ] Binary Tree Maximum Path Sum - https://leetcode.com/problems/binary-tree-maximum-path-sum/
- [x] binary-tree-level-order-traversal
- [x] serialize-and-deserialize-binary-tree
- [x] subtree-of-another-tree
- [x] construct-binary-tree-from-preorder-and-inorder-traversal
- [x] validate-binary-search-tree
- [x] kth-smallest-element-in-a-bst
- [x] Lowest Common Ancestor of BST
- [x] Implement Trie (Prefix Tree)
- [ ] Add and Search Word - https://leetcode.com/problems/add-and-search-word-data-structure-design/
- [ ] Word Search II - https://leetcode.com/problems/word-search-ii/

Heap
- [x] top-k-frequent-elements
- [ ] Find Median from Data Stream - https://leetcode.com/problems/find-median-from-data-stream/

Other
- [x] clone-graph
- [x] Counting Bits
- [x] Course Schedule
- [ ] Daily Temperatures
- [x] Evaluate Reverse Polish Notation
- [ ] Find Pivot Index
- [x] Fizz Buzz
- [x] Implement Queue using Stacks
- [x] Leaf-Similar Trees
- [x] longest-common-subsequence
- [x] maximum-difference-between-node-and-ancestor
- [ ] Maximum Product Subarray - https://leetcode.com/problems/maximum-subarray/
- [ ] Maximum Product of Splitted Binary Tree
- [ ] Merge Intervals
- [ ] Merge Intervals - https://leetcode.com/problems/merge-intervals/
- [ ] Non-overlapping Intervals - https://leetcode.com/problems/non-overlapping-intervals/
- [ ] Meeting Rooms (Leetcode Premium) - https://leetcode.com/problems/meeting-rooms/
- [ ] Meeting Rooms II (Leetcode Premium) - https://leetcode.com/problems/meeting-rooms-ii/
- [x] find-mode-in-binary-search-tree
- [x] add-two-numbers-ii
- [x] longest-consecutive-sequence