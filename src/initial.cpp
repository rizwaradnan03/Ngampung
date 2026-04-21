#include "initial.h"
#include "raylib.h"

Initial::Initial(){
    Image block_face = LoadImage("../image/block/knight.jpg");
    Texture block_face_t = LoadTextureFromImage(block_face);

    this->block.push_back(std::make_pair("block_face", block_face_t));
}

Texture* Initial::find_block_by_name(std::string name){
    for(int i = 0;i < this->block.size();i++){
        if(block[i].first == name){
            return &block[i].second;
        }
    }

    return nullptr;
}