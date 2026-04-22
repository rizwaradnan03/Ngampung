#include "body/static.h"
#include "raylib.h"
#include "initial.h"
#include "iostream"

void Static::Init(int x, int y, bool anchor, std::string texture){
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

void Static::Display(){
    DrawTexture(this->texture, this->x, this->y, WHITE);
}

Static::~Static(){
    
}