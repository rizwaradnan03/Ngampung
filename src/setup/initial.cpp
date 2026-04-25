#include "initial.h"
#include "raylib.h"
#include "iostream"
#include "utility"

Initial* G_initial = nullptr;

void Initial::InitImage(){
    Image BLOCK_face = LoadImage("./assets/image/block/knight.jpg");
    if (BLOCK_face.data == nullptr) {
        std::cout << "GAGAL LOAD IMAGE!" << std::endl;
    }

    Texture BLOCK_face_t = LoadTextureFromImage(BLOCK_face);
    UnloadImage(BLOCK_face);

    this->block.push_back(std::make_pair("BLOCK_face", BLOCK_face_t));

}

void Initial::InitAudio(){
    Sound fx_die = LoadSound("./assets/audio/die.mp3");

    this->audio.push_back(std::make_pair("die", fx_die));
}

void Initial::InitGlobal(){
}

Initial::Initial(){
    this->InitImage();    
    this->InitAudio();    
    this->InitGlobal();    
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