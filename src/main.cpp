#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

int main() {
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::string input;
    std::vector<std::string> builtins = {"echo", "exit", "type"};

    while (true) {
        // Read Line
        std::cout << "$ ";
        std::string command, arg;
        std::getline(std::cin, input);
        std::istringstream iss(input);
        iss >> command;

        if (command == "exit") {
            break;

        } else if (command == "echo") {
            iss >> arg;
            std::cout << arg << std::endl;

        } else if (command == "type") {
            iss >> arg;

            if (std::find(builtins.begin(), builtins.end(), arg) != builtins.end()) {
                std::cout << arg << " is a shell builtin" << std::endl;
            } else {
                std::cout << arg << ": not found" << std::endl;
            }

        } else {
            // Seach PATH for executable

            std::cout << input << ": command not found" << std::endl;
        }
    }

    return 0;
}
