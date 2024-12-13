#include <iostream>
#include <fstream>
#include <regex>

int main() {
    std::cout << "Day 13, FirstQuestion" << std::endl;

    auto calculateCost = [](int xa, int ya, int xb, int yb, int x, int y) -> long {
        long top = yb * x - xb * y;
        long bottom = xa * yb - xb * ya;
        if (top % bottom == 0) {
            long n = top / bottom;
            if (n > 0 && n < 100)
            {
                long mtop = (y - ya * n);
                if (mtop % yb == 0)
                {
                    long m = mtop / yb;
                    if (m > 0 && m < 100)
                    {
                        return n * 3 + m * 1;
                    }
                }
                else {
                    std::cout << "No solution" << std::endl;
                    return 0;
                }
            }
        } else {
            std::cout << "No solution" << std::endl;
            return 0;
        }
    };

    long sum = 0;
    std::ifstream file("../input.txt");
    if (file.is_open())
    {
        std::string line;
        int readOrder = 0;
        while (std::getline(file, line)) {
            //std::cout << line << std::endl;

            // Variables to store the extracted values
            int xa, ya, xb, yb, x, y;

            // Regular expressions for each line
            std::regex buttonARegex(R"(Button A: X\+(\d+), Y\+(\d+))");
            std::regex buttonBRegex(R"(Button B: X\+(\d+), Y\+(\d+))");
            std::regex prizeRegex(R"(Prize: X=(\d+), Y=(\d+))");
            std::smatch match;

            if (std::regex_match(line, match, buttonARegex)) {
                xa = std::stoi(match[1]);
                ya = std::stoi(match[2]);
                readOrder++;
            } else if (std::regex_match(line, match, buttonBRegex)) {
                xb = std::stoi(match[1]);
                yb = std::stoi(match[2]);
                readOrder++;
            } else if (std::regex_match(line, match, prizeRegex)) {
                x = std::stoi(match[1]);
                y = std::stoi(match[2]);
                readOrder++;
            } else{
                readOrder = 0;
            }

            if (readOrder == 3) {
                //std::cout << xa << " " << ya << " " << xb << " " << yb << " " << x << " " << y << std::endl;
                sum += calculateCost(xa, ya, xb, yb, x, y);
            }
        }
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
    }

    std::cout << "Cost: " << sum << std::endl;

    return 0;
}
