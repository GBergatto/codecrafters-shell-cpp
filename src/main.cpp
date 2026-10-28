#include <iostream>
#include <string>

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  std::string input;

  while (true) {
      std::cout << "$ ";
      std::cin >> input;

      if (input == "exit") break;

      std::cout << input << ": command not found" << std::endl;
  }

  return 0;
}
