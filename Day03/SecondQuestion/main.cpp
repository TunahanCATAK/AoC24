#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <queue>

int main() {
    std::cout << "Day 03, SecondQuestion" << std::endl;

    std::ifstream file("../input.txt");
    int sum = 0;
    bool isEnabled = true;
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
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
        file.close();

    }
    else {
        std::cerr << "Unable to open file" << std::endl;
    }


    std::cout << "Sum: " << sum << std::endl;

    return 0;
}
