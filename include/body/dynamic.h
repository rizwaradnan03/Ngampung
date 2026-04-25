#include "engine/render.h"
#include "cstdint"
#include "raylib.h"
#include "string"

#pragma once

class Dynamic: public Render {
    using Render::Init;

    public:    
        void Init(int32_t x, int32_t y, int32_t* health, bool anchor, bool is_can_collide, std::string texture) override;
        void Run() override;
        void Display() override;
        void Movement(); 

    private:
        int32_t x;
        int32_t y;
        int32_t* health;
        bool anchor;
        bool is_can_collide;

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