#include <body/static.h>
#include <raylib.h>
#include <initial.h>
#include <iostream>

void Static::Init(int32_t x, int32_t y, int32_t health, bool anchor, bool is_can_collide, int32_t layer, std::vector<int32_t>* collide_masks, std::string texture){
    this->x = x;
    this->y = y;
    this->anchor = anchor;
    this->is_can_collide = is_can_collide;
    this->collide_masks = collide_masks;
    this->layer = layer;
    this->health = health;

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

int32_t Static::get_layer(){
    return this->layer;
}

void Static::set_layer(int32_t layer){
    this->layer = layer;
}

bool Static::get_is_can_collide(){
    return this->is_can_collide;
}

void Static::set_is_can_collide(bool is_can_collide){
    this->is_can_collide = is_can_collide;
}


std::vector<int32_t>* Static::get_collide_masks(){
    return this->collide_masks;
}

void Static::set_collide_masks(std::vector<int32_t>* collide_masks){
    this->collide_masks = collide_masks;
}

void Static::Run(std::string *action, const std::vector<Static*>& static_objects){
    this->physics(static_objects);
    this->action_check(action);
    this->Display();

    // delete checker
    this->Delete();
}

// we do need to implement stuff here
void Static::physics(const std::vector<Static*>& static_objects){

}

void Static::Delete(){
    if(this->health <= 0){
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
        this->health -= 1;
    }
}

void Static::action_check(std::string* action){
    if(action != nullptr){
        this->affect_by_action(*action);
    }
}

Static::~Static(){
    
}