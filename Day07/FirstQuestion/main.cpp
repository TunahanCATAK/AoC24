#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>
#include <queue>
#include <deque>

int main() {
    std::cout << "Day 07, FirstQuestion" << std::endl;
    std::queue<long> numbers;
    long totalNumbers = 0;
    std::ifstream file("../input.txt");
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            long targetNumber;
            std::regex regexPattern(R"((\d+):([\d\s]+))");
            std::smatch matches;

            if (std::regex_match(line, matches, regexPattern)) {
                targetNumber = std::stol(matches[1].str());

                std::string rest = matches[2].str();

                std::istringstream iss(rest);
                long number;
                while (iss >> number) {
                    numbers.push(number);
                }
            }

            // calculate:
            std::deque<long long> calculations;
            // the first two numbers
            auto first = numbers.front();
            numbers.pop();
            auto second = numbers.front();
            numbers.pop();

            calculations.push_back(first + second);
            calculations.push_back(first * second);

            std::deque<long long> temp;
            while (!calculations.empty())
            {

                if (numbers.empty())
                {
                    if (std::find(calculations.begin(), calculations.end(), targetNumber) != calculations.end())
                    {
                        totalNumbers += targetNumber;
                        std::cout << "Found: " << targetNumber << std::endl;
                    }
                    break;
                }

                auto current = calculations.front();
                calculations.pop_front();

                temp.push_back((long long)current + numbers.front());
                temp.push_back((long long)current * numbers.front());

                if (calculations.empty())
                {
                    calculations = temp;
                    numbers.pop();
                    while (!temp.empty())
                        temp.pop_back();
                }
            }

        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file" << std::endl;
    }


    std::cout << "Total numbers: " << totalNumbers << std::endl;

    return 0;
}
