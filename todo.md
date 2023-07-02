
how to run one script
=====================
- [ ] create common.h, and include it in the solution
- [ ] get Solution.cpp to compile with generated runner

- [ ] (figure out how to debug a script without proper headers)
    - [ ] create a common.h file, with -I../../common in the makefile
    - [ ] use directive: '#line linenum filename'
    - [ ] write script to parse and create ifndefs in the headers
- [ ] parse solution class
- [ ] create input parser object from solution class
    - note: the sample solution classes should only have one function,
        however I shall assume the function needed to answer the question
        is the very last one in the class, thereby allowing all extra helper
        functions to exist before the answer

I will create an enum of known input types
and a list of acceptable types of that kind
that way "string" and "std::string" will both be accepted
then, this will be added to the parser

- [ ] create TestCase class
    - fill from input string
    - fill from output string
    - fill testcase number/name 
    - create testcase parser for file parsing
    - fill testcase from input and output strings

- [ ] create runner.cpp generator:
  - create #include values from input and output types
    - vector, string, Tree, Node, ..., as needed
  - create Solution solution;
  - create std::vector<TestCase>;
  - accept as a string the input values,
    - create a map, and for each function argument:
        - associates the arg name to the arg contents as a string
  - convert arg content string to arg type
  - run the solution function

- [ ] create script which uses directory name,
    and creates main.cpp, compiles solution, and runs with readme input

- [ ] create directory and fill directory
    - [ ] resolve url or problem name
    - [ ] resolve the problem text
    - [ ] get solution script format
    - [ ] parse solution class function name and definitions
    - [ ] of the argument types, generate includes
    - [ ] generate script runner expecting a string of input values
    - [ ] after determining argument names and types, look for them in the input string
        - allow for optional namespace std::
        - create dictionary of known input types
    - [ ] after determining return type, parse 'output:' string
        - create dictionary of known output types
    - [ ] generate SolutionRunner.cpp (and .h files?)
        - possibly create 'out/' directory first

Tools
=====
- [ ] create script to fetch problem statement
- [x] create simple Readme Parser
- [ ] script to create a new directory from url
- [ ] script to fetch problem statement from url
- [x] create common directory that compiles some extra functionality
- [x] finish tree namespace
- [x] finish kthsmallest tree problem
- [x] move tree namespace to common/

Cpp set
=======
- [x] Clone Graph - https://leetcode.com/problems/clone-graph/
- [x] Counting Bits
- [ ] Course Schedule
- [ ] Daily Temperatures
- [ ] Evaluate Reverse Polish Notation
- [ ] Find Pivot Index
- [x] Fizz Buzz
- [ ] Implement Queue using Stacks
- [ ] Leaf-Similar Trees
- [ ] Longest Common Subsequence
- [ ] Maximum Difference Between Node and Ancestor
- [ ] Maximum Product Subarray
- [ ] Maximum Product of Splitted Binary Tree
- [ ] Merge Intervals
- [ ] Merge k Sorted Lists
- [ ] Middle of the Linked List
- [ ] Minimum Average Difference
- [ ] Minimum Falling Path Sum
- [ ] Missing Number
- [ ] Nearest Exit from Entrance in Maze
- [x] Number of 1 Bits
- [ ] Number of Steps to Reduce a Number to Zero
- [ ] Odd Even Linked List
- [ ] Question - Language
- [ ] Ransom Note
- [ ] Richest Customer Wealth
- [ ] Running Sum of 1d Array
- [ ] Tenth Line - bash
- [ ] Time Based Key-Value Store
- [ ] Ugly Number
- [x] Unique Paths
- [ ] Valid Anagram
- [x] Word Break
- [ ] List item

Blind 75
========

Array
- [x] Two Sum - https://leetcode.com/problems/two-sum/
    - [ ] run in cpp
- [ ] Best Time to Buy and Sell Stock - https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
- [ ] Contains Duplicate - https://leetcode.com/problems/contains-duplicate/
- [ ] Product of Array Except Self - https://leetcode.com/problems/product-of-array-except-self/
- [ ] Maximum Subarray - https://leetcode.com/problems/maximum-subarray/
- [ ] Maximum Product Subarray - https://leetcode.com/problems/maximum-product-subarray/
- [ ] Find Minimum in Rotated Sorted Array - https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
- [ ] Search in Rotated Sorted Array - https://leetcode.com/problems/search-in-rotated-sorted-array/
- [ ] 3 Sum - https://leetcode.com/problems/3sum/
- [ ] Container With Most Water - https://leetcode.com/problems/container-with-most-water/

Binary
- [ ] Sum of Two Integers - https://leetcode.com/problems/sum-of-two-integers/
- [ ] Number of 1 Bits - https://leetcode.com/problems/number-of-1-bits/
- [ ] Counting Bits - https://leetcode.com/problems/counting-bits/
- [ ] Missing Number - https://leetcode.com/problems/missing-number/
- [ ] Reverse Bits - https://leetcode.com/problems/reverse-bits/
- [ ] Dynamic Programming
- [ ] Climbing Stairs - https://leetcode.com/problems/climbing-stairs/
- [ ] Coin Change - https://leetcode.com/problems/coin-change/
- [ ] Longest Increasing Subsequence - https://leetcode.com/problems/longest-increasing-subsequence/
- [ ] Longest Common Subsequence - https://leetcode.com/problems/longest-common-subsequence/
- [ ] Word Break Problem - https://leetcode.com/problems/word-break/
- [ ] Combination Sum - https://leetcode.com/problems/combination-sum-iv/
- [ ] House Robber - https://leetcode.com/problems/house-robber/
- [ ] House Robber II - https://leetcode.com/problems/house-robber-ii/
- [ ] Decode Ways - https://leetcode.com/problems/decode-ways/
- [ ] Unique Paths - https://leetcode.com/problems/unique-paths/
- [ ] Jump Game - https://leetcode.com/problems/jump-game/

Graph
- [x] Clone Graph - https://leetcode.com/problems/clone-graph/
- [ ] Course Schedule - https://leetcode.com/problems/course-schedule/
- [ ] Pacific Atlantic Water Flow - https://leetcode.com/problems/pacific-atlantic-water-flow/
- [ ] Number of Islands - https://leetcode.com/problems/number-of-islands/
- [ ] Longest Consecutive Sequence - https://leetcode.com/problems/longest-consecutive-sequence/
- [ ] Alien Dictionary (Leetcode Premium) - https://leetcode.com/problems/alien-dictionary/
- [ ] Graph Valid Tree (Leetcode Premium) - https://leetcode.com/problems/graph-valid-tree/
- [ ] Number of Connected Components in an Undirected Graph (Leetcode Premium) - https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/

Interval
- [ ] Insert Interval - https://leetcode.com/problems/insert-interval/
- [ ] Merge Intervals - https://leetcode.com/problems/merge-intervals/
- [ ] Non-overlapping Intervals - https://leetcode.com/problems/non-overlapping-intervals/
- [ ] Meeting Rooms (Leetcode Premium) - https://leetcode.com/problems/meeting-rooms/
- [ ] Meeting Rooms II (Leetcode Premium) - https://leetcode.com/problems/meeting-rooms-ii/

Linked List
- [ ] Reverse a Linked List - https://leetcode.com/problems/reverse-linked-list/
- [ ] Detect Cycle in a Linked List - https://leetcode.com/problems/linked-list-cycle/
- [ ] Merge Two Sorted Lists - https://leetcode.com/problems/merge-two-sorted-lists/
- [ ] Merge K Sorted Lists - https://leetcode.com/problems/merge-k-sorted-lists/
- [ ] Remove Nth Node From End Of List - https://leetcode.com/problems/remove-nth-node-from-end-of-list/
- [ ] Reorder List - https://leetcode.com/problems/reorder-list/

Matrix
- [ ] Set Matrix Zeroes - https://leetcode.com/problems/set-matrix-zeroes/
- [ ] Spiral Matrix - https://leetcode.com/problems/spiral-matrix/
- [ ] Rotate Image - https://leetcode.com/problems/rotate-image/
- [ ] Word Search - https://leetcode.com/problems/word-search/

String
- [ ] Longest Substring Without Repeating Characters - https://leetcode.com/problems/longest-substring-without-repeating-characters/
- [ ] Longest Repeating Character Replacement - https://leetcode.com/problems/longest-repeating-character-replacement/
- [ ] Minimum Window Substring - https://leetcode.com/problems/minimum-window-substring/
- [ ] Valid Anagram - https://leetcode.com/problems/valid-anagram/
- [ ] Group Anagrams - https://leetcode.com/problems/group-anagrams/
- [ ] Valid Parentheses - https://leetcode.com/problems/valid-parentheses/
- [ ] Valid Palindrome - https://leetcode.com/problems/valid-palindrome/
- [ ] Longest Palindromic Substring - https://leetcode.com/problems/longest-palindromic-substring/
- [ ] Palindromic Substrings - https://leetcode.com/problems/palindromic-substrings/
- [ ] Encode and Decode Strings (Leetcode Premium) - https://leetcode.com/problems/encode-and-decode-strings/

Tree
- [ ] Maximum Depth of Binary Tree - https://leetcode.com/problems/maximum-depth-of-binary-tree/
- [ ] Same Tree - https://leetcode.com/problems/same-tree/
- [ ] Invert/Flip Binary Tree - https://leetcode.com/problems/invert-binary-tree/
- [ ] Binary Tree Maximum Path Sum - https://leetcode.com/problems/binary-tree-maximum-path-sum/
- [ ] Binary Tree Level Order Traversal - https://leetcode.com/problems/binary-tree-level-order-traversal/
- [ ] Serialize and Deserialize Binary Tree - https://leetcode.com/problems/serialize-and-deserialize-binary-tree/
- [ ] Subtree of Another Tree - https://leetcode.com/problems/subtree-of-another-tree/
- [ ] Construct Binary Tree from Preorder and Inorder Traversal - https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
- [ ] Validate Binary Search Tree - https://leetcode.com/problems/validate-binary-search-tree/
- [x] Kth Smallest Element in a BST - https://leetcode.com/problems/kth-smallest-element-in-a-bst/
- [ ] Lowest Common Ancestor of BST - https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
- [ ] Implement Trie (Prefix Tree) - https://leetcode.com/problems/implement-trie-prefix-tree/
- [ ] Add and Search Word - https://leetcode.com/problems/add-and-search-word-data-structure-design/
- [ ] Word Search II - https://leetcode.com/problems/word-search-ii/

Heap
- [ ] Merge K Sorted Lists - https://leetcode.com/problems/merge-k-sorted-lists/
- [ ] Top K Frequent Elements - https://leetcode.com/problems/top-k-frequent-elements/
- [ ] Find Median from Data Stream - https://leetcode.com/problems/find-median-from-data-stream/

Bonus - https://hackernoon.com/14-patterns-to-ace-any-coding-interview-question-c5bb3357f6ed

Optional
- [ ] create querySelector for XML
- [ ] create LMMS xml -> sonic PI converter
- [ ] test in-place iofstream character replacer