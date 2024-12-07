# AoC24
Advent of Code 2024 


run the code with the following command: 
```bash
python3 createProj.py
```
## Day 1: 

## Day 2: 
_bool isSafe(const std::vector<int>& values)_ function time complexity analysis:

In the first question: 

- std::adjacent_difference --> O(n)
- std::find_if --> O(n)
- std::all_of --> O(n)

but there is no nested loops, so the overall time complexity is **O(n)**

In the second question:

- std::adjacent_difference --> O(n)
- std::find_if --> O(n)
- std::all_of --> O(n)

but this time, we have the nested loop to calculate subVector's safety, so the overall time complexity is **O(n<sup>2</sup>)**

Ideas to apply: 
- create an async function to calculate the safety of the subVector and have a 
thread pool to run while reading values from the input.txt. Something like Producer/Consumer. 

## Day 3:

Created a _co-routine based lazy file reading_ utility function. 
Which reads a file line by line and waits the caller to ask for the next line.
Tried to implement a kind of generator function in C++.

## Day 5: 
Tried to solve the problem with recursive function, but it was not efficient. I got 
a stack overflow error. So, I had to change the approach. 

Then I decided to use std::is_sorted() function. Which provides us a special comparison function.
But the time complexity of the solution became O(n<sup>2</sup>).
O(n) for the is_sorted function and O(n) for the comparison function.

## Day 6:
I've solved the second problem with a brute force approach, with adding '#' to all possible positions and find out to loop with iterating through the maze. 
There can be some nicer solutions with graphs, investigate it. 


