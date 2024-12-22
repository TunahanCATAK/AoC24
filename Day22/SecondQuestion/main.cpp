#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <ranges>
#include <set>

struct slicingWindow {
    int first;
    int second;
    int third;
    int fourth;

    bool operator==(const slicingWindow& other) const {
        return first == other.first &&
               second == other.second &&
               third == other.third &&
               fourth == other.fourth;
    }
};

struct slicingWindowHash {
    std::size_t operator()(const slicingWindow& window) const {
        std::size_t h1 = std::hash<int>()(window.first);
        std::size_t h2 = std::hash<int>()(window.second);
        std::size_t h3 = std::hash<int>()(window.third);
        std::size_t h4 = std::hash<int>()(window.fourth);

        // Combine the hash values using XOR and a prime multiplier
        return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
    }
};

int main() {
    std::cout << "Day 22, SecondQuestion" << std::endl;
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

    //numbers = {123};
    std::vector<std::vector<int>> changes;
    std::vector<std::vector<int>> prices;
    for (auto number : numbers) {
        auto secret = number;
        std::vector<int> individualChanges;
        std::vector<int> individualPrices;
        long prevSecretLastDigit = secret % 10;
        for (int i = 0; i < 1999; ++i){
            long long calculated = secret * 64;
            secret = mix(calculated, secret);
            secret = prune(secret);
            calculated = secret /32 ;
            secret = mix(calculated, secret);
            secret = prune(secret);
            calculated = secret * 2048;
            secret = mix(calculated, secret);
            secret = prune(secret);

            auto secretLastDigit = secret % 10;

            //std::cout << "Secret: " << secret << std::endl;
            //std::cout << "Secret Last Digit: " << secretLastDigit << std::endl;
            // add the difference between the secret's last digit with the last element in the vector individualChanges
            individualPrices.push_back(secretLastDigit);
            individualChanges.push_back(secretLastDigit - prevSecretLastDigit);

            prevSecretLastDigit = secretLastDigit;
        }
        prices.push_back(individualPrices);
        changes.push_back(individualChanges);
    }

//    for (const auto& change : changes) {
//        for (int i = 0; i < change.size(); ++i) {
//            std::cout << change[i] << " ";
//        }
//        std::cout << std::endl;
//    }

    std::unordered_map<slicingWindow, int, slicingWindowHash> windowFrequencies;
    std::unordered_map<slicingWindow, int, slicingWindowHash> windowFrequencyBananas;
    for (int i = 0; i < changes.size(); ++i) {
        std::unordered_map<slicingWindow, bool, slicingWindowHash> soldWindows;
        for (int j = 0; j < changes[i].size() - 4; ++j) {
            slicingWindow window{changes[i][j], changes[i][j+1], changes[i][j+2], changes[i][j+3]};
            if (soldWindows.find(window) != soldWindows.end()) {
                continue;
            }
            soldWindows[window] = true;
            windowFrequencies[window]++;
            windowFrequencyBananas[window] += prices[i][j+3];
        }
    }

    slicingWindow maxWindow;
    int maxFrequency = 0;
    for (const auto& [key, value] : windowFrequencies) {
        if (value > maxFrequency) {
            maxFrequency = value;
            maxWindow = key;
        }
    }

    std::cout << "Max Frequency: " << maxFrequency << std::endl;
    std::cout << "Max Window: " << maxWindow.first << " " << maxWindow.second << " " << maxWindow.third << " " << maxWindow.fourth << std::endl;

//    for (const auto& [key, value]: windowFrequencies){
//        std::cout << key.first << " " << key.second << " " << key.third << " " << key.fourth << " : " << value << std::endl;
//    }

    slicingWindow maxWindowBasedPrice;
    int maxFrequencyBasedPrice = 0;
    for (const auto& [key, value] : windowFrequencyBananas) {
        if (value > maxFrequencyBasedPrice) {
            maxFrequencyBasedPrice = value;
            maxWindowBasedPrice = key;
        }
    }

    std::cout << "Max Frequency Based Price: " << maxFrequencyBasedPrice << std::endl;
    std::cout << "Max Window Based Price: " << maxWindowBasedPrice.first << " " << maxWindowBasedPrice.second << " " << maxWindowBasedPrice.third << " " << maxWindowBasedPrice.fourth << std::endl;


//
//    for (int i = 0; i < prices.size(); ++i) {
//        std::cout << i << "th Individual Prices:" << std::endl;
//        for (int j = 0; j < prices[i].size() - 4; ++j) {
//            std::cout << prices[i][j] << " (" << changes[i][j] << ") \n";
//        }
//    }


    return 0;
}
