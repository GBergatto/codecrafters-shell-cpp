#include <filesystem>
#include <optional>
#include <string>
#include <sstream>

namespace shell {
    std::optional<std::filesystem::path> findExecutable(const std::string& command);

    using BuiltinFunction = void (*)(std::istringstream&);

    BuiltinFunction getBuiltin(const std::string& command);

    namespace builtins {
        void echo(std::istringstream& iss);
        void type(std::istringstream& iss);
    }
}

