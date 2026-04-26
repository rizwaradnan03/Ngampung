#include <body/static.h>
#include <raylib.h>
#include <initial.h>
#include <iostream>

void Static::Init(int32_t x, int32_t y, int32_t* health, bool anchor, bool is_can_collide, std::vector<int32_t>* collide_masks, std::string texture){
    this->x = x;
    this->y = y;
    this->anchor = anchor;
    this->is_can_collide = is_can_collide;
    this->collide_masks = collide_masks;

    if(health != nullptr){
        this->health = health;
    }

    auto tex = G_initial->find_block_by_name(texture);
    if(tex == nullptr) {
        std::cout << "Texture Tidak Ditemukan!" << std::endl;
        return;
    }
    
    this->texture = *tex;
}

int32_t Static::get_x(){
    return this->x;
}

void Static::set_x(int32_t x){
    this->x = x;
}

int32_t Static::get_y(){
    return this->y;
}

void Static::set_y(int32_t y){
    this->y = y;
}

void Static::Run(std::string *action){
    this->action_check(action);
    this->Display();

    // delete checker
    this->Delete();
}

void Static::Delete(){
    if(*this->health <= 0){
        delete this;
    }
}

void Static::Display(){
    Rectangle source = {0, 0, (float)this->texture.width, (float)this->texture.height};
    Rectangle dest = {(float)this->x, (float)this->y, 30.0f, 30.0f};
    Vector2 origin = {0, 0};

    DrawTexturePro(this->texture, source, dest, origin, 0.0f, WHITE);
}

void Static::affect_by_action(std::string action){
    if(action == "ACT_HIT"){
        if(this->health != nullptr){
            *this->health -= 1;
        }
    }
}

void Static::action_check(std::string* action){
    if(action != nullptr){
        this->affect_by_action(*action);
    }
}

Static::~Static(){
    
}