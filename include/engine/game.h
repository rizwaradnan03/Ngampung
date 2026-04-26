#include <vector>
#include <utility>
#include <body/dynamic.h>
#include <body/static.h>
#include <string>

#pragma once

class Game {
    public:
        void Start();
        void Habit(std::string* action);

    private:
        std::vector<std::pair<int, std::vector<Static*>>> to_render_static;
        Dynamic* player;
};