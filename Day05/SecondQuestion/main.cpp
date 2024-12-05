#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <tuple>
#include <ranges>
#include <algorithm>
#include <set>
#include <stack>

void updateChildIterative(std::map<int, std::tuple<int, std::vector<int>>>& order, int key)
{
    std::stack<int> stack;
    std::set<int> visited;
    stack.push(key);
    visited.insert(key);

    while (!stack.empty())
    {
        int currentKey = stack.top();
        stack.pop();

        for (int child : std::get<1>(order[currentKey]))
        {
            if (visited.find(child) == visited.end())
            {
                std::get<0>(order[child]) = std::get<0>(order[currentKey]) + 1;
                stack.push(child);
                stack.push_range(std::get<1>(order[child]));
                visited.insert(child);
            }
        }
    }
}

void reorder(int first, int second, std::map<int, std::tuple<int, std::vector<int>>> &order)
{
    if (order.find(first) == order.end()) // first item is not in the map yet:
    {
        if (order.find(second) == order.end()) // second item is not in the map yet
        {
            order[first] = std::make_tuple(0, std::vector<int>{second});
            order[second] = std::make_tuple(1, std::vector<int>{});
        }
        else if (order.find(second) != order.end()) // second item is in the map, but the first item is not.
        {
            order[first] = std::make_tuple(0, std::vector<int>{second});
            // be sure the second is greater than the first one, or update the whole childs
            if (std::get<0>(order[second]) > 0)
            {
                // do nothing
            }
            else {
                // recursively update all child trees with the new value
                std::get<0>(order[second]) = 1;
                updateChildIterative(order, second);
            }
        }

    }
    else if (order.find(first) != order.end())
    {
        if (order.find(second) == order.end())
        {
            std::get<1>(order[first]).push_back(second);
            order[second] = std::make_tuple(std::get<0>(order[first]) + 1, std::vector<int>{});
        }
        else if (order.find(second) != order.end())
        {
            std::get<1>(order[first]).push_back(second);
            if (std::get<0>(order[second]) > std::get<0>(order[first]))
            {
                // do nothing
            }
            else {
                std::get<0>(order[second]) = std::get<0>(order[first]) + 1;
                // recursively update all child trees with the new value
                updateChildIterative(order, second);
            }


        }
    }
}

void placeInDict(int first, int second, std::map<int, std::vector<int>> &relationMap)
{
    if (relationMap.find(first) == relationMap.end())
    {
        relationMap[first] = std::vector<int>{second};
    }
    else
    {
        relationMap[first].push_back(second);
    }
}

std::ostream& operator<<(std::ostream &os, const std::vector<int> &vec)
{
    os << "[";
    for (int i = 0; i < vec.size(); ++i)
    {
        os << vec[i];
        if (i != vec.size() - 1)
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

int main() {
    std::cout << "Day 05, FirstQuestion" << std::endl;

    //std::map<int, std::tuple<int, std::vector<int>>> order;
    std::map<int, std::vector<int>> relationMap;
    int sum = 0;


    std::ifstream file("../input.txt");
    if (file.is_open())
    {
        bool prepDone = false;
        std::string line;
        while (std::getline(file, line))
        {
            if (line == "")
            {
                prepDone = true;
                continue;
            }

            if (!prepDone)
            {
                int first, second;
                sscanf(line.c_str(), "%d|%d", &first, &second);
                //reorder(first, second, order);
                placeInDict(first, second, relationMap);
            }
            else
            {
                // parse line into vector of ints (1,3,46,98) -> [1,3,46,98]
                std::vector<int> values;
                std::string value;
                std::stringstream ss(line);
                while (std::getline(ss, value, ','))
                {
                    values.push_back(std::stoi(value));
                }

                bool isSelected = true;
                for (int i = 0; i < values.size() ; ++i)
                {
                    std::vector<int> searchVector;
                    std::copy(values.begin(), values.end() - (i + 1), std::inserter(searchVector, searchVector.begin()));
                    auto mapValue = relationMap[values[values.size()-(i+1)]];
                    std::sort(searchVector.begin(), searchVector.end());
                    std::sort(mapValue.begin(), mapValue.end());

                    std::vector<int> intersectVector;
                    std::set_intersection(searchVector.begin(), searchVector.end(), mapValue.begin(), mapValue.end(), std::back_inserter(intersectVector));

                    if (intersectVector.size() > 0)
                    {
                        isSelected = false;
                        break;
                    }
                }

                if (isSelected)
                {
                    //auto middle = values.begin() + values.size() / 2;
                    //sum+= *middle;
                }
                else{
                    std::sort(values.begin(), values.end(), [relationMap](int a, int b) { return
                            !(std::find(relationMap.at(b).begin(), relationMap.at(b).end(), a) != relationMap.at(b).end()); });
                    auto middle = values.begin() + values.size() / 2;
                    sum+= *middle;
                }

            }
        }

        file.close();
    }
    else {
        std::cerr << "Unable to open file" << std::endl;
    }


    std::cout << "Sum: " << sum << std::endl;

    return 0;
}
