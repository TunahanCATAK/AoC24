#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <unordered_map>

using Point = std::pair<int, int>;

struct hash_pair {
    std::size_t operator()(const Point& p) const {
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
                maze[nextPoint.first][nextPoint.second] != '.' &&
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

std::vector<Point> findShortestPath(const std::vector<std::vector<char>>& maze, Point startPoint, Point endPoint) {
    std::array<Point, 4> directions = {Point{0, 1}, Point{0, -1}, Point{1, 0}, Point{-1, 0}}; // Right, Left, Down, Up
    std::queue<std::pair<Point, std::vector<Point>>> queue; // Each entry contains a point and the path to reach it
    std::set<Point> visited; // Track visited points

    queue.push({startPoint, {startPoint}});
    visited.insert(startPoint);

    while (!queue.empty()) {
        auto [currentPoint, path] = queue.front();
        queue.pop();

        // Check if we've reached the endpoint
        if (currentPoint.first == endPoint.first &&  currentPoint.second == endPoint.second) {
            return path; // Return the shortest path
        }

        // Explore all directions
        for (const auto& direction : directions) {
            Point nextPoint = {currentPoint.first + direction.first, currentPoint.second + direction.second};

            // Check if the next point is valid
            if (nextPoint.first >= 0 && nextPoint.first < maze.size() &&
                nextPoint.second >= 0 && nextPoint.second < maze[0].size() &&
                maze[nextPoint.first][nextPoint.second] != '.' &&
                visited.find(nextPoint) == visited.end()) {

                visited.insert(nextPoint); // Mark as visited
                auto newPath = path; // Copy the current path
                newPath.push_back(nextPoint); // Add the next point to the path
                queue.push({nextPoint, newPath}); // Push the new point and path into the queue
            }
        }
    }

    return {}; // Return an empty path if no solution is found
}

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

int euclidianDistance(const Point& p1, const Point& p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

int main() {
    std::cout << "Day 20, SecondQuestion" << std::endl;

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

//    auto candidatePoint = Point{3,1};
//    auto point = Point{7,3};
//    int distanceToCandidate = solveMaze(maze, point, candidatePoint);
//    auto shortestPathToCandidate = findShortestPath(maze, point, candidatePoint);
//    int shortestDistanceToCandidate = shortestPathToCandidate.size() - 1;
//
//    std::cout << "Distance to Candidate: " << distanceToCandidate << std::endl;
//    std::cout << "Shortest Distance to Candidate: " << shortestPathToCandidate.size() - 1 << std::endl;
//    std::cout << "Candidate Distance: " << distances[candidatePoint] << std::endl;
//    std::cout << "Distance: " << distances[point] << std::endl;
//    std::cout << "Gain: " << distances[candidatePoint] - distances[point] - distanceToCandidate <<  std::endl;
//    std::cout << "Gain /w shortest path: " << distances[candidatePoint] - distances[point] - shortestDistanceToCandidate <<  std::endl;

    int maxDistance = distance;
    std::unordered_map<int, int> gains;
    std::unordered_map<Point, std::vector<Point>, hash_pair> visitedPoints;
    int counter = 0;
    for (const auto& [point, distance] : distances) {

        for (const auto& [candidatePoint, candidateDistance] : distances) {
            if (point != candidatePoint && distance < candidateDistance && euclidianDistance(point, candidatePoint) <= 20){
                //std::cout << "Point: " << point << " Candidate Point: " << candidatePoint << std::endl;
                if (std::find(visitedPoints[point].begin(), visitedPoints[point].end(), candidatePoint) != visitedPoints[point].end() ||
                    std::find(visitedPoints[candidatePoint].begin(), visitedPoints[candidatePoint].end(), point) != visitedPoints[candidatePoint].end())
                {
                    continue;
                }
                auto pathToCandidate = findShortestPath(maze, point, candidatePoint);
                int distanceToCandidate = pathToCandidate.size() - 1;
                if (distanceToCandidate <= 20)
                {
                    visitedPoints[point].push_back(candidatePoint);
                    int gain = candidateDistance - distance - distanceToCandidate;
                    gains[gain]++;
                }
            }
        }
    }

    std::cout << "Gains: " << gains << std::endl;

    for (const auto& [gain, count] : gains) {

        if (gain >= 50)
        {
            std::cerr << "Gain: " << gain << " Count: " << count << std::endl;
            if (count % 2 == 0)
                counter += count/2;
            else
                counter += (count - 1)/2 + 1;
        }

    }

    std::cout << "Counter: " << counter << std::endl;

    return 0;
}
