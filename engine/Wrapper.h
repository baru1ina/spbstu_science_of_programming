#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <functional>
#include <variant>

template <typename T, typename... args>
class Wrapper {
private:
    using Func = int (T::*)(args...);

    T* subject;
    Func function;

    std::unordered_map<std::string, int> arguments;
    std::vector<int> vals;

public:
    Wrapper(T* _subject, Func _func, std::unordered_map<std::string, int> _args) {
        subject = _subject;
        function = _func;
        for (const auto& pair : _args) {
            arguments[pair.first] = pair.second;
        }
    }

    template<size_t... idx>
    int call(std::index_sequence<idx...>) {
        return (subject->*function)(vals[idx]...);
    }

    int execute(std::unordered_map<std::string, int> _args) {
        try { 
            if (sizeof...(args) != _args.size()) {
                throw std::runtime_error("invalid number of arguments\n");
            }
            for (const auto& pair : _args) {
                vals.push_back(pair.second);
            }
            int result = call(std::make_index_sequence<sizeof...(args)>{});
            return result;
        }
        catch (std::exception& ex) {
            std::cout << ex.what();
        }
        
    }
};