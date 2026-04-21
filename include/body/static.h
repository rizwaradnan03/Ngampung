#include "raylib.h"
#include "string"

#pragma once

class Static {
    public:
        Static(int x, int y, std::string texture);
        ~Static();
        void Render();

    private:
        int x;
        int y;
        Texture texture;
};