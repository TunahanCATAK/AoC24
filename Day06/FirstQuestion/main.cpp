#include <iostream>
#include <fstream>
#include <vector>
#include <set>

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
    std::cout << "Day 06, FirstQuestion" << std::endl;

    std::vector<std::vector<char>> maze;
    std::set<std::pair<int, int>> visited;

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

    int x = 0, y = 0;
    int maxX = maze.size() - 1;
    int maxY = maze[0].size() - 1;

    // find the starting point
    auto [startX, startY, dir] = getStartPosition(maze);


    while (startX < maxX && startY < maxY && startX >= 0 && startY >= 0)
    {

        std::cout << "StartX: " << startX << " StartY: " << startY << std::endl;
        if (dir == direction::UP)
        {
            if (startX > 0 && maze[startX - 1][startY] == '#')
            {
                dir = direction::RIGHT;
                continue;
            }
            else {
                std::cerr << "Visited: " << startX << " " << startY << std::endl;
                visited.insert(std::make_pair(startX, startY));
                startX--;
                continue;
            }
        }
        if (dir == direction::RIGHT)
        {
            if (startY < maxY && maze[startX][startY+1] == '#')
            {
                dir = direction::DOWN;
                continue;
            }
            else {
                std::cerr << "Visited: " << startX << " " << startY << std::endl;
                visited.insert(std::make_pair(startX, startY));
                startY++;
                continue;
            }
        }
        if (dir == direction::DOWN)
        {
            if (startX < maxX && maze[startX+1][startY] == '#')
            {
                dir = direction::LEFT;
                continue;
            }
            else {
                std::cerr << "Visited: " << startX << " " << startY << std::endl;
                visited.insert(std::make_pair(startX, startY));
                startX++;
                continue;
            }
        }
        if (dir == direction::LEFT)
        {
            if (startY > 0 && maze[startX][startY-1] == '#')
            {
                dir = direction::UP;
                continue;
            }
            else {
                std::cerr << "Visited: " << startX << " " << startY << std::endl;
                visited.insert(std::make_pair(startX, startY));
                startY--;
                continue;
            }
        }

    }

    std::cout << "Visited: " << visited.size() << std::endl;

    return 0;
}
