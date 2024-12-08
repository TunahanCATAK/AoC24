#include <iostream>
#include <fstream>
#include <unordered_map>
#include <set>
#include <ranges>
#include <vector>

using Point=std::pair<int,int>;

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.first << "," << p.second << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::unordered_map<char, std::vector<Point>>& maze) {
    for (const auto& [key, value] : maze) {
        os << key << ": ";
        for (const auto& p : value) {
            os << p << " ";
        }
        os << std::endl;
    }
    return os;
}

std::pair<int, int> calculateVector(const Point& node1, const Point& node2) {
    int xComponent = node2.first - node1.first; // x2 - x1
    int yComponent = node2.second - node1.second; // y2 - y1

    // Return as a pair (xComponent, yComponent)
    return {xComponent, yComponent};
}

std::pair<int, int> negateVector(const std::pair<int, int>& vector) {
    return {-vector.first, -vector.second};
}

const Point& operator+(const Point& point, const std::pair<int, int>& vector) {
    Point newPoint = point;

    newPoint.first += vector.first;
    newPoint.second += vector.second;
    return newPoint;
}

bool isPointInTheMaze(const Point& point, int maxRow, int maxCol) {
    return point.first >= 0 && point.first < maxRow && point.second >= 0 && point.second < maxCol;
}

struct view_as_pairs {
    std::vector<Point>& values;

    struct tracker{
        size_t size;

        std::pair<int, int> indexes(int ind)
        {
            //std::cout << "ind: " << ind << std::endl;
            //std::cout << size << std::endl;
            int ind1 = 0;
            int ind2 = 1;
            for ( int i = 0; i < ind; i++)
            {
                if (ind2 + 1 < size){
                    ind2 += 1;
                }
                else if (ind1 + 1 < size){
                    ind1 += 1;
                    ind2 = ind1 + 1;
                }
                else {
                    throw std::out_of_range("Out of range");
                }
            }
            //std::cout << "ind1: " << ind1 << " ind2: " << ind2 << std::endl;
            return { ind1, ind2};
        }
    };

    struct proxy {
        std::vector<Point>::iterator it;
        std::vector<Point>::iterator it2;

        Point& first() { return *it;}
        Point& second() { return *it2; }
    };
    proxy operator[](size_t index){
        //std::cout << "operator [] index: " << index << std::endl;
        auto ind = tracker_state.indexes(index);
        return proxy{values.begin() + ind.first, values.begin() + ind.second};
    }
    size_t size() {
        // calculate size permutation 2 of values.size()
        return values.size() * (values.size() - 1) / 2;
    }

    view_as_pairs(std::vector<Point>& values) : values(values), tracker_state{values.size()} {}

private:
    tracker tracker_state;
};


int main() {
    std::cout << "Day 08, SecondQuestion" << std::endl;

    std::unordered_map<char, std::vector<Point>> maze;
    std::set<Point> visited;
    std::ifstream file("../input.txt");
    if (!file.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        return 1;
    }

    size_t mazeMaxRow = 0;
    size_t mazeMaxCol = 0;
    std::string line;
    int row = 0;
    while (std::getline(file, line)) {
        mazeMaxCol = line.size();
        for (int col = 0; col < line.size(); ++col) {
            char ch = line[col];
            if (ch != '.') {
                maze[ch].emplace_back(row, col);
            }
        }
        ++row;
    }
    mazeMaxRow = row;

    std::cout << mazeMaxRow << " " << mazeMaxCol << std::endl;
    std::cout << maze << std::endl;

    std::unordered_map<char, std::vector<Point>> newMazeNodes = maze;

    for (auto& [key, value] : maze) {
        view_as_pairs pointPairs{value};

        // print pointPairs
        for (size_t i=0; i < pointPairs.size(); ++i){
            auto pointPair = pointPairs[i]; // has to be used this way because of the view object missing some implementation..

            //std::cout << pointPair.first() << " " << pointPair.second() << "\n";
            auto diffVector = calculateVector(pointPair.first(), pointPair.second());
            auto newPoint = pointPair.second() + diffVector;
            // continue adding the vector to new point till hit the wall or out of the maze
            while (isPointInTheMaze(newPoint, mazeMaxRow, mazeMaxCol)) {
                visited.insert(pointPair.second());
                visited.insert(pointPair.first());

                visited.insert(newPoint);
                newPoint = newPoint + diffVector;
            }

            newPoint = pointPair.first() + negateVector(diffVector);
            while (isPointInTheMaze(newPoint, mazeMaxRow, mazeMaxCol)) {
                visited.insert(pointPair.first());
                visited.insert(pointPair.second());

                visited.insert(newPoint);
                newPoint = newPoint + negateVector(diffVector);
            }

        }
    }


    std::cout << "Visited: " << visited.size() << std::endl;

    // print the maze with # with the visited nodes and the nodes in the maze
    for (int row = 0; row < mazeMaxRow; ++row) {
        for (int col = 0; col < mazeMaxCol; ++col) {
            Point p{row, col};
            if (visited.find(p) != visited.end()) {
                std::cout << "#";
            }
            else {
                bool found = false;
                for (const auto& [key, value] : maze) {
                    if (std::find(value.begin(), value.end(), p) != value.end()) {
                        std::cout << key;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    std::cout << ".";
                }
            }
        }
        std::cout << std::endl;
    }

    return 0;
}
