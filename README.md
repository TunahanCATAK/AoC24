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
