#include <string>
#include <raylib.h>
#include <cstdint>
#include <vector>

#pragma once

class Render {
    public:
        virtual void Display();
        virtual void Init(int32_t x, int32_t y, int32_t w, int32_t h, int32_t health, bool anchor, bool is_can_collide, int32_t layer, std::vector<int32_t>* collide_masks, std::string texture);
        virtual void Delete();
        virtual void Run();
        
        virtual int32_t get_layer();
        virtual void set_layer(int32_t layer);

        virtual int32_t get_x();
        virtual void set_x(int32_t x);

        virtual int32_t get_y();
        virtual void set_y(int32_t y);

        virtual int32_t get_w();
        virtual void set_w(int32_t w);

        virtual int32_t get_h();
        virtual void set_h(int32_t h);

    private:
        int32_t layer;
        int32_t x;
        int32_t y;
        int32_t w;
        int32_t h;
        Texture texture;
        bool anchor;
        bool is_can_collide;
        std::vector<int32_t>* collide_masks;
};