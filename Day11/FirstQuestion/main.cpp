#include <iostream>
#include <fstream>
#include <forward_list>
#include <ranges>

std::ostream& operator<<(std::ostream& os, const std::forward_list<long>& list)
{
    for (const auto& number : list) {
        os << number << " ";
    }
    return os;
}

long countStones(const std::forward_list<long> stones, int maxTurnCount)
{
    std::forward_list<long> initStones = stones;
    int turnCounter = 0;
    while (turnCounter < maxTurnCount)
    {
        std::cout << initStones << std::endl;
        std::forward_list<long> newStones;
        for (long number : initStones)
        {
            if (number == 0)
            {
                newStones.push_front(1);
            }
            else if (int digits = std::floor(std::log10(number) + 1); digits % 2 == 0 )
            {
                int half = std::pow(10, digits / 2);
                newStones.push_front(number / half);
                newStones.push_front(number % half);
            }
            else {
                newStones.push_front(number * 2024);
            }
        }
        turnCounter++;

        initStones = newStones;
    }

    return std::distance(initStones.begin(), initStones.end());
}

int main() {
    std::cout << "Day 11, FirstQuestion" << std::endl;

    long stonesCount = 0;
    std::forward_list<long> numbers;
    std::ifstream file("../input.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;

            for (const auto& x : std::views::split(line, ' '))
            {
                numbers.push_front(std::stol(std::string(x.begin(), x.end())));
            }

            stonesCount += countStones(numbers, 25);
        }
    }
    else {
        std::cerr << "File could not be opened." << std::endl;
    }




    std::cout << "Stone Count: " << stonesCount << std::endl;

    return 0;
}
