#include <iostream>
#include <sstream>
#include <string>

#include "shell.hpp"


int main() {
    // Flush after every std::cout / std:cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    std::string input;

    while (true) {
        // Read Line
        std::cout << "$ ";
        std::string command, arg;
        std::getline(std::cin, input);
        std::istringstream iss(input);
        iss >> command;

        if (command == "exit") {
            break;

        } else if (auto builtin = shell::getBuiltin(command)) {
            builtin(iss);
        } else {
            // Seach PATH for executable

            std::cout << input << ": command not found" << std::endl;
        }
    }

    return 0;
}
