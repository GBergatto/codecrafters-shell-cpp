#include <algorithm>
#include <filesystem>
#include <iostream>
#include <optional>
#include <ostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

std::optional<std::filesystem::path> findExecutable(const std::string& command) {
    if (const char* path = std::getenv("PATH")) {
        std::stringstream stream(path);
        std::string directory;

        while (std::getline(stream, directory, ':')) {
            auto fullPath = std::filesystem::path(directory) / command;
            // TODO: handle empty path (current directory)

            if (std::filesystem::exists(fullPath)) {
                // Check if user has execute permisssion for file
                if (access(fullPath.c_str(), X_OK) == 0) {
                    return fullPath;
                }
            }
        }
    }

    return std::nullopt;
}

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
            std::getline(iss >> std::ws, arg);
            std::cout << arg << std::endl;

        } else if (command == "type") {
            iss >> arg;

            if (std::find(builtins.begin(), builtins.end(), arg) != builtins.end()) {
                std::cout << arg << " is a shell builtin" << std::endl;
            } else {
                // Seach PATH for executable
                if (auto execPath = findExecutable(arg)) {
                    std::cout << command << " is " << execPath.value().c_str() << std::endl;
                } else {
                    std::cout << arg << ": not found" << std::endl;
                }
            }

        } else {
            // Seach PATH for executable

            std::cout << input << ": command not found" << std::endl;
        }
    }

    return 0;
}
