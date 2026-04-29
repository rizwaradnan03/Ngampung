#include <initial.h>
#include <raylib.h>
#include <iostream>
#include <utility>

Initial* G_initial = nullptr;

void Initial::InitImage(){
    Image BLOCK_face = LoadImage("./assets/image/block/knight.jpg");
    if (BLOCK_face.data == nullptr) {
        std::cout << "GAGAL LOAD IMAGE!" << std::endl;
    }

    Image BLOCK_dirt = LoadImage("./assets/image/block/dirt.png");
    if (BLOCK_dirt.data == nullptr) {
        std::cout << "GAGAL LOAD IMAGE!" << std::endl;
    }

    Image BLOCK_player = LoadImage("./assets/image/accessories/player.png");
    if (BLOCK_player.data == nullptr) {
        std::cout << "GAGAL LOAD IMAGE!" << std::endl;
    }

    Texture BLOCK_face_t = LoadTextureFromImage(BLOCK_face);
    UnloadImage(BLOCK_face);

    Texture BLOCK_dirt_t = LoadTextureFromImage(BLOCK_dirt);
    UnloadImage(BLOCK_dirt);

    Texture BLOCK_player_t = LoadTextureFromImage(BLOCK_player);
    UnloadImage(BLOCK_player);

    this->block.push_back(std::make_pair("BLOCK_face", BLOCK_face_t));
    this->block.push_back(std::make_pair("BLOCK_dirt", BLOCK_dirt_t));
    this->block.push_back(std::make_pair("BLOCK_player", BLOCK_player_t));

}

void Initial::InitAudio(){
    Sound fx_die = LoadSound("./assets/audio/die.mp3");

    this->audio.push_back(std::make_pair("die", fx_die));

    Sound fx_jump = LoadSound("./assets/audio/jump.mp3");

    this->audio.push_back(std::make_pair("jump", fx_jump));
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