#include "initial.h"
#include "raylib.h"
#include "iostream"
#include "utility"

Initial* G_initial = nullptr;

void Initial::InitImage(){
    Image block_face = LoadImage("./assets/image/block/knight.jpg");
    if (block_face.data == nullptr) {
        std::cout << "GAGAL LOAD IMAGE!" << std::endl;
    }

    Texture block_face_t = LoadTextureFromImage(block_face);
    UnloadImage(block_face);

    this->block.push_back(std::make_pair("block_face", block_face_t));

}

void Initial::InitAudio(){
    Sound fx_die = LoadSound("./assets/audio/die.mp3");

    this->audio.push_back(std::make_pair("die", fx_die));
}

Initial::Initial(){
    this->InitImage();    
    this->InitAudio();    
}

Texture* Initial::find_block_by_name(std::string name){
    for(int i = 0;i < this->block.size();i++){
        if(this->block[i].first == name){
            return &this->block[i].second;
        }
    }

    return nullptr;
}

Sound* Initial::find_audio_by_name(std::string name){
    for(int i = 0;i < this->audio.size();i++){
        if(this->audio[i].first == name){
            return &this->audio[i].second;
        }
    }

    return nullptr;
}