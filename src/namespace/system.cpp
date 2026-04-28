#include <namespace/system.h>
#include <iostream>

namespace System {
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
}
