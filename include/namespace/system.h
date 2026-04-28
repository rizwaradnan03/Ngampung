#include <string>
#include <chrono>

#pragma once

namespace System {
    void Log(bool type, const std::string& custom_message);
    std::chrono::time_point<std::chrono::high_resolution_clock> current_time();
}