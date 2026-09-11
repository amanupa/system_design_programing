#pragma once
#include "jump.h"
#include<iostream>
#include <memory>
using namespace std;

class Cell {
private:
    std::unique_ptr<Jump> jump;

public:
    Cell() = default;

    void setJump(unique_ptr<Jump> j) {
        jump = std::move(j);
    }

    Jump* getJump() const {
        return jump.get();
    }
};
