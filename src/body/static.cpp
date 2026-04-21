#include "body/static.h"
#include "raylib.h"
#include "initial.h"

Static::Static(int x, int y, std::string texture){
    this->x = x;
    this->y = y;

    Initial init;

    this->texture = *init.find_block_by_name(texture);
}

Static::~Static(){
    
}