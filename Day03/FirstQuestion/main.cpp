#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

int main() {
    std::cout << "Day 03, FirstQuestion" << std::endl;

    int sum = 0;

    std::ifstream file("../input.txt");
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::regex regexPattern(R"(mul\((\d+),(\d+)\))");
            std::smatch match;

            auto matchesBegin = std::sregex_iterator(line.begin(), line.end(), regexPattern);
            auto matchesEnd = std::sregex_iterator();

            for (auto it = matchesBegin; it != matchesEnd; ++it) {
                std::smatch match = *it;
                // std::cout << "Found: " << match.str() << " with values: "
                //          << match[1] << " and " << match[2] << std::endl;

                sum += std::stoi(match[1].str()) * std::stoi(match[2].str());
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
