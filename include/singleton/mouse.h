#include <utility>
#include <string>
#include <cstdint>

#pragma once

class SINGLETON_Mouse {
    public:
        std::pair<std::string*, std::pair<int32_t, int32_t>> get_mouse();
        void set_mouse(std::pair<std::string*, std::pair<int32_t, int32_t>> mouse);

    private:
        std::pair<std::string*, std::pair<int32_t, int32_t>> mouse;  
};

extern SINGLETON_Mouse* G_SINGLETON_Mouse;