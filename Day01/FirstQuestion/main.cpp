#include <iostream>
#include <fstream>
#include <set>

int main() {
    std::cout << "Day 01, FirstQuestion" << std::endl;

    int left, right;
    std::multiset<int> leftDetectives, rightDetectives;
    int distance = 0;

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

    auto rightIt = rightDetectives.begin();
    for (auto value : leftDetectives)
    {
        distance += abs(value - *rightIt);
        rightIt++;
    }

    std::cout << "Distance: " << distance << std::endl;

    return 0;
}
