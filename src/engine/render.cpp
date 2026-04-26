#include <engine/render.h>
#include <iostream>
#include <initial.h>

void Render::Init(int32_t x, int32_t y, int32_t* health, bool anchor, bool is_can_collide, int32_t layer, std::vector<int32_t>* collide_masks, std::string texture){
    this->x = x;
    this->y = y;
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

void Render::Display(){
    Rectangle source = {0, 0, (float)this->texture.width, (float)this->texture.height};
    Rectangle dest = {(float)this->x, (float)this->y, 30.0f, 30.0f};
    Vector2 origin = {0, 0};

    DrawTexturePro(this->texture, source, dest, origin, 0.0f, WHITE);
}

void Render::Delete(){}

void Render::Run(){}