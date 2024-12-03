#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <queue>

#include "lazy_read_file.h"

int main() {
    std::cout << "Day 03, SecondQuestion" << std::endl;

    // std::ifstream file("../input.txt");
    int sum = 0;
    bool isEnabled = true;
    auto line_generator = tc::read_lines("../input.txt");
    for (std::string_view line_view; !(line_view = line_generator.next()).empty();)
    {
        std::string line(line_view);
        std::regex regexPattern(R"(do\(\)|don't\(\)|mul\(\d+,\d+\))");
        std::queue<std::string> matchedQueue;

        auto matchesBegin = std::sregex_iterator(line.begin(), line.end(), regexPattern);
        auto matchesEnd = std::sregex_iterator();

        for (auto it = matchesBegin; it != matchesEnd; ++it) {
            std::smatch match = *it;
            matchedQueue.push(match.str()); // Add the match to the queue
        }

        while (!matchedQueue.empty()) {
            auto item = matchedQueue.front();
            if (std::equal(item.begin(), item.end(), "do()"))
            {
                isEnabled = true;
            }
            else if (std::equal(item.begin(), item.end(), "don't()"))
            {
                isEnabled = false;
            }
            else if (isEnabled)
            {
                std::regex regexPattern(R"(mul\((\d+),(\d+)\))");
                std::smatch match;
                std::regex_search(item, match, regexPattern);
                sum += std::stoi(match[1].str()) * std::stoi(match[2].str());
            }
            matchedQueue.pop();
        }
    }

    std::cout << "Sum: " << sum << std::endl;

    return 0;
}
