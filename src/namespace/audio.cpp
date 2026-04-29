#include <namespace/audio.h>
#include <initial.h>
#include <iostream>

namespace Audio {
    void play(const std::string& name){
        auto aud = G_initial->find_audio_by_name(name);
        if(aud == nullptr){
            std::cout << "Suara Tidak Bisa Diputar!" << std::endl;
            return;
        }
    
        PlaySound(*aud);
    }
}
