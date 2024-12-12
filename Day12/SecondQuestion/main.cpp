#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <map>
#include <set>

void exploreRegion(const std::vector<std::vector<char>>& grid, int i, int j,
                   std::map<std::pair<int, int>, bool>& visited,
                   std::unordered_map<int, std::vector<std::pair<int, int>>>& regions,
                   int regionIndex)
{
    //std::cout << i << " " << j << std::endl;
    visited[std::make_pair(i, j)] = true;
    regions[regionIndex].push_back(std::make_pair(i, j));

    if (i - 1 >= 0 && grid[i - 1][j] == grid[i][j] && visited.find(std::make_pair(i - 1, j)) == visited.end())
    {
        exploreRegion(grid, i - 1, j, visited, regions, regionIndex);
    }
    if (i + 1 < grid.size() && grid[i + 1][j] == grid[i][j] && visited.find(std::make_pair(i + 1, j)) == visited.end())
    {
        exploreRegion(grid, i + 1, j, visited, regions, regionIndex);
    }
    if (j - 1 >= 0 && grid[i][j - 1] == grid[i][j] && visited.find(std::make_pair(i, j - 1)) == visited.end())
    {
        exploreRegion(grid, i, j - 1, visited, regions, regionIndex);
    }
    if (j + 1 < grid[i].size() && grid[i][j + 1] == grid[i][j] && visited.find(std::make_pair(i, j + 1)) == visited.end())
    {
        exploreRegion(grid, i, j + 1, visited, regions, regionIndex);
    }
}

int countCorners(const std::vector<std::pair<int, int>>& region) {
    int corners = 0;
    // Store cells in a set for fast lookup
    std::set<std::pair<int, int>> regionSet(region.begin(), region.end());

    for (const auto& [x, y] : region) {
        // check the left and up cells are not in the regionSet
        if (regionSet.find(std::make_pair(x - 1, y)) == regionSet.end() &&
            regionSet.find(std::make_pair(x, y - 1)) == regionSet.end()) {
            corners++;
        }
        // check the right and up cells are not in the regionSet
        if (regionSet.find(std::make_pair(x + 1, y)) == regionSet.end() &&
            regionSet.find(std::make_pair(x, y - 1)) == regionSet.end()) {
            corners++;
        }
        // check the left and down cells are not in the regionSet
        if (regionSet.find(std::make_pair(x - 1, y)) == regionSet.end() &&
            regionSet.find(std::make_pair(x, y + 1)) == regionSet.end()) {
            corners++;
        }
        // check the right and down cells are not in the regionSet
        if (regionSet.find(std::make_pair(x + 1, y)) == regionSet.end() &&
            regionSet.find(std::make_pair(x, y + 1)) == regionSet.end()) {
            corners++;
        }

        // for convey cases: check the left and up cells are in the regionSet and left-up cell is not in the regionSet
        if (regionSet.find(std::make_pair(x - 1, y)) != regionSet.end() &&
            regionSet.find(std::make_pair(x, y - 1)) != regionSet.end() &&
            regionSet.find(std::make_pair(x - 1, y - 1)) == regionSet.end()) {
            corners++;
        }
        // for convey cases: check the right and up cells are in the regionSet and right-up cell is not in the regionSet
        if (regionSet.find(std::make_pair(x + 1, y)) != regionSet.end() &&
            regionSet.find(std::make_pair(x, y - 1)) != regionSet.end() &&
            regionSet.find(std::make_pair(x + 1, y - 1)) == regionSet.end()) {
            corners++;
        }
        // for convey cases: check the left and down cells are in the regionSet and left-down cell is not in the regionSet
        if (regionSet.find(std::make_pair(x - 1, y)) != regionSet.end() &&
            regionSet.find(std::make_pair(x, y + 1)) != regionSet.end() &&
            regionSet.find(std::make_pair(x - 1, y + 1)) == regionSet.end()) {
            corners++;
        }
        // for convey cases: check the right and down cells are in the regionSet and right-down cell is not in the regionSet
        if (regionSet.find(std::make_pair(x + 1, y)) != regionSet.end() &&
            regionSet.find(std::make_pair(x, y + 1)) != regionSet.end() &&
            regionSet.find(std::make_pair(x + 1, y + 1)) == regionSet.end()) {
            corners++;
        }
    }

    return corners;

}


void findRegions(const std::vector<std::vector<char>>& grid)
{
    std::map<std::pair<int, int>, bool> visited;
    std::unordered_map<int, std::vector<std::pair<int, int>>> regions;

    auto regionIndex = 0;
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (visited.find(std::make_pair(i, j)) == visited.end())
            {
                visited[std::make_pair(i, j)] = true;
                exploreRegion(grid, i, j, visited, regions, regionIndex++);
            }
        }
    }


    int sum = 0;
    for (const auto& [key, value] : regions)
    {
        std::cout << countCorners(value) << " " << value.size() << std::endl;
        sum += countCorners(value) * value.size();
    }
    std::cout << sum << std::endl;

}

int main() {
    std::cout << "Day 12, SecondQuestion" << std::endl;

    std::vector<std::vector<char>> grid;

    std::ifstream file("../input.txt");
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line)) {
            std::vector<char> row;
            for (char c : line)
            {
                row.push_back(c);
            }
            grid.push_back(row);
        }
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
    }

    findRegions(grid);

    return 0;
}
