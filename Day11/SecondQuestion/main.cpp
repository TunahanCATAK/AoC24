#include <iostream>
#include <fstream>
#include <forward_list>
#include <ranges>
#include <unordered_map>

std::ostream& operator<<(std::ostream& os, const std::forward_list<long>& list)
{
    for (const auto& number : list) {
        os << number << " ";
    }
    return os;
}

long stonesCountAfterNBlink(long number, int blinkCount)
{
    static std::unordered_map<long, long> cacheMap;
    if (blinkCount == 0)
    {
        return 1;
    }
    auto key = (number << 16) | blinkCount; // this trick for not using std::pair<long, int> in the unordered_map..
    if (cacheMap.contains(key)) // dynamic algorithm part - caching
    {
        return cacheMap[key];
    }
    if (number == 0)
    {
        cacheMap[key] = stonesCountAfterNBlink(1, blinkCount - 1);
        return cacheMap[key];
    }
    if (int digits = std::floor(std::log10(number) + 1); digits % 2 == 0 )
    {
        int half = std::pow(10, digits / 2);
        cacheMap[key] = stonesCountAfterNBlink(number / half, blinkCount - 1) + stonesCountAfterNBlink(number % half, blinkCount  -1);
        return cacheMap[key];
    }

    cacheMap[key] = stonesCountAfterNBlink(number * 2024, blinkCount - 1);
    return cacheMap[key];
}

int main() {
    std::cout << "Day 11, SecondQuestion" << std::endl;

    long stonesCount = 0;
    std::forward_list<long> numbers;
    std::ifstream file("../input.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            //std::cout << line << std::endl;

            for (const auto& x : std::views::split(line, ' '))
            {
                numbers.push_front(std::stol(std::string(x.begin(), x.end())));
            }

            for (auto number : numbers)
            {
                auto x = stonesCountAfterNBlink(number, 75);
                stonesCount += x;
            }
            
        }
    }
    else {
        std::cerr << "File could not be opened." << std::endl;
    }




    std::cout << "Stone Count: " << stonesCount << std::endl;

    return 0;
}
