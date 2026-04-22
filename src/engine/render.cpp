#include "engine/render.h"
#include "iostream"
#include "initial.h"

void Render::Init(int x, int y, bool anchor, std::string texture){
    this->x = x;
    this->y = y;
    this->anchor = anchor;

    auto tex = G_initial->find_block_by_name(texture);
    if(tex == nullptr) {
        std::cout << "Texture Tidak Ditemukan!" << std::endl;
        return;
    }

    this->texture = *tex;
}

void Render::Display(){
    // std::cout << "Texture ID: " << this->texture.id << std::endl;
    DrawTextureEx(this->texture, {(float)this->x, (float)this->y}, 0.2f, 0.2f, RED);
}