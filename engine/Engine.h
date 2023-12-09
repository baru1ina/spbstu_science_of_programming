#pragma once
#include "Wrapper.h"

class Engine {
private:
	std::unordered_map<std::string, std::function<int(std::unordered_map<std::string, int>)>> commands;

public:
	template <typename T, typename... args>
	void register_command(Wrapper<T, args...>* wrapper, const std::string& command) {
        try {
            if (commands.find(command) != commands.end()) {
                throw std::runtime_error("command named " + command + " already exists\n");
            }
            else {
                commands[command] = [wrapper](std::unordered_map<std::string, int> _args) {
                    return wrapper->execute(_args);
                    };
            }
        }
        catch (std::exception& ex) {
            std::cout << ex.what();
        }
	}
    int execute(const std::string& command, std::unordered_map<std::string, int> args);
};

