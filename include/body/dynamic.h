#include "engine/render.h"
#include "cstdint"
#include "raylib.h"
#include "string"

#pragma once

class Dynamic: public Render {
    // to use the same function
    using Render::Init;

    public:    
        void Init(int x, int y, bool anchor, std::string texture);
        void Display() override;
        void Move(); 

    private:
        int32_t x;
        int32_t y;
        int32_t health;
        bool anchor;

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