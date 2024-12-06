#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

enum class direction{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

std::tuple<int, int, direction> getStartPosition(std::vector<std::vector<char>> &maze)
{
    int maxX = maze.size();
    int maxY = maze[0].size();
    direction dir;
    int startX = 0, startY = 0;

    for (int i = 0; i < maxX; i++)
    {
        for (int j = 0; j < maxY; j++)
        {
            if (maze[i][j] == '<' || maze[i][j] == '>' || maze[i][j] == '^' || maze[i][j] == 'v')
            {
                if (maze[i][j] == '<')
                {
                    dir = direction::LEFT;
                }
                else if (maze[i][j] == '>')
                {
                    dir = direction::RIGHT;
                }
                else if (maze[i][j] == '^')
                {
                    dir = direction::UP;
                }
                else if (maze[i][j] == 'v')
                {
                    dir = direction::DOWN;
                }

                startX = i;
                startY = j;
                break;
            }
        }
    }

    return std::make_tuple(startX, startY, dir);
}

int main() {
    std::cout << "Day 06, SecondQuestion" << std::endl;

    std::vector<std::vector<char>> maze;

    std::ifstream file("../input.txt");
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            maze.push_back(std::vector<char>(line.begin(), line.end()));
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file" << std::endl;
    }

    int maxX = maze.size() - 1;
    int maxY = maze[0].size() - 1;

    // find the starting point
    auto [startX, startY, dir] = getStartPosition(maze);

    int obstacleCount = 0;

    auto cycleCheck = [&](int x, int y, int obsX, int obsY, direction startDir){

        int turn = 0;
        while (x <= maxX && y <= maxY && x >= 0 && y >= 0)
        {
            turn++;
            if (turn > 100'000)
            {
                std::cout << "ObsX: " << obsX << " ObsY: " << obsY << std::endl;
                return true;
            }
            if (startDir == direction::UP)
            {
                if (x > 0 && maze[x - 1][y] == '#')
                {
                    startDir = direction::RIGHT;
                    continue;
                }
                else {
                    x--;
                    continue;
                }
            }
            if (startDir == direction::RIGHT)
            {
                if (y < maxY && maze[x][y+1] == '#')
                {
                    startDir = direction::DOWN;
                    continue;
                }
                else {
                    y++;
                    continue;
                }
            }
            if (startDir == direction::DOWN)
            {
                if (x < maxX && maze[x+1][y] == '#')
                {
                    startDir = direction::LEFT;
                    continue;
                }
                else {
                    x++;
                    continue;
                }
            }
            if (startDir == direction::LEFT)
            {
                if (y > 0 && maze[x][y-1] == '#')
                {
                    startDir = direction::UP;
                    continue;
                }
                else {
                    y--;
                    continue;
                }
            }

        }
        return false;

    };

    // find the position of '#' chars in the maze and print them:

    for (int x = 0; x < maze.size(); x++)
    {
        for (int y = 0; y < maze[x].size(); y++)
        {
            if (maze[x][y] == '.' && !(x == startX && y == startY))
            {
                maze[x][y] = '#';

                // do check
                if (cycleCheck(startX, startY, x, y, dir)){
                    obstacleCount++;
                }

                maze[x][y] = '.';
            }
        }
    }

    std::cout << "Obstacle count: " << obstacleCount << std::endl;

    return 0;
}
