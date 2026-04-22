#include "raylib.h"
#include "string"
#include "engine/render.h"

#pragma once

class Static: public Render {
    public:
        ~Static();
        void Display() override;
        void Init(int x, int y, bool anchor, std::string texture) override;

    private:
        int x;
        int y;
        Texture texture;
        bool anchor;
};