#include <iostream>
#include <fstream>
#include <list>

std::ostream& operator<<(std::ostream& os, const std::list<int>& memory)
{
    for (const auto& item : memory)
    {
        os << item << " ";
    }
    return os;
}

int main() {
    std::cout << "Day 09, FirstQuestion" << std::endl;

    std::list<int> memory;

    std::ifstream file("../input.txt");
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::cout << line << std::endl;
            int fileId = 0;
            for (auto i = 0; i < line.size(); i+=2)
            {
                std::cout << line[i] << std::endl;
                std::cout << line[i+1] << std::endl;
                for (int j = 0; j < (line[i] - '0'); j++)
                {
                    memory.push_back(fileId);
                }
                for (int j= 0; j < (line[i+1] - '0'); j++)
                {
                    memory.push_back(-1);
                }

                fileId++;

            }

            std::cout << "Memory Original: " << memory << std::endl;

            auto forwardIt = memory.begin();
            auto backwardIt = memory.end();
            for (--backwardIt; forwardIt != backwardIt; forwardIt++)
            {
                std::cout << *forwardIt << " " << *backwardIt << std::endl;
                if (*forwardIt == -1)
                {
                    while (*backwardIt == -1)
                        backwardIt--;

                    std::swap(*forwardIt, *backwardIt);
                }
            }

        }
    }
    else {
        std::cout << "Unable to open file" << std::endl;
        return 1;
    }

    std::cout << "Memory: " << memory << std::endl;

    long checksum = 0;
    int ind = 0;
    for (const auto& item : memory)
    {
        if (item == -1)
            continue;

        checksum += item*ind++;
    }

    std::cout << "Checksum: " << checksum << std::endl;

    return 0;
}
