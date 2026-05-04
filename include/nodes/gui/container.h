#include <engine/gui.h>
#include <cstdint>
#include <raylib.h>

#pragma once

class GUI_Container: Gui{
    public:
        void Display() override;
        void Init(int32_t x, int32_t y, int32_t w, int32_t h, Color color);
        void Delete() override;
        void Run() override;

        int32_t get_x() override;
        void set_x(int32_t x) override;

        int32_t get_y() override;
        void set_y(int32_t y) override;

        int32_t get_w() override;
        void set_w(int32_t w) override;

        int32_t get_h() override;
        void set_h(int32_t h) override;

        Color get_color() override;
        void set_color(Color color) override;

    private:
        int32_t x;
        int32_t y;
        int32_t w;
        int32_t h;

        Color color;
};