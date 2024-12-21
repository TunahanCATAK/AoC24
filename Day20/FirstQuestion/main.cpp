#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <unordered_map>


using Point = std::pair<int, int>;

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::stack<std::pair<Point, int>>& stack) {
    std::stack<std::pair<Point, int>> tempStack = stack;
    while (!tempStack.empty()) {
        auto current = tempStack.top();
        tempStack.pop();
        os << current.first << " ";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::unordered_map<int, int>& map) {
    for (const auto& [key, value] : map) {
        os << "Key: " << key << " Value: " << value << std::endl;
    }
    return os;
}

struct hash_pair {
    std::size_t operator()(const std::pair<int, int>& p) const {
        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
    }
};


int solveMaze(std::vector<std::vector<char>>& maze, Point startPoint, Point endPoint) {

    // solve the maze start from the StartPoint and find the end point with 'E' character
    std::array<Point, 4> directions = {Point{0, 1}, Point{0, -1}, Point{1, 0}, Point{-1, 0}}; // Right, Left, Down, Up

    std::stack<std::pair<Point, int>> stack;
    std::set<Point> visited;
    stack.push(std::make_pair(startPoint, 0));
    visited.insert(startPoint);

    while (!stack.empty()) {
        auto current = stack.top();
        stack.pop();

        auto [currentPoint, currentDirectionIndex] = current;
//        std::cout << "Current Point: " << currentPoint << std::endl;
//        std::cout << "Current Direction Index: " << currentDirectionIndex << std::endl;

        if (currentPoint.first == endPoint.first && currentPoint.second == endPoint.second) {
//            std::cout << "End point found at (" << currentPoint.first << ", " << currentPoint.second << ")" << std::endl;
            break;
        }

        for (int i = currentDirectionIndex; i < 4; ++i) {
            Point direction = directions[i];
            Point nextPoint = std::make_pair(currentPoint.first + direction.first, currentPoint.second + direction.second);

            if (nextPoint.first >= 0 && nextPoint.first < maze.size() &&
                nextPoint.second >= 0 && nextPoint.second < maze[0].size() &&
                maze[nextPoint.first][nextPoint.second] != '#' &&
                visited.find(nextPoint) == visited.end()) {

                visited.insert(nextPoint);
                stack.push(std::make_pair(currentPoint, i + 1));
                stack.push(std::make_pair(nextPoint, 0));
                break;
            }
        }
    }

    int distance = 1;
    while (!stack.empty()){
        stack.pop();
        distance++;
    }

    return distance;

}


int main() {
    std::cout << "Day 20, FirstQuestion" << std::endl;

    std::vector<std::vector<char>> maze;
    Point startPoint;

    std::ifstream file("../input.txt");
    if (file.is_open()) {
        std::string line;
        int rowIndex = 0;
        while (std::getline(file, line)) {
            std::vector<char> row;
            int columnIndex = 0;
            for (char c : line)
            {
                if (c == 'S'){
                    startPoint = std::make_pair(rowIndex, columnIndex);
                }
                row.push_back(c);
                columnIndex++;
            }
            rowIndex++;
            maze.push_back(row);
        }
    }
    else {
        std::cerr <<  "Unable to open file" << std::endl;
    }

    // solve the maze start from the StartPoint and find the end point with 'E' character
    std::array<Point, 4> directions = {Point{0, 1}, Point{0, -1}, Point{1, 0}, Point{-1, 0}}; // Right, Left, Down, Up

    std::stack<std::pair<Point, int>> stack;
    std::set<Point> visited;
    stack.push(std::make_pair(startPoint, 0));
    visited.insert(startPoint);

    while (!stack.empty()) {
        auto current = stack.top();
        stack.pop();

        auto [currentPoint, currentDirectionIndex] = current;
//        std::cout << "Current Point: " << currentPoint << std::endl;
//        std::cout << "Current Direction Index: " << currentDirectionIndex << std::endl;

        if (maze[currentPoint.first][currentPoint.second] == 'E') {
            stack.push(current);
//            std::cout << "End point found at (" << currentPoint.first << ", " << currentPoint.second << ")" << std::endl;
            break;
        }

        for (int i = currentDirectionIndex; i < 4; ++i) {
            Point direction = directions[i];
            Point nextPoint = std::make_pair(currentPoint.first + direction.first, currentPoint.second + direction.second);

            if (nextPoint.first >= 0 && nextPoint.first < maze.size() &&
                nextPoint.second >= 0 && nextPoint.second < maze[0].size() &&
                maze[nextPoint.first][nextPoint.second] != '#' &&
                visited.find(nextPoint) == visited.end()) {

                visited.insert(nextPoint);
                stack.push(std::make_pair(currentPoint, i + 1));
                stack.push(std::make_pair(nextPoint, 0));
                break;
            }
        }
    }

    if (!stack.empty())
    {
        std::cout << "Found the end point" << std::endl;
        // print the path
        std::cout << stack << std::endl;
    }
    else
    {
        std::cout << "Could not find the end point" << std::endl;
    }

    std::unordered_map<Point, int, hash_pair> distances;
    int distance = 0;
    while (!stack.empty()) {
        auto current = stack.top();
        stack.pop();

        distances.insert(std::make_pair(current.first, distance++));

    }
    int maxDistance = distance;

//    for (const auto& [point, distance] : distances) {
//        std::cout << "Point: " << point << " Distance: " << distance << std::endl;
//    }


    std::array<std::pair<Point, Point>, 4> wallThroughDirections = {
        std::make_pair(Point{0,1}, Point{0,2}),
        std::make_pair(Point{0,-1},Point{0,-2}),
        std::make_pair(Point{1,0},Point{2,0}),
        std::make_pair(Point{-1,0},Point{-2,0})
    }; // Right, Left, Down, Up

    int counter = 0;
    std::unordered_map<int, int> gains;
    std::set<std::pair<Point, Point>> cheated;
    for (const auto& [point, distance] : distances) {

        for (int i = 0; i < 4; ++i) {
            auto [direction1, direction2] = wallThroughDirections[i];
            Point wallPoint1 = std::make_pair(point.first + direction1.first, point.second + direction1.second);
            Point wallPoint2 = std::make_pair(point.first + direction2.first, point.second + direction2.second);

            if (wallPoint1.first >= 0 && wallPoint1.first < maze.size() &&
                wallPoint1.second >= 0 && wallPoint1.second < maze[0].size() &&
                wallPoint2.first >= 0 && wallPoint2.first < maze.size() &&
                wallPoint2.second >= 0 && wallPoint2.second < maze[0].size() &&
                maze[wallPoint1.first][wallPoint1.second] == '#' &&
                maze[wallPoint2.first][wallPoint2.second] == '.') {

                    if (distances.find(wallPoint2) != distances.end())
                    {
                        auto cheatedDistance = distances[wallPoint2]; // distance from the end point
                        auto currentDistance = distances[point]; // distance from the start point
                        if (cheated.find(std::make_pair(point, wallPoint1)) != cheated.end() ||
                            cheated.find(std::make_pair(wallPoint1, point)) != cheated.end())
                        {
                            std::cout << "Already cheated" << std::endl;
                            continue;
                        }
                        cheated.insert(std::make_pair(wallPoint1, point));
                        auto gain = std::abs(cheatedDistance - currentDistance) - 2;
                        gains[gain]++;
                        if (gain >= 100)
                        {
                            counter++;
                            std::cout << "Wall Point 1: " << wallPoint1 << " Wall Point 2: " << wallPoint2 << " Gain: " << gain << std::endl;
                        }
                    }
                    else {
                        std::cout << "Could not find the wall point 2" << std::endl;
                        // calculate the distance from the start point to the wall point 2
                        // if the distance is greater than 100, increment the counter
                        auto cheatedDistance = solveMaze(maze, wallPoint2, startPoint);
                        auto currentDistance = distances[point]; // distance from the start point

                        auto gain =  cheatedDistance - currentDistance - 2;
                        gains[gain]++;
                        if (gain >= 100)
                        {
                            counter++;
                            std::cout << "Wall Point 1: " << wallPoint1 << " Wall Point 2: " << wallPoint2 << " Gain: " << gain << std::endl;
                        }
                    }
            }
        }

    }

    int halfCounter = 0;
    std::cout << "Gains: " << gains << std::endl;
    for (const auto& [gain, count] : gains) {

        if (gain >= 100)
        {
            std::cerr << "Gain: " << gain << " Count: " << count << std::endl;
            if (count % 2 == 0)
                halfCounter += count/2;
            else
                halfCounter += (count - 1)/2 + 1;
            //halfCounter += count/2;
        }

    }

    std::cout << "Counter: " << counter << std::endl;
    std::cout << "Half Counter: " << halfCounter << std::endl;

    return 0;
}
