#include <engine/render.h>
#include <body/body.h>
#include <cstdint>
#include <raylib.h>
#include <string>
#include <vector>
#include <body/static.h>
#include <utility>
#include <struct/dynamic.h>
#include <chrono>

#pragma once

class Dynamic: public Body {
    using Body::Init;

    public:    
        void Init(int32_t x, int32_t y, int32_t w, int32_t h, int32_t health, bool anchor, bool is_can_collide, int32_t layer, std::vector<int32_t>* collide_masks, std::string texture) override;
        void Run(const std::vector<Static*>& static_objects, const std::vector<Dynamic*>& dynamic_objects);
        void Display() override;
        void Delete() override;

        void Movement(); 
        void mouse_movement(const std::vector<Static*>& static_objects, const std::vector<Dynamic*>& dynamic_objects);

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

        int32_t get_health();
        void set_health(int32_t health);

        int32_t get_jump_amount();
        void set_jump_amount(int32_t jump_amount);

        bool get_is_can_collide();
        void set_is_can_collide(bool is_can_collide);

        bool get_anchor();
        void set_anchor(bool anchor);

        bool get_is_free() override;
        void set_is_free(bool is_free) override;

        std::pair<bool, bool> get_available_direction();
        void set_available_direction(std::pair<bool, bool> movement_direction);

        std::vector<Render*> get_inventory();
        void set_inventory(std::vector<Render*> inventory);

        std::string get_movement_action();
        void set_movement_action(std::string movement_action);

        std::string get_movement_direction();
        void set_movement_direction(std::string movement_direction);

        std::chrono::time_point<std::chrono::high_resolution_clock> get_start_jump();
        void set_start_jump(std::chrono::time_point<std::chrono::high_resolution_clock> start_jump);

        void physics(const std::vector<Static*>& static_objects, const std::vector<Dynamic*>& dynamic_objects);
        void box_collide_checker(const std::vector<Static*>& static_objects, const std::vector<Dynamic*>& dynamic_objects);
        void gravity(const std::vector<Static*>& static_objects, const std::vector<Dynamic*>& dynamic_objects);

    private:
        int32_t layer;
        int32_t x;
        int32_t y;
        int32_t w;
        int32_t h;
        int32_t health;
        int32_t jump_amount;
        
        bool is_free;

        std::pair<bool, bool> available_direction;

        std::chrono::time_point<std::chrono::high_resolution_clock> start_jump;
        std::string movement_action;
        std::string movement_direction;

        bool anchor;
        
        bool is_can_collide;
        std::vector<int32_t>* collide_masks;

        Texture u_head;
        Texture u_face;
        Texture u_neck;
        
        Texture m_body;
        Texture m_r_hand;
        Texture m_l_hand;

        Texture l_leg;
        Texture l_foot;

        std::vector<Render*> inventory;
};