#include "body/dynamic.h"

void Dynamic::Init(int x, int y, bool anchor, std::string texture){
    this->x = x;
    this->y = y;
    this->anchor = anchor;
    // this->texture = texture;
}

void Dynamic::Display(){
    // upper body
    DrawTextureEx(this->u_head, {(float)this->x, (float)this->y}, 0.2f, 0.2f, GREEN);
    DrawTextureEx(this->u_face, {(float)this->x, (float)this->y}, 0.2f, 0.2f, GREEN);
    DrawTextureEx(this->u_neck, {(float)this->x, (float)this->y}, 0.2f, 0.2f, GREEN);
    
    //middle body
    DrawTextureEx(this->m_body, {(float)this->x, (float)this->y}, 0.2f, 0.2f, GREEN);
    DrawTextureEx(this->m_l_hand, {(float)this->x, (float)this->y}, 0.2f, 0.2f, GREEN);
    DrawTextureEx(this->m_r_hand, {(float)this->x, (float)this->y}, 0.2f, 0.2f, GREEN);

    // lower body
    DrawTextureEx(this->l_foot, {(float)this->x, (float)this->y}, 0.2f, 0.2f, GREEN);
    DrawTextureEx(this->l_leg, {(float)this->x, (float)this->y}, 0.2f, 0.2f, GREEN);
}

void Dynamic::Move(){
    if(IsKeyDown(KEY_UP)){
        this->y += 2.0f;
    }else if(IsKeyDown(KEY_DOWN)){
        this->y -= 2.0f;
    }else if(IsKeyDown(KEY_RIGHT)){
        this->x += 2.0f;
    }else if(IsKeyDown(KEY_LEFT)){
        this->x -= 2.0f;
    }
}