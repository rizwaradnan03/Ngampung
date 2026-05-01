#include <engine/render.h>
#include <iostream>
#include <initial.h>

void Render::Init(int32_t x, int32_t y, int32_t w, int32_t h, int32_t health, bool anchor, bool is_can_collide, int32_t layer, std::vector<int32_t>* collide_masks, std::string texture){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->anchor = anchor;
    this->is_can_collide = is_can_collide;
    this->collide_masks = collide_masks;
    this->layer = layer;

    auto tex = G_initial->find_block_by_name(texture);
    if(tex == nullptr) {
        std::cout << "Texture Tidak Ditemukan!" << std::endl;
        return;
    }

    this->texture = *tex;
}

int32_t Render::get_x(){
    return this->x;
}

void Render::set_x(int32_t x){
    this->x = x;
}

int32_t Render::get_y(){
    return this->y;
}

void Render::set_y(int32_t y){
    this->y = y;
}

int32_t Render::get_w(){
    return this->w;
}

void Render::set_w(int32_t w){
    this->w = w;
}

int32_t Render::get_h(){
    return this->h;
}

void Render::set_h(int32_t h){
    this->h = h;
}

int32_t Render::get_layer(){
    return this->layer;
}

void Render::set_layer(int32_t layer){
    this->layer = layer;
}

bool Render::get_is_can_collide(){
    return this->is_can_collide;
}

void Render::set_is_can_collide(bool is_can_collide){
    this->is_can_collide = is_can_collide;
}

bool Render::get_is_free(){
    return this->is_free;
}
void Render::set_is_free(bool is_free){
    this->is_free = is_free;
}

void Render::Display(){
    Rectangle source = {0, 0, (float)this->texture.width, (float)this->texture.height};
    Rectangle dest = {(float)this->x, (float)this->y, (float)this->w, (float)this->h};
    Vector2 origin = {0, 0};

    DrawTexturePro(this->texture, source, dest, origin, 0.0f, WHITE);
}

void Render::Delete(){}

void Render::Run(){}