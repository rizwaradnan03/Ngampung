#include <string>
#include <chrono>
#include <chrono>

#pragma once

namespace sys {
    void Log(bool type, const std::string& custom_message);
    std::chrono::time_point<std::chrono::high_resolution_clock> current_time();

    void fps_counter();
    extern int32_t frame_count;
    extern std::chrono::time_point<std::chrono::high_resolution_clock> run_time;
}