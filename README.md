# leetcode-cpp
Some Leetcode problems solved with C++

Currently working on the blind 75

Usage
-----
To run one or more problem statements, first setup Make and gcc, then run:
- `make common`
- `make tools`
- then each directory under 'problems' has one leetcode question which can be ran and compiled
- `cd problems`
- `make makefiles`
- `cd <problem-name>` for any subdirectory
- then cd into any of the problem directories and run `make` to build and execute the runner program

How this works:

- Solution.h -> SolutionFunc.json
    - Using the program under tools/solution2json, we parse a 'Solution.h' file for the solution class,
    the pertinent function is assumed to be the last public function inside of the class,
    and the program builds a 'SolutionFunc.json' file which includes information of the argument names,
    argument types, and return type expected from that function.
- SolutionFunc.json -> runner.cpp
    - The program under tools/json2runner accepts the 'SolutionFunc.json', and builds a 'runner.cpp' which
runs the solution function using those expected argument and return types.
- runner.cpp + readme.md -> test case result
    - runner.cpp accepts test case specifications from readme.md, and transforms them into C++
    objects to be passed to the solution function, and an output value which result is a 'success' or a 'fail' result if this expected output value matches the actual output value
- wrapper classes
    - every type which is passed to/from a solution function must have a wrapper class, such as:
        - string -> TString
        - TreeNode* -> TTreeNode
        - vector<int> -> TVectorInt
        - and so on ... 
    - each of them requires a "get", "operator==", "tryParse", and "operator<<" function to be implemented.

TODO
----
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
- [ ] Longest Common Subsequence
- [ ] Maximum Difference Between Node and Ancestor
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