#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <set>
#include <ranges>
#include <algorithm>

void groupConnectedNodes(std::unordered_map<std::string, std::set<std::string>>& graph,
                         std::set<std::string>& visitedNodes,
                         std::string currentNode,
                         std::set<std::string>& connectedNodes){
    visitedNodes.insert(currentNode);
    connectedNodes.insert(currentNode);

    for (const auto& node : graph[currentNode]){
        if (visitedNodes.find(node) == visitedNodes.end()){
            bool isFullyConnected = true;
            for (const auto& connectedNode : connectedNodes)
            {
                if (!graph[node].contains(connectedNode))
                {
                    isFullyConnected = false;
                    break;
                }
            }
            if (!isFullyConnected)
            {
                continue;
            }
            groupConnectedNodes(graph, visitedNodes, node, connectedNodes);
        }
    }
}

int main() {
    std::cout << "Day 23, SecondQuestion" << std::endl;

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

    std::vector<std::set<std::string>> connectedGroups;
    for (const auto& [key, value] : graph){
        std::set<std::string> visitedNodes;
        std::set<std::string> connectedNodes;
        groupConnectedNodes(graph, visitedNodes, key, connectedNodes);

        connectedGroups.push_back(connectedNodes);

    }

    const auto biggestConnectedGraph = std::ranges::max_element(connectedGroups, [](const auto& lhs, const auto& rhs){
        return lhs.size() < rhs.size();
    });

    std::cout << "Biggest connected group size: " << biggestConnectedGraph->size() << std::endl;
    std::ostringstream oss;
    const auto password = std::ranges::transform(biggestConnectedGraph->begin(), biggestConnectedGraph->end(), std::ostream_iterator<std::string>(oss, ","),
                                            [](const std::string& s) { return s; });

    std::cout << oss.str() << std::endl;

    return 0;
}
