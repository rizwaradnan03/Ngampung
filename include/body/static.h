#include <raylib.h>
#include <string>
#include <engine/render.h>
#include <cstdint>
#include <vector>

#pragma once

class Static: public Render {
    using Render::Init;
    using Render::Run;

    public:
        void Init(int32_t x, int32_t y, int32_t* health, bool anchor, bool is_can_collide, int32_t layer, std::vector<int32_t>* collide_masks, std::string texture) override;
        void Display() override;
        void Delete() override;
        void Run(std::string* action, const std::vector<Static*>& static_objects);
        
        void action_check(std::string* action);
        void affect_by_action(std::string action);

        void physics(const std::vector<Static*>& static_objects);

        int32_t get_layer();
        void set_layer(int32_t layer);

        int32_t get_x();
        void set_x(int32_t x);

        int32_t get_y();
        void set_y(int32_t y);

        bool get_is_can_collide();
        void set_is_can_collide(bool is_can_collide);

        std::vector<int32_t>* get_collide_masks();
        void set_collide_masks(std::vector<int32_t>* collide_masks);

        ~Static();

    private:
        int32_t layer;
        int32_t x;
        int32_t y;
        bool anchor;
        bool is_can_collide;
        std::vector<int32_t>* collide_masks;

        int32_t* health;
        Texture texture;
};