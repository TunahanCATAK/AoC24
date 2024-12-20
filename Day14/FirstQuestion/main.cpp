#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <ranges>
#include <algorithm>

using Point=std::pair<int,int>;
constexpr auto MAZE_WIDTH = 101;
constexpr auto MAZE_HEIGHT = 103;

// TODO: possible to compose with Maze interface and update the Maze grids??
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
            std::cout << grid[i][j] << ' ';
        }
        std::cout << '\n';
    }
}


void countRobotsInQuadrants(const std::vector<robot>& robots) {
    int firstQuadrant = 0, secondQuadrant = 0, thirdQuadrant = 0, fourthQuadrant = 0;

    for (const auto& rob : robots) {
        if (rob.currentPos.first < MAZE_WIDTH / 2 && rob.currentPos.second < MAZE_HEIGHT / 2) {
            ++firstQuadrant;
        } else if (rob.currentPos.first >= MAZE_WIDTH / 2 + 1 && rob.currentPos.second < MAZE_HEIGHT / 2) {
            ++secondQuadrant;
        } else if (rob.currentPos.first < MAZE_WIDTH / 2 && rob.currentPos.second >= MAZE_HEIGHT / 2 + 1) {
            ++thirdQuadrant;
        } else if (rob.currentPos.first >= MAZE_WIDTH / 2 + 1 && rob.currentPos.second >= MAZE_HEIGHT / 2 + 1) {
            ++fourthQuadrant;
        }
    }

    std::cout << "Safety: " << firstQuadrant * secondQuadrant * thirdQuadrant * fourthQuadrant << std::endl;
}

int main() {
    std::cout << "Day 14, FirstQuestion" << std::endl;

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

    const auto& x = robots | std::views::transform([](robot& r){
        for (int i = 0; i < 100; ++i)
        {
            r.move();
        }
        return r;
    });
    for (const auto& rob : x){
        std::cout << "Robot is at: (" << rob.currentPos.first << " - " << rob.currentPos.second << ")\n";
    }
    std::copy(x.begin(), x.end(), robots.begin());


    printGrid(robots);
    countRobotsInQuadrants(robots);

    return 0;
}
