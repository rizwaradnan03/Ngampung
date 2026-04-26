#include <engine/render.h>
#include <cstdint>
#include <raylib.h>
#include <string>
#include <vector>
#include <body/static.h>
#include <utility>

#pragma once

class Dynamic: public Render {
    using Render::Init;

    public:    
        void Init(int32_t x, int32_t y, int32_t* health, bool anchor, bool is_can_collide, std::vector<int32_t>* collide_masks, std::string texture) override;
        void Run(const std::vector<std::pair<int, std::vector<Static*>>>& static_objects);
        void Display() override;
        void Movement(); 

        void physics(const std::vector<std::pair<int, std::vector<Static*>>>& static_objects);

    private:
        int32_t x;
        int32_t y;
        int32_t* health;
        bool anchor;
        bool is_can_collide;
        std::vector<int32_t>* collide_masks;

        // upper body
        Texture u_head;
        Texture u_face;
        Texture u_neck;
        
        // mid body
        Texture m_body;
        Texture m_r_hand;
        Texture m_l_hand;

        // lower body
        Texture l_leg;
        Texture l_foot;
};