#include <iostream>
#include <fstream>
#include <vector>
#include <set>

std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<int>>& topographicMap) {
    for (const auto& row : topographicMap) {
        for (int cell : row) {
            os << cell << " ";
        }
        os << std::endl;
    }
    return os;
}

int main() {
    std::cout << "Day 10, FirstQuestion" << std::endl;

    std::vector<std::vector<int>> topographicMap;
    std::ifstream file("../input.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            // todo: create a view to convert a range to a specific range
            // to<vector<int>>(line) something like that.
            std::vector<int> row;
            for (char c : line) {
                row.push_back(c - '0');
            }
            topographicMap.push_back(row);
        }
    }
    else {
        std::cerr << "File could not be opened." << std::endl;
    }

    std::stack<std::tuple<std::pair<int, int>, int>> travelledRoutes; // (x, y), direction index
    std::vector<std::pair<int, int>> directions = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    int sumOfTrailHeadRouteCounts = 0;
    std::pair<int, int> currentPosition = {0, 0};
    int currentDirection = 0;
    for (int i = 0; i < topographicMap[0].size(); i++) {
        for (int j = 0; j < topographicMap.size(); j++) {
            currentPosition = {j, i};
            currentDirection = 0;

            if (topographicMap[currentPosition.first][currentPosition.second] == 0) {

                travelledRoutes.push({currentPosition, currentDirection});

                while (!travelledRoutes.empty())
                {
                    if (std::get<1>(travelledRoutes.top()) == directions.size())
                    {
                        travelledRoutes.pop();
                        if (travelledRoutes.empty())
                        {
                            break;
                        }
                        std::get<1>(travelledRoutes.top())++;
                        continue;
                    }
                    int nextX = std::get<0>(travelledRoutes.top()).first + directions[std::get<1>(travelledRoutes.top())].first;
                    int nextY = std::get<0>(travelledRoutes.top()).second + directions[std::get<1>(travelledRoutes.top())].second;

                    int prevValue = topographicMap[std::get<0>(travelledRoutes.top()).first][std::get<0>(travelledRoutes.top()).second];
                    travelledRoutes.push({{nextX, nextY}, 0});

                    if (nextX < 0 || nextX >= topographicMap.size() || nextY < 0 || nextY >= topographicMap[0].size() ||
                        topographicMap[nextX][nextY] !=  prevValue + 1 ) {

                        travelledRoutes.pop();
                        std::get<1>(travelledRoutes.top())++;
                        continue;
                    }

                    if (topographicMap[std::get<0>(travelledRoutes.top()).first][std::get<0>(travelledRoutes.top()).second] == 9) {
                        sumOfTrailHeadRouteCounts++;
                        travelledRoutes.pop();
                        std::get<1>(travelledRoutes.top())++;

                        continue;
                    }
                }
            }
        }
    }

    std::cout << "Sum of Trail Head Route Counts: " << sumOfTrailHeadRouteCounts << std::endl;

    return 0;
}
