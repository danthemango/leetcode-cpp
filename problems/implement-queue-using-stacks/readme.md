Example 1:

Input: commands = ["MyQueue", "push", "push", "peek", "pop", "empty"], args = [[], [1], [2], [], [], []]
Output: [null, null, null, 1, 1, false]

Explanation
MyQueue myQueue = new MyQueue();
myQueue.push(1); // queue is: [1]
myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
myQueue.peek(); // return 1
myQueue.pop(); // return 1, queue is [2]
myQueue.empty(); // return false