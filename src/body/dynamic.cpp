#include <body/dynamic.h>
#include <initial.h>
#include <namespace/system.h>
#include <iostream>
#include <engine/audio.h>
#include <namespace/physic.h>

void Dynamic::Init(int32_t x, int32_t y, int32_t w, int32_t h, int32_t health, bool anchor, bool is_can_collide, int32_t layer, std::vector<int32_t>* collide_masks, std::string texture){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->anchor = anchor;
    this->is_can_collide = is_can_collide;
    this->health = health;
    this->layer = layer;

    auto tex = G_initial->find_block_by_name(texture);
    if(tex == nullptr){
        System::Log(false, "Gagal Load Texture!");
        return;
    }

    this->m_body = *tex;
}

int32_t Dynamic::get_layer(){
    return this->layer;
}

void Dynamic::set_layer(int32_t layer){
    this->layer = layer;
}

int32_t Dynamic::get_x(){
    return this->x;
}

void Dynamic::set_x(int32_t x){
    this->x = x;
}

int32_t Dynamic::get_y(){
    return this->y;
}

void Dynamic::set_y(int32_t y){
    this->y = y;
}

int32_t Dynamic::get_w(){
    return this->w;
}

void Dynamic::set_w(int32_t w){
    this->w = w;
}

int32_t Dynamic::get_h(){
    return this->h;
}

void Dynamic::set_h(int32_t h){
    this->h = h;
}

bool Dynamic::get_is_can_collide(){
    return this->is_can_collide;
}

void Dynamic::set_is_can_collide(bool is_can_collide){
    this->is_can_collide = is_can_collide;
}

bool Dynamic::get_anchor(){
    return this->anchor;
}

void Dynamic::set_anchor(bool anchor){
    this->anchor = anchor;
}

void Dynamic::Run(const std::vector<Static*>& static_objects, const std::vector<Dynamic*>& dynamic_objects){
    this->physics(static_objects, dynamic_objects);
    this->Display();
}

void Dynamic::physics(const std::vector<Static*>& static_objects, const std::vector<Dynamic*>& dynamic_objects){
    this->physic_collide(static_objects, dynamic_objects);
    this->gravity(static_objects, dynamic_objects);
}

// check the collide
void Dynamic::physic_collide(const std::vector<Static*>& static_objects, const std::vector<Dynamic*>& dynamic_objects){
    if(this->get_is_can_collide() == true){
        for(int i = 0;i < static_objects.size() + dynamic_objects.size();i++){
            if(i < static_objects.size()){
                if(static_objects[i]->get_layer() == this->layer && static_objects[i]->get_is_can_collide() == true){
                    std::pair<bool, std::string*> check_collide = Physic::is_colliding(this, static_objects[i]);
                }
            }else{
                if(dynamic_objects[i - static_objects.size()]->get_layer() == this->layer && dynamic_objects[i - static_objects.size()]->get_is_can_collide() == true){
                    std::pair<bool, std::string*> check_collide = Physic::is_colliding(this, dynamic_objects[i - static_objects.size()]);
                }
            }
        }
    }
}

void Dynamic::gravity(const std::vector<Static*>& static_objects, const std::vector<Dynamic*>& dynamic_objects){
    if(this->get_anchor() == false){
        // gotta implement the gravity with checking if is there collide with any block
        this->y += 1.0f;
    }
}

void Dynamic::Display(){
    Rectangle source = {(float)this->x, (float)this->y, (float)this->m_body.width, (float)this->m_body.height};
    Rectangle dest = {(float)this->x, (float)this->y, 30.0f, 30.0f};
    Vector2 origin = {0, 0};

    DrawTexturePro(this->u_head, source, dest, origin, 0.0f, WHITE);
    DrawTexturePro(this->u_face, source, dest, origin, 0.0f, WHITE);
    DrawTexturePro(this->u_neck, source, dest, origin, 0.0f, WHITE);
    
    DrawTexturePro(this->m_body, source, dest, origin, 0.0f, WHITE);
    DrawTexturePro(this->m_l_hand, source, dest, origin, 0.0f, WHITE);
    DrawTexturePro(this->m_r_hand, source, dest, origin, 0.0f, WHITE);

    DrawTexturePro(this->l_foot, source, dest, origin, 0.0f, WHITE);
    DrawTexturePro(this->l_leg, source, dest, origin, 0.0f, WHITE);
}

void Dynamic::Movement(){
    if(IsKeyDown(KEY_RIGHT)){
        this->x += 1.0f;
    }else if(IsKeyDown(KEY_LEFT)){
        this->x -= 1.0f;
    }

    if(IsKeyPressed(KEY_SPACE)){
        Play("die");
        this->y -= 10.0f;
    }
}