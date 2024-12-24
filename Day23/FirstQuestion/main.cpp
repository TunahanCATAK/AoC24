#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <set>
#include <algorithm>

std::ostream& operator<<(std::ostream& os, const std::unordered_map<std::string, std::set<std::string>>& graph){
    for (const auto& [key, value] : graph){
        os << key << " : ";
        for (const auto& val : value){
            os << val << " ";
        }
        os << std::endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::set<std::tuple<std::string, std::string, std::string>>& threeConnectedComputers){
    for (const auto& [first, second, third] : threeConnectedComputers){
        os << first << " " << second << " " << third << std::endl;
    }
    return os;
}

std::tuple<std::string, std::string, std::string> sortTuple(
        const std::tuple<std::string, std::string, std::string>& inputTuple)
{
    std::array<std::string, 3> elements = {std::get<0>(inputTuple), std::get<1>(inputTuple), std::get<2>(inputTuple)};
    std::sort(elements.begin(), elements.end());

    return {elements[0], elements[1], elements[2]};
}


int main() {
    std::cout << "Day 23, FirstQuestion" << std::endl;

    std::unordered_map<std::string, std::set<std::string>> graph;

    std::ifstream file("../input.txt");
    if (file.is_open()){
        std::string line;
        while (std::getline(file, line)){
            // Parse the line xx-yy into two strings
            std::string head = line.substr(0, line.find("-"));
            std::string tail = line.substr(line.find("-") + 1);

            graph[head].insert(tail);
            graph[tail].insert(head);
        }
    }
    else {
        std::cerr << "Unable to open file" << std::endl;
    }

    std::set<std::tuple<std::string, std::string, std::string>> threeConnectedComputers;
    for (const auto& [key, value] : graph){
        for (const auto& val : value){
            for (const auto& val2 : graph[val]){
                if (val2 != key && value.find(val2) != value.end()){
                    std::tuple<std::string, std::string, std::string> threeConnectedComputersTuple = {key, val, val2};
                    threeConnectedComputersTuple = sortTuple(threeConnectedComputersTuple);
                    threeConnectedComputers.insert(threeConnectedComputersTuple);
                }
            }
        }
    }


    int total = 0;

    for (const auto& [first, second, third] : threeConnectedComputers){
        if (first[0] == 't' || second[0] =='t' || third[0] == 't') {
            total++;
            std::cout << first << " " << second << " " << third << std::endl;
        }
    }

    std::cout << "Total: " << total << std::endl;

//
//
//    std::cout << graph << std::endl;
//    std::cout << "Three connected computers: " << threeConnectedComputers.size() << std::endl;
//    std::cout << "Three connected computers: " << threeConnectedComputers << std::endl;

    return 0;
}
