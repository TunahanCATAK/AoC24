import os
import requests

# Replace with your Advent of Code session cookie
SESSION_COOKIE = "53616c7465645f5fe760441e17c5751180478d6b99add5c046cb0c3c87925e24f3e0fffe8dbcaaa41f6d786fb567b9c7327e5ab3fb71e59665adf10803d68913"

def create_day_folder(day_num):
    day_folder = f"Day{day_num:02}"
    os.makedirs(day_folder, exist_ok=True)

    # Create subfolders and CMakeLists.txt for both questions
    for question in ["FirstQuestion", "SecondQuestion"]:
        question_folder = os.path.join(day_folder, question)
        os.makedirs(question_folder, exist_ok=True)

        cmake_file_content = f"""cmake_minimum_required(VERSION 3.24)
project(Day{day_num:02}_{question})

set(CMAKE_CXX_STANDARD 23)

add_executable(Day{day_num:02}_{question} main.cpp)
"""
        cmake_file_path = os.path.join(question_folder, "CMakeLists.txt")
        with open(cmake_file_path, "w") as cmake_file:
            cmake_file.write(cmake_file_content)

        # Create a sample main.cpp file
        main_cpp_content = f"""#include <iostream>

int main() {{
    std::cout << "Day {day_num:02}, {question}" << std::endl;
    return 0;
}}
"""
        main_cpp_path = os.path.join(question_folder, "main.cpp")
        with open(main_cpp_path, "w") as main_cpp_file:
            main_cpp_file.write(main_cpp_content)

    return day_folder

def update_root_cmake(day_num):
    root_cmake_path = "CMakeLists.txt"
    if os.path.exists(root_cmake_path):
        with open(root_cmake_path, "r") as file:
            content = file.readlines()
    else:
        content = ["cmake_minimum_required(VERSION 3.24)\n", "project(AdventOfCode2024)\n", "set(CMAKE_CXX_STANDARD 23)\n\n"]

    # Add subdirectories for the new day
    new_entry = f"add_subdirectory(Day{day_num:02})\n"
    if new_entry not in content:
        content.append(new_entry)

    with open(root_cmake_path, "w") as file:
        file.writelines(content)

def get_input(day_num):
    url = f"https://adventofcode.com/2024/day/{day_num}/input"
    headers = {"Cookie": f"session={SESSION_COOKIE}"}
    try:
        response = requests.get(url, headers=headers, timeout=10)
        if response.status_code == 200:
            return response.text
        elif response.status_code == 403:
            print("Forbidden: Check your session cookie.")
        elif response.status_code == 404:
            print(f"Not Found: Day {day_num} is not available yet.")
        else:
            print(f"HTTP Error {response.status_code}: Unable to fetch input.")
    except requests.RequestException as e:
        print(f"Request failed: {e}")
    return None

def save_input(day_folder, day_num):
    input_data = get_input(day_num)
    if input_data:
        input_path = os.path.join(day_folder, "input.txt")
        with open(input_path, "w") as input_file:
            input_file.write(input_data)

def main():
    print("Enter the day number you want to set up (1-25):")
    day_num = int(input())
    day_folder = create_day_folder(day_num)
    update_root_cmake(day_num)
    save_input(day_folder, day_num)
    print(f"Setup completed for Day {day_num:02}.")

if __name__ == "__main__":
    main()
