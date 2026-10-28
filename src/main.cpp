#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::string input;
  std::vector<std::string> builtins = {"echo", "exit", "type"};

  while (true) {
      std::cout << "$ ";
      std::getline(std::cin, input);

      if (input == "exit") {
          break;
      } else if (input.substr(0, 5) == "echo ") {
          std::cout << input.substr(5) << std::endl;
      } else if (input.substr(0, 5) == "type ") {
          // TODO: extract next argument (command) more robustly
          std::string arg = input.substr(5);

          if (std::find(builtins.begin(), builtins.end(), arg) != builtins.end()) {
              std::cout << arg << " is a shell builtin" << std::endl;

          } else {
              std::cout << arg << ": command not found" << std::endl;
          }

      } else {
          std::cout << input << ": command not found" << std::endl;
      }
  }

  return 0;
}
