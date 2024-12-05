#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <ranges>
#include <algorithm>

void placeInDict(int first, int second, std::map<int, std::vector<int>> &relationMap)
{
    if (relationMap.find(first) == relationMap.end())
    {
        relationMap[first] = std::vector<int>{second};
    }
    else
    {
        relationMap[first].push_back(second);
    }
}

int main() {
    std::cout << "Day 05, FirstQuestion" << std::endl;

    std::map<int, std::vector<int>> relationMap;
    int sum = 0;

    std::ifstream file("../input.txt");
    if (file.is_open())
    {
        bool prepDone = false;
        std::string line;
        while (std::getline(file, line))
        {
            if (line == "")
            {
                prepDone = true;
                continue;
            }

            if (!prepDone)
            {
                int first, second;
                sscanf(line.c_str(), "%d|%d", &first, &second);
                placeInDict(first, second, relationMap);
            }
            else
            {
                // parse line into vector of ints (1,3,46,98) -> [1,3,46,98]
                std::vector<int> values;
                std::string value;
                std::stringstream ss(line);
                while (std::getline(ss, value, ','))
                {
                    values.push_back(std::stoi(value));
                }

                auto isSorted = std::is_sorted(values.begin(), values.end(), [&relationMap](int a, int b){

                    auto greaterThanB = relationMap.find(b);
                    return std::find(greaterThanB->second.begin(), greaterThanB->second.end(), a) == greaterThanB->second.end();

                });

                if (isSorted)
                {
                    auto middleItem = values.begin() + values.size()/2;
                    sum+= *middleItem;
                }

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
