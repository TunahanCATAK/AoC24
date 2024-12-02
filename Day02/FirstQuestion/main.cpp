#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
#include <algorithm>

bool isSafe(const std::vector<int>& values)
{
    std::vector<int> differences(values.size());

    std::adjacent_difference(values.begin(), values.end(), differences.begin());
    auto it = std::find_if(differences.begin() + 1, differences.end(), [](int value) {return abs(value) > 3;});
    if (it != differences.end())
    {
        return false;
    }

    bool allPositive = std::all_of(differences.begin() + 1, differences.end(), [](int value) {return value > 0;});
    bool allNegative = std::all_of(differences.begin() + 1, differences.end(), [](int value) {return value < 0;});

    return allPositive || allNegative;
}

int main() {
    std::cout << "Day 02, FirstQuestion" << std::endl;

    int safeCount = 0;
    std::ifstream file("../../input.txt");
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::vector<int> values;
            std::istringstream iss(line);
            int value;
            while (iss >> value)
            {
                values.push_back(value);
            }
            if (isSafe(values))
            {
                safeCount++;
            }
        }
        file.close();

    }
    else {
        std::cerr << "Unable to open file" << std::endl;
    }

    std::cout << "Safe Count: " << safeCount << std::endl;
    return 0;
}
