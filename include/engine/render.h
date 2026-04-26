#include <string>
#include <raylib.h>
#include <cstdint>
#include <vector>

#pragma once

class Render {
    public:
        virtual void Display();
        virtual void Init(int32_t x, int32_t y, int32_t* health, bool anchor, bool is_can_collide, int32_t layer, std::vector<int32_t>* collide_masks, std::string texture);
        virtual void Delete();
        virtual void Run();
        
    private:
        int32_t layer;
        int32_t x;
        int32_t y;
        Texture texture;
        bool anchor;
        bool is_can_collide;
        std::vector<int32_t>* collide_masks;
};