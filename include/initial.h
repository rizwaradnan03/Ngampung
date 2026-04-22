#include "vector"
#include "raylib.h"
#include "string"

#pragma once

class Initial{
    public:
        Initial();
        Texture* find_block_by_name(std::string name);

        std::vector<std::pair<std::string, Texture>> block;
};

extern Initial* G_initial;