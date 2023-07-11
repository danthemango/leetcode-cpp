There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
Return true if you can finish all courses. Otherwise, return false.


Example 29:
Input: numCourses = 4, prerequisites = [[0,1],[3,1],[1,3],[3,2]]
Output: false

 
Example 1:

Input: numCourses = 2, prerequisites = [[1,0]]
Output: true
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0. So it is possible.
Example 2:

Input: numCourses = 2, prerequisites = [[1,0],[0,1]]
Output: false
Explanation: There are a total of 2 courses to take. 
To take course 1 you should have finished course 0, and to take course 0 you should also have finished course 1. So it is impossible.

Example 3:
Input: numCourses = 2, prerequisites = [[0,1]]
Output: true

Example 4:
Input: numCourses = 3, prerequisites = [[2,1],[1,0]]
Output: true

Example 5:
Input: numCourses = 3, prerequisites = [[2,1],[1,0],[0,2]]
Output: false

Example 43:
Input: numCourses = 5, prerequisites = [[1,4],[2,4],[3,1],[3,2]]
Output: true

Example 51:
Input: numCourses = 7, prerequisites = [[1,0],[0,3],[0,2],[3,2],[2,5],[4,5],[5,6],[2,4]]
Output: true