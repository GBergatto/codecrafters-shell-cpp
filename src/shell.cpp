#include <iostream>
#include <string>
#include <unistd.h>
#include <unordered_map>

#include "shell.hpp"

namespace shell {
    namespace {
        const std::unordered_map<std::string, BuiltinFunction> builtinCommands = {
            {"echo", builtins::echo},
            {"type", builtins::type},
        };
    }

    bool isBuiltin(const std::string& command) {
        return builtinCommands.find(command) != builtinCommands.end();
    }

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

    BuiltinFunction getBuiltin(const std::string& command) {
        auto it = builtinCommands.find(command);
        
        if (it != builtinCommands.end()) {
            return it->second;
        }

        return nullptr;
    }

    namespace builtins {
        void echo(std::istringstream& iss) {
            std::string args;
            std::getline(iss >> std::ws, args);
            std::cout << args << std::endl;
        }

        void type(std::istringstream& iss) {
            std::string command;
            iss >> command;
            if (isBuiltin(command)) {
                std::cout << command << " is a shell builtin" << std::endl;
            } else {
                // Seach PATH for executable
                if (auto execPath = findExecutable(command)) {
                    std::cout << command << " is " << execPath.value().c_str() << std::endl;
                } else {
                    std::cout << command << ": not found" << std::endl;
                }
            }
        }
    }
}
