#include "vector"
#include "utility"
#include "engine/render.h"

#pragma once

class Game {
    public:
        void Start();
        void Display();

    private:
        std::vector<std::pair<int, std::vector<Render*>>> to_render;
};