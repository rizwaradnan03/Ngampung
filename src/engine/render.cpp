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
    Rectangle source = {0, 0, (float)this->texture.width, (float)this->texture.height};
    Rectangle dest = {(float)this->x, (float)this->y, 30.0f, 30.0f};
    Vector2 origin = {0, 0};

    DrawTexturePro(this->texture, source, dest, origin, 0.0f, WHITE);
}