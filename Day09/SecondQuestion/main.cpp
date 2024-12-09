#include <iostream>
#include <fstream>
#include <list>

struct MemoryNode {
    int value;
    size_t size;
};

std::ostream& operator<<(std::ostream& os, const std::list<MemoryNode>& memory){
    for (const auto &item: memory) {
        if (item.value == -1)
        {
            for (size_t i = 0; i < item.size; i++)
            {
                os << ".";
            }
        }
        else
        {
            for (size_t i = 0; i < item.size; i++)
            {
                os  << item.value;
            }
        }
    }

    return os;
}

std::ostream &operator<<(std::ostream &os, const MemoryNode &memory) {
    os << memory.value << " :" << memory.size << "x times";
    return os;
}

int main() {
    std::cout << "Day 09, SecondQuestion" << std::endl;

    std::list<MemoryNode> memory;
    std::ifstream file("../input.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            int fileId = 0;
            for (auto i = 0; i < line.size(); i += 2) {
                std::cout << line[i] << std::endl;
                std::cout << line[i + 1] << std::endl;

                memory.push_back({fileId, (std::size_t) (line[i] - '0')});
                if (i + 1 < line.size())
                    memory.push_back({-1, (std::size_t) (line[i + 1] - '0')});

                fileId++;

            }

            auto backwardIt = memory.end();
            for (--backwardIt; backwardIt != memory.begin(); backwardIt--) {
                if (backwardIt->value != -1) {
                    //std::cout << "Candidate to Move: " << *backwardIt << std::endl;
                    auto firstEmptyPlace = std::find_if(memory.begin(), backwardIt,
                                                        [backwardIt](const MemoryNode &node) {
                                                            return node.value == -1 && node.size >= backwardIt->size;
                                                        });

                    if (firstEmptyPlace != memory.end()) {
                        size_t diffSize = firstEmptyPlace->size - backwardIt->size;
                        if (diffSize > 0) {
                            memory.insert(std::next(firstEmptyPlace), {firstEmptyPlace->value, diffSize});
                        }
                        std::swap(*firstEmptyPlace, *backwardIt);
                        backwardIt->size = firstEmptyPlace->size;

                    }
                    //std::cout << "After the move operation\n";

                }
            }
        }
    } else {
        std::cout << "File not found" << std::endl;
    }

    std::cout << memory << std::endl;

    // calculate checksum:
    long checksum = 0;
    int ind = 0;
    for (const auto &item : memory) {
        if (item.value == -1)
        {
            ind += item.size;
            continue;
        }

        for (size_t i = 0; i < item.size; i++)
        {
            checksum += item.value * ind++;
        }
    }


    std::cout << "Checksum: " << checksum << std::endl;

    return 0;
}
