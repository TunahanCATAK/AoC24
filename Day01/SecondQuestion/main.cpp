#include <iostream>
#include <fstream>
#include <set>

int main() {
    std::cout << "Day 01, SecondQuestion" << std::endl;

    int left, right;
    std::multiset<int> leftDetectives, rightDetectives;

    std::ifstream file("../../input.txt");

    if (file.is_open())
    {
        while (file >> left >> right)
        {
            leftDetectives.insert(left);
            rightDetectives.insert(right);
        }

        file.close();
    }
    else {
        std::cerr << "Unable to open file" << std::endl;
    }

    int similarityScore = 0;
    for (auto value : leftDetectives)
    {
        similarityScore += value * rightDetectives.count(value);
    }

    std::cout << "Similarity Score: " << similarityScore << std::endl;

    return 0;
}
