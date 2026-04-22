#include "raylib.h"
#include "vector"
#include "string"

#pragma once

class Initial{
    public:
        Initial();
        void InitImage();
        void InitAudio();
        Texture* find_block_by_name(std::string name);
        Sound* find_audio_by_name(std::string name);

        std::vector<std::pair<std::string, Texture>> block;
        std::vector<std::pair<std::string, Sound>> audio;
};

extern Initial* G_initial;