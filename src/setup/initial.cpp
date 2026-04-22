#include "initial.h"
#include "raylib.h"
#include "iostream"

Initial* G_initial = nullptr;

Initial::Initial(){
    Image block_face = LoadImage("./image/block/knight.jpg");
    if (block_face.data == nullptr) {
        std::cout << "GAGAL LOAD IMAGE!" << std::endl;
    }

    Texture block_face_t = LoadTextureFromImage(block_face);
    UnloadImage(block_face);

    this->block.push_back(std::make_pair("block_face", block_face_t));

}

Texture* Initial::find_block_by_name(std::string name){
    for(int i = 0;i < this->block.size();i++){
        if(this->block[i].first == name){
            return &this->block[i].second;
        }
    }

    return nullptr;
}