# AoC24
Advent of Code 2024 


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

but this time, we have the nested loop to calculate subVector's safety, so the overall time complexity is **O(n^2)**
