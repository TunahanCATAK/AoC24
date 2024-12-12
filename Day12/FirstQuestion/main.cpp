#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <map>

struct hash_pair {
    std::size_t operator()(const std::pair<int, int>& p) const {
        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
    }
};

struct hash_tuple {
    std::size_t operator()(const std::tuple<int, int, int>& p) const {
        return std::hash<int>()(std::get<0>(p)) ^ (std::hash<int>()(std::get<1>(p)) << 1);
    }
};

bool considerTop(const std::vector<std::vector<char>>& grid, int i, int j,
                 std::unordered_map<int, int>& walls,
                 const std::unordered_map<char, std::vector<std::pair<int, int>>>& visited)
{
    if (i - 1 >= 0)
    {
        if (std::find(visited.at(grid[i][j]).begin(), visited.at(grid[i][j]).end(),
                      std::make_pair(i - 1, j)) == visited.at(grid[i][j]).end())
        {
            return false;
        }

        if (grid[i - 1][j] == grid[i][j])
        {
            return true;
        }
    }
    return false;
}

bool considerBottom(const std::vector<std::vector<char>>& grid, int i, int j,
                    std::unordered_map<int, int>& walls,
                    const std::unordered_map<char, std::vector<std::pair<int, int>>>& visited)
{
    if (i + 1 < grid.size())
    {
        if (std::find(visited.at(grid[i][j]).begin(), visited.at(grid[i][j]).end(),
                      std::make_pair(i + 1, j)) == visited.at(grid[i][j]).end())
        {
            return false;
        }

        if (grid[i + 1][j] == grid[i][j])
        {
            return true;
        }
    }

    return false;
}

bool considerLeft(const std::vector<std::vector<char>>& grid, int i, int j,
                  std::unordered_map<int, int>& walls,
                  const std::unordered_map<char, std::vector<std::pair<int, int>>>& visited)
{
    if (j - 1 >= 0)
    {
        if (std::find(visited.at(grid[i][j]).begin(), visited.at(grid[i][j]).end(),
                      std::make_pair(i, j - 1)) == visited.at(grid[i][j]).end())
        {
            return false;
        }

        if (grid[i][j - 1] == grid[i][j])
        {
            return true;
        }
    }

    return false;
}

bool considerRight(const std::vector<std::vector<char>>& grid, int i, int j,
                   std::unordered_map<int, int>& walls,
                   const std::unordered_map<char, std::vector<std::pair<int, int>>>& visited)
{
    if (j + 1 < grid[i].size())
    {
        if (std::find(visited.at(grid[i][j]).begin(), visited.at(grid[i][j]).end(),
                      std::make_pair(i, j + 1)) == visited.at(grid[i][j]).end())
        {
            return false;
        }

        if (grid[i][j + 1] == grid[i][j])
        {
            return true;
        }
    }

    return false;
}

std::ostream& operator<<(std::ostream& os, const std::vector<std::vector<std::pair<int, int>>>& ranges)
{
    for (const auto& range : ranges)
    {
        for (const auto& [i, j] : range)
        {
            os << "(" << i << ", " << j << ") ";
        }
        os << std::endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::unordered_map<int, int>& walls)
{
    for (const auto& [key, value] : walls)
    {
        os << key << " : " << value << std::endl;
    }
    return os;
}


void createRange(const std::vector<std::vector<char>>& grid, int i, int j)
{
    static std::vector<std::vector<std::pair<int, int>>> ranges;
    static std::unordered_map<int, int> walls;
    static std::unordered_map<char, std::vector<std::pair<int, int>>> visited;


    visited[grid[i][j]].push_back(std::make_pair(i, j));


    auto isConnectedTop = considerTop(grid, i, j, walls, visited);
    if (isConnectedTop) walls[ranges.size() - 1] -= 2;
    auto isConnectedBottom = considerBottom(grid, i, j, walls, visited);
    if (isConnectedBottom) walls[ranges.size() - 1] -= 2;
    auto isConnectedLeft = considerLeft(grid, i, j, walls, visited);
    if (isConnectedLeft) walls[ranges.size() - 1] -= 2;
    auto isConnectedRight = considerRight(grid, i, j, walls, visited);
    if (isConnectedRight) walls[ranges.size() - 1] -= 2;

    if (isConnectedRight || isConnectedLeft || isConnectedTop || isConnectedBottom)
    {
        ranges[ranges.size() - 1].push_back(std::make_pair(i, j));
        walls[ranges.size() - 1] += 4;
    }
    else {
        ranges.push_back(std::vector<std::pair<int, int>>{std::make_pair(i, j)});
        walls[ranges.size() - 1] = 4;
    }

    std::cout << ranges << std::endl;
    std::cout << walls << std::endl;
}

void exploreRegion(const std::vector<std::vector<char>>& grid, int i, int j,
                   std::map<std::pair<int, int>, bool>& visited,
                   std::unordered_map<int, int>& regions, int regionIndex,
                   std::unordered_map<std::pair<int,int>, int, hash_pair>& walls,
                   std::unordered_map<std::tuple<int, int, int>, int, hash_tuple>& walls1)
{
    //std::cout << i << " " << j << std::endl;
    visited[std::make_pair(i, j)] = true;
    regions[regionIndex] += 1;

    if (i - 1 >= 0 && grid[i - 1][j] == grid[i][j] && visited.find(std::make_pair(i - 1, j)) == visited.end())
    {
        exploreRegion(grid, i - 1, j, visited, regions, regionIndex, walls, walls1);
    }
    if (i - 1 >= 0 && grid[i - 1][j] != grid[i][j])
    {
        //std::cout << "Wall to " << i << " " << j << std::endl;
        walls[std::make_pair(i,j)] += 1;
        walls1[std::make_tuple(i,j, regionIndex)] += 1;
    }
    if (i - 1 < 0)
    {
        //std::cout << "Wall to " << i << " " << j << std::endl;
        walls[std::make_pair(i,j)] += 1;
        walls1[std::make_tuple(i,j, regionIndex)] += 1;
    }

    if (i + 1 < grid.size() && grid[i + 1][j] == grid[i][j] && visited.find(std::make_pair(i + 1, j)) == visited.end())
    {
        exploreRegion(grid, i + 1, j, visited, regions, regionIndex, walls, walls1);
    }
    if (i + 1 < grid.size() && grid[i + 1][j] != grid[i][j])
    {
        //std::cout << "Wall to " << i << " " << j << std::endl;
        walls[std::make_pair(i,j)] += 1;
        walls1[std::make_tuple(i,j, regionIndex)] += 1;
    }
    if (i + 1 >= grid.size())
    {
        //std::cout << "Wall to " << i << " " << j << std::endl;
        walls[std::make_pair(i,j)] += 1;
        walls1[std::make_tuple(i,j, regionIndex)] += 1;
    }

    if (j - 1 >= 0 && grid[i][j - 1] == grid[i][j] && visited.find(std::make_pair(i, j - 1)) == visited.end())
    {
        exploreRegion(grid, i, j - 1, visited, regions, regionIndex, walls, walls1);
    }
    if (j - 1 >= 0 && grid[i][j - 1] != grid[i][j])
    {
        //std::cout << "Wall to " << i << " " << j << std::endl;
        walls[std::make_pair(i,j)] += 1;
        walls1[std::make_tuple(i,j, regionIndex)] += 1;
    }
    if (j - 1 < 0)
    {
        //std::cout << "Wall to " << i << " " << j << std::endl;
        walls[std::make_pair(i,j)] += 1;
        walls1[std::make_tuple(i,j, regionIndex)] += 1;
    }

    if (j + 1 < grid[i].size() && grid[i][j + 1] == grid[i][j] && visited.find(std::make_pair(i, j + 1)) == visited.end())
    {
        exploreRegion(grid, i, j + 1, visited, regions, regionIndex, walls, walls1);
    }
    if (j + 1 < grid[i].size() && grid[i][j + 1] != grid[i][j])
    {
        //std::cout << "Wall to " << i << " " << j << std::endl;
        walls[std::make_pair(i,j)] += 1;
        walls1[std::make_tuple(i,j, regionIndex)] += 1;
    }
    if (j +1 >= grid[i].size())
    {
        //std::cout << "Wall to " << i << " " << j << std::endl;
        walls[std::make_pair(i,j)] += 1;
        walls1[std::make_tuple(i,j, regionIndex)] += 1;
    }
}

void findRegions(const std::vector<std::vector<char>>& grid)
{
    std::map<std::pair<int, int>, bool> visited;
    std::unordered_map<int, int> regions;
    std::unordered_map<std::pair<int, int>, int, hash_pair> walls;
    std::unordered_map<std::tuple<int, int, int>, int, hash_tuple> walls1;

    auto regionIndex = 0;
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (visited.find(std::make_pair(i, j)) == visited.end())
            {
                //std::cout << "Region " << regionIndex << std::endl;
                visited[std::make_pair(i, j)] = true;
                exploreRegion(grid, i, j, visited, regions, regionIndex++, walls, walls1);
            }
        }
    }


//    for (const auto& [key, value] : regions)
//    {
//        std::cout << key << " : " << value << std::endl;
//    }
//
//    for (const auto& [key, value] : walls)
//    {
//        std::cout << key.first << " " << key.second << " : " << value << std::endl;
//    }
//
//    for (const auto& [key, value] : walls1)
//    {
//        std::cout << std::get<0>(key) << " " << std::get<1>(key) << " " << std::get<2>(key) << " : " << value << std::endl;
//    }

    long sum = 0;
    for (const auto& [key, value] : regions)
    {
        int multiplier = value;

        int wall = 0;
        for (const auto& [key1, value1] : walls1)
        {
            if (std::get<2>(key1) == key)
            {
                wall += value1;
            }
        }
        sum += (multiplier * wall);
    }

    std::cout << sum << std::endl;

}

int main() {
    std::cout << "Day 12, FirstQuestion" << std::endl;

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
