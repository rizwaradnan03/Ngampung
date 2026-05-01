#include <raylib.h>
#include <string>
#include <body/body.h>
#include <cstdint>
#include <vector>

#pragma once

class Static: public Body {
    using Body::Init;
    using Body::Run;

    public:
        void Init(int32_t x, int32_t y, int32_t w, int32_t h, int32_t health, bool anchor, bool is_can_collide, int32_t layer, std::vector<int32_t>* collide_masks, std::string texture) override;
        void Display() override;
        void Delete() override;
        void Run(std::string* action, const std::vector<Static*>& static_objects);
        
        void action_check(std::string* action);
        void affect_by_action(std::string action);

        void physics(const std::vector<Static*>& static_objects);

        int32_t get_layer() override;
        void set_layer(int32_t layer) override;

        int32_t get_x() override;
        void set_x(int32_t x) override;

        int32_t get_y() override;
        void set_y(int32_t y) override;

        int32_t get_w() override;
        void set_w(int32_t w) override;

        int32_t get_h() override;
        void set_h(int32_t h) override;

        bool get_is_can_collide();
        void set_is_can_collide(bool is_can_collide);

        bool get_is_free() override;
        void set_is_free(bool is_can_collide) override;

        std::vector<int32_t>* get_collide_masks();
        void set_collide_masks(std::vector<int32_t>* collide_masks);

        ~Static();

    private:
        int32_t layer;
        int32_t x;
        int32_t y;
        int32_t w;
        int32_t h;
        bool anchor;
        bool is_can_collide;
        bool is_free;
        std::vector<int32_t>* collide_masks;

        int32_t health;
        Texture texture;
};