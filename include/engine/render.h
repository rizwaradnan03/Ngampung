#include "string"
#include "raylib.h"

#pragma once

class Render {
    public:
        void Display();
        virtual void Init(int x, int y, bool anchor, std::string texture);
    
    private:
        int x;
        int y;
        Texture texture;
        bool anchor;
};