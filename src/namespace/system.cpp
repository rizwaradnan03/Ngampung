#include <namespace/system.h>
#include <iostream>
#include <raylib.h>

namespace sys {
    void Log(bool type, const std::string& custom_message = ""){
        std::string message;
    
        if(type == false){
            message = "Terjadi Kegagalan!";
        }else{
            message = "Berhasil";
        }
    
        if(custom_message.size() > 0){
            message = custom_message;
        }
    
        std::cout << "LOG (" << (type == true ? "Berhasil" : "Gagal") << ") " << message << std::endl;
    }

    std::chrono::time_point<std::chrono::high_resolution_clock> current_time(){
        auto time = std::chrono::high_resolution_clock::now();
        return time;
    }

    int32_t frame_count = 0;
    std::chrono::time_point<std::chrono::high_resolution_clock> run_time;
    void fps_counter(){
        auto current_time = std::chrono::high_resolution_clock::now();
        frame_count++;

        std::chrono::duration<float> differ = current_time - run_time;
        std::string strf = "Frame : " + std::to_string(frame_count);

        if(differ.count() >= 1.0f){
            float fps = static_cast<float>(frame_count) / differ.count();
            frame_count = 0;
            run_time = current_time;
        }

        DrawText(strf.c_str(), 0, 0, 20, RED);
    }
}