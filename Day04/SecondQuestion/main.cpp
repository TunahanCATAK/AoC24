#include <iostream>
#include <fstream>
#include <vector>
#include <coroutine>

template<typename T>
class generator {
public:
    struct promise_type {
        T currentSubMatrix;

        auto get_return_object() {
            return generator{std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        std::suspend_always initial_suspend() noexcept { return {}; }

        std::suspend_always final_suspend() noexcept { return {}; }

        std::suspend_always yield_value(T subMatrix) noexcept {
            currentSubMatrix = subMatrix;
            return {};
        }

        void return_void() {}

        void unhandled_exception() {
            throw;
        }
    };

    using handle_type = std::coroutine_handle<promise_type>;

    explicit generator(handle_type handle) : coro_handle(handle) {}

    ~generator() {
        if (coro_handle) coro_handle.destroy();
    }

    generator(const generator&) = delete;
    generator& operator=(const generator&) = delete;

    generator(generator&& other) noexcept : coro_handle(other.coro_handle) {
        other.coro_handle = nullptr;
    }

    generator& operator=(generator&& other) noexcept {
        if (this != &other) {
            if (coro_handle) coro_handle.destroy();
            coro_handle = other.coro_handle;
            other.coro_handle = nullptr;
        }
        return *this;
    }

    T next() {
        if (coro_handle && !coro_handle.done()) {
            coro_handle.resume();
            return coro_handle.done() ? T() : coro_handle.promise().currentSubMatrix;
        }
        return {};
    }

private:
    handle_type coro_handle;

};


std::vector<std::vector<char>> getSubMatrix(const std::vector<std::vector<char>>& matrix, int startRow, int startCol, int size) {
    std::vector<std::vector<char>> subMatrix(size, std::vector<char>(size));
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            subMatrix[i][j] = matrix[startRow + i][startCol + j];
        }
    }
    return subMatrix;
}


generator<std::vector<std::vector<char>>> slidingWindow3x3(const std::vector<std::vector<char>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    int windowSize = 3;

    for (int i = 0; i <= rows - windowSize; ++i) {
        for (int j = 0; j <= cols - windowSize; ++j) {
            auto subMatrix = getSubMatrix(matrix, i, j, windowSize);
            co_yield subMatrix;
        }
    }
}

int main() {
    std::cout << "Day 04, SecondQuestion" << std::endl;

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

    auto gen = slidingWindow3x3(maze);
    auto nextOne = gen.next();
    int sum = 0;
    while (nextOne.size() > 0)
    {
        if (nextOne[0][0] == 'M' && nextOne[0][2] == 'S' && nextOne[2][0] == 'M' && nextOne[2][2] == 'S' && nextOne[1][1] == 'A')
        {
            sum++;
        }
        else if (nextOne[0][0] == 'S' && nextOne[0][2] == 'S' && nextOne[2][0] == 'M' && nextOne[2][2] == 'M' && nextOne[1][1] == 'A')
        {
            sum++;
        }
        else if (nextOne[0][0] == 'S' && nextOne[0][2] == 'M' && nextOne[2][0] == 'S' && nextOne[2][2] == 'M' && nextOne[1][1] == 'A')
        {
            sum++;
        }
        else if (nextOne[0][0] == 'M' && nextOne[0][2] == 'M' && nextOne[2][0] == 'S' && nextOne[2][2] == 'S' && nextOne[1][1] == 'A')
        {
            sum++;
        }

        nextOne = gen.next();
    }

    std::cout << "Sum: " << sum << std::endl;
    return 0;
}
