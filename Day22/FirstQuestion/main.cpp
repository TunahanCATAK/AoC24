#include <iostream>
#include <fstream>
#include <vector>
#include <functional>

int main() {
    std::cout << "Day 22, FirstQuestion" << std::endl;
    std::bit_xor<long long> bitXor;
    std::vector<long> numbers;

    std::ifstream file("../input.txt");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            numbers.push_back(std::stol(line));
        }
    }
    else {
        std::cerr <<  "Unable to open file" << std::endl;
    }

    auto mix = [&bitXor](long long lhs, long long rhs) -> long long {
        return bitXor(lhs,rhs);
    };

    auto prune = [](long long number) -> long{
        return (long) (number % 16777216);
    };


    std::vector<long> calc2000th; // 2000th calculation
    for (auto number : numbers) {
        auto secret = number;
        for (int i = 0; i < 2000; ++i){
            long long calculated = secret * 64;
            secret = mix(calculated, secret);
            secret = prune(secret);
            calculated = secret /32 ;
            secret = mix(calculated, secret);
            secret = prune(secret);
            calculated = secret * 2048;
            secret = mix(calculated, secret);
            secret = prune(secret);
        }
        calc2000th.push_back(secret);
    }

    long sum = 0;
    for (auto number : calc2000th) {
        std::cout << number << std::endl;
        sum += number;
    }

    std::cout << "Sum: " <<sum << std::endl;

    return 0;
}
