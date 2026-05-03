#include <engine/render.h>
#include <vector>
#include <string>

#pragma once

class Static;
class Dynamic;

class Body: public Render {
    public:
        virtual void Display();
        virtual void Init(int32_t x, int32_t y, int32_t w, int32_t h, int32_t health, bool anchor, bool is_can_collide, int32_t layer, std::vector<int32_t>* collide_masks, std::string texture);
        virtual void Delete();
        virtual void Run(std::string* action, const std::vector<Static*>& static_objects, const std::vector<Dynamic*>& dynamic_objects);
        
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

        virtual bool get_is_can_collide();
        virtual void set_is_can_collide(bool is_can_collide);

        virtual bool get_is_free();
        virtual void set_is_free(bool is_free);

    private:
        int32_t layer;
        int32_t x;
        int32_t y;
        int32_t w;
        int32_t h;
        Texture texture;
        bool anchor;
        bool is_can_collide;
        bool is_free;
        std::vector<int32_t>* collide_masks;

        int32_t amount;
};