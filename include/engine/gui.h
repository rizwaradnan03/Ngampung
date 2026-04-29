#include <engine/render.h>

#pragma once

class Gui: Render {
    public:
        void Display() override;
        void Init(int32_t x, int32_t y, int32_t w, int32_t h, Color color);
        void Delete() override;
        void Run() override;

        virtual int32_t get_x();
        virtual void set_x(int32_t x);

        virtual int32_t get_y();
        virtual void set_y(int32_t y);

        virtual int32_t get_w();
        virtual void set_w(int32_t w);

        virtual int32_t get_h();
        virtual void set_h(int32_t h);

        virtual Color get_color();
        virtual void set_color(Color color);

    private:
        int32_t x;
        int32_t y;
        int32_t w;
        int32_t h;

        Color color;
};