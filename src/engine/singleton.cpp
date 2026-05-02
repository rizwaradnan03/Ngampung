#include <singleton/mouse.h>

std::pair<std::string*, std::pair<int32_t, int32_t>> SINGLETON_Mouse::get_mouse(){
    return this->mouse;
}

void SINGLETON_Mouse::set_mouse(std::pair<std::string*, std::pair<int32_t, int32_t>> mouse){
    this->mouse = mouse;
}