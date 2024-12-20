#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <ranges>

using Point=std::pair<int,int>;
constexpr auto MAZE_WIDTH = 101;
constexpr auto MAZE_HEIGHT = 103;

// TODO: possible to implement Maze interface and update the Maze grids??
struct robot{
    Point currentPos;
    int velocityX;
    int velocityY;

    void move(){
        currentPos.first = (currentPos.first + velocityX) % MAZE_WIDTH;
        if (currentPos.first < 0) currentPos.first += MAZE_WIDTH;

        currentPos.second = (currentPos.second + velocityY) % MAZE_HEIGHT;
        if (currentPos.second < 0) currentPos.second += MAZE_HEIGHT;
    }

    robot() = default;
    robot(std::pair<int, int> p, int velX, int velY) : currentPos{p}, velocityX(velX), velocityY(velY) {}
    robot(const robot&) = default;
    robot(robot&&) = default;
    robot& operator=(const robot&) = default;
    robot& operator=(robot&&) = default;
};

std::ostream& operator<<(std::ostream& os, const std::vector<robot>& robots){
    for (const auto& robot : robots){
        os << "Robot is at: (" << robot.currentPos.first << " - " << robot.currentPos.second << ")\n";
    }
    return os;
}

void printGrid(const std::vector<robot>& robots) {
    char grid[MAZE_HEIGHT][MAZE_WIDTH] = {};

    // Initialize the grid with dots
    for (int i = 0; i < MAZE_HEIGHT; ++i) {
        for (int j = 0; j < MAZE_WIDTH; ++j) {
            grid[i][j] = '.';
        }
    }

    // Mark the robots' positions on the grid
    for (const auto& rob : robots) {
        grid[rob.currentPos.second][rob.currentPos.first] = 'R';
    }

    // Print the grid
    for (int i = 0; i < MAZE_HEIGHT; ++i) {
        for (int j = 0; j < MAZE_WIDTH; ++j) {
            std::cout << grid[i][j] ;
        }
        std::cout << '\n';
    }
}

int findK(const std::vector<robot>& robots, Point position){
    if (std::find_if(robots.begin(), robots.end(),
                     [&position](const auto& r){
                        return r.currentPos == std::make_pair(position.first + 1, position.second);
                    }) == robots.end()){
        return position.first;
    }

    return findK(robots, std::make_pair(position.first + 1,position.second));
}

int findN(const std::vector<robot>& robots, Point position){
    if (std::find_if(robots.begin(), robots.end(),
                     [&position](const auto& r){
                         return r.currentPos == std::make_pair(position.first, position.second + 1);
                     }) == robots.end()){
        return position.second;
    }

    return findN(robots, std::make_pair(position.first,position.second + 1));
}

bool checkFrame(const std::vector<robot>& robots)
{
    for (const auto& robot : robots)
    {
        Point position = robot.currentPos;
        // find the k: to the right
        auto kPosition = findK(robots, position);
        //std::cout << "k: " << kPosition << " - " << position.first << std::endl;
        if (kPosition <= position.first + 20){
            continue;
        }
        // find the n: to the bottom
        auto nPosition = findN(robots, position);
        //std::cout << "n: " << nPosition << " - " << position.second << std::endl;
        if (nPosition <= position.second + 20){
            continue;
        }
        // check other sides of the frame with n and k
        return true;
    }
    return false;
}

int main() {
    std::cout << "Day 14, SecondQuestion" << std::endl;

    std::vector<robot> robots;

    std::ifstream file("../input.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            // Variables to store the extracted values
            int x, y, velX, velY;
            std::regex robotParamRegex(R"(p=(-?\d+),(-?\d+) v=(-?\d+),(-?\d+))");
            std::smatch match;
            if (std::regex_match(line, match, robotParamRegex)) {
                x = std::stoi(match[1]);
                y = std::stoi(match[2]);
                velX = std::stoi(match[3]);
                velY = std::stoi(match[4]);

                robots.emplace_back(robot{std::make_pair(x, y), velX, velY});
            }
        }
    }
    else {
        std::cerr <<  "Unable to open file" << std::endl;
    }

    // check there is a frame for the photo:
    bool isXmasTreeFound = false;
    long seconds = 0;
    while (!isXmasTreeFound){
        for(auto& robot : robots) {
            robot.move();
        }
        seconds++;
        std::cout << seconds << std::endl;
        isXmasTreeFound = checkFrame(robots);
        if (isXmasTreeFound){
            std::cout << "Time elapsed for xmas tree: " << seconds << std::endl;
            printGrid(robots);
        }
    }

    return 0;
}
