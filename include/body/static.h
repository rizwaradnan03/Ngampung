#include <raylib.h>
#include <string>
#include <body/body.h>
#include <cstdint>
#include <vector>
#include <chrono>
#include <utility>

#pragma once

class Static: public Body {
    using Body::Init;
    using Body::Run;

    public:
        void Init(int32_t x, int32_t y, int32_t w, int32_t h, int32_t health, bool anchor, bool is_can_collide, int32_t layer, std::vector<int32_t>* collide_masks, std::string texture) override;
        void Display() override;
        void Delete() override;
        void Run(std::string* action, const std::pair<std::string*, std::pair<int32_t, int32_t>>& mouse, const std::vector<Static*>& static_objects);
        
        void mouse_checker(const std::pair<std::string*, std::pair<int32_t, int32_t>>& mouse);

        void action_check(std::string* action);
        void affect_by_action(std::string action);

        void physics(const std::vector<Static*>& static_objects);
        void reset_max_time_checker();

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

        std::chrono::time_point<std::chrono::high_resolution_clock>* get_max_time_before_break();
        void set_max_time_before_break(std::chrono::time_point<std::chrono::high_resolution_clock>* max_time_before_break);

        std::vector<int32_t>* get_collide_masks();
        void set_collide_masks(std::vector<int32_t>* collide_masks);

        int32_t get_health();
        void set_health(int32_t health);

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

        std::chrono::time_point<std::chrono::high_resolution_clock>* max_time_before_break;;

        int32_t health;
        Texture texture;
};