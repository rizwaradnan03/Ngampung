#include "engine/render.h"
#include "initial.h"

void Render::Init(int x, int y, bool anchor, std::string texture){
    this->x = x;
    this->y = y;
    this->anchor = anchor;

    Initial init;

    this->texture = *init.find_block_by_name(texture);
}

void Render::Display(){
    DrawTexture(this->texture, this->x, this->y, WHITE);
}