#include "Engine.h"

int Engine::execute(const std::string& command, std::unordered_map<std::string, int> args) {
    try {
        if (commands.find(command) == commands.end()) {
            throw std::runtime_error("command not found\n");
        }
        return (commands.find(command)->second)(args);
    }
    catch (std::exception& ex) {
        std::cout << ex.what();
    }
}