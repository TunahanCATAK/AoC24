#include <iostream>
#include <fstream>
#include <vector>

int main() {
    std::cout << "Day 04, FirstQuestion" << std::endl;

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

    int totalXmas = 0;
    for (int x = 0; x < maze.size(); x++)
    {
        for (int y = 0; y < maze[x].size(); y++)
        {
            if (maze[x][y] == 'X')
            {
                // right
                if (y + 3 < maze[x].size())
                {
                    if (maze[x][y + 1] == 'M' && maze[x][y + 2] == 'A' && maze[x][y + 3] == 'S')
                    {
                        totalXmas++;
                    }
                }
                // left
                if (y - 3 >= 0)
                {
                    if (maze[x][y - 1] == 'M' && maze[x][y - 2] == 'A' && maze[x][y - 3] == 'S')
                    {
                        totalXmas++;
                    }
                }
                // top
                if (x - 3 >= 0)
                {
                    if (maze[x - 1][y] == 'M' && maze[x - 2][y] == 'A' && maze[x - 3][y] == 'S')
                    {
                        totalXmas++;
                    }
                }
                // bottom
                if (x + 3 < maze.size())
                {
                    if (maze[x + 1][y] == 'M' && maze[x + 2][y] == 'A' && maze[x + 3][y] == 'S')
                    {
                        totalXmas++;
                    }
                }
                // 4x diagonal directions
                // top right
                if (x - 3 >= 0 && y + 3 < maze[x].size())
                {
                    if (maze[x - 1][y + 1] == 'M' && maze[x - 2][y + 2] == 'A' && maze[x - 3][y + 3] == 'S')
                    {
                        totalXmas++;
                    }
                }
                // top left
                if (x - 3 >= 0 && y - 3 >= 0)
                {
                    if (maze[x - 1][y - 1] == 'M' && maze[x - 2][y - 2] == 'A' && maze[x - 3][y - 3] == 'S')
                    {
                        totalXmas++;
                    }
                }
                // bottom right
                if (x + 3 < maze.size() && y + 3 < maze[x].size())
                {
                    if (maze[x + 1][y + 1] == 'M' && maze[x + 2][y + 2] == 'A' && maze[x + 3][y + 3] == 'S')
                    {
                        totalXmas++;
                    }
                }
                // bottom left
                if (x + 3 < maze.size() && y - 3 >= 0)
                {
                    if (maze[x + 1][y - 1] == 'M' && maze[x + 2][y - 2] == 'A' && maze[x + 3][y - 3] == 'S')
                    {
                        totalXmas++;
                    }
                }
            }
        }
        std::cout << std::endl;
    }

    std::cout << "Total Xmas: " << totalXmas << std::endl;

    return 0;
}
