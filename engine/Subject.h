#pragma once
#include <iostream>
#include <string>
#include "Engine.h"

class Subject {
public:
    int f1(int a, int b) {
        return a + b;
    };

    int f2(int a) {
        return a * a;
    };

    int f3(int a, int b) {
        return a * b;
    };
};
