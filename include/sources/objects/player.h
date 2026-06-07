#include <nodes/body/dynamic.h>
#include <cstdint>
#include <raylib.h>
#include <string>
#include <vector>
#include <utility>
#include <struct/dynamic.h>
#include <chrono>
#include <nodes/body/body.h>
#include <sources/gui/inventory.h>
#include <engine/render.h>

#pragma once

class Static;

class Player: public Dynamic {
    using Dynamic::Init;

    public:    
        void Init(int32_t x, int32_t y, int32_t w, int32_t h, int32_t health, bool anchor, bool is_can_collide, int32_t layer, std::vector<int32_t>* collide_masks, std::string texture) override;
        void Run(std::string* action, const std::vector<Static*>& static_objects, const std::vector<Dynamic*>& dynamic_objects);
        void Display();
        void Delete();
        void Movement(); 
        void mouse_movement(const std::vector<Static*>& static_objects, const std::vector<Dynamic*>& dynamic_objects);
        void reset_oxygen_level_checker();

        int32_t get_layer();
        void set_layer(int32_t layer);

        std::vector<int32_t>* get_collide_masks();
        void set_collide_masks(std::vector<int32_t>* collide_masks);

        int32_t get_x();
        void set_x(int32_t x);

        int32_t get_y();
        void set_y(int32_t y);

        int32_t get_w();
        void set_w(int32_t w);

        int32_t get_h();
        void set_h(int32_t h);

        int32_t get_health();
        void set_health(int32_t health);

        int32_t get_oxygen_level();
        void set_oxygen_level(int32_t oxygen_level);

        std::chrono::time_point<std::chrono::high_resolution_clock>* get_dive_time();
        void set_dive_time(std::chrono::time_point<std::chrono::high_resolution_clock>* dive_time);

        std::string get_state();
        void set_state(std::string state);

        int32_t get_jump_amount();
        void set_jump_amount(int32_t jump_amount);

        bool get_is_can_collide();
        void set_is_can_collide(bool is_can_collide);

        bool get_anchor();
        void set_anchor(bool anchor);

        bool get_is_free();
        void set_is_free(bool is_free);

        std::pair<bool, bool> get_available_direction();
        void set_available_direction(std::pair<bool, bool> movement_direction);

        std::string get_movement_action();
        void set_movement_action(std::string movement_action);

        std::string get_movement_direction();
        void set_movement_direction(std::string movement_direction);

        std::string* get_mouse_action();
        void set_mouse_action(std::string* mouse_action);

        std::chrono::time_point<std::chrono::high_resolution_clock> get_start_jump();
        void set_start_jump(std::chrono::time_point<std::chrono::high_resolution_clock> start_jump);

        GUI_Inventory* get_inventory();
        void set_inventory(GUI_Inventory* inventory);
        
        Render* get_selected_item();
        void set_selected_item(Render* selected_item);

        void fixed_on_screen_run();
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

        int32_t oxygen_level;
        std::chrono::time_point<std::chrono::high_resolution_clock>* dive_time;
        std::string state;

        bool is_free;

        std::pair<bool, bool> available_direction;

        std::chrono::time_point<std::chrono::high_resolution_clock> start_jump;
        std::string movement_action;
        std::string movement_direction;
        std::string* mouse_action;

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

        GUI_Inventory* inventory;
        Render* selected_item;
};