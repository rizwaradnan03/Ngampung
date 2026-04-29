#include <engine/gui.h>

void Gui::Init(int32_t x, int32_t y, int32_t w, int32_t h, Color color){
    this->set_x(x);
    this->set_y(y);
    this->set_w(w);
    this->set_h(h);
    this->set_color(color);
}

void Gui::Delete(){
    delete this;
}

void Gui::Run(){
    this->Display();
}

void Gui::Display(){
    
}

int32_t Gui::get_x(){
    return this->x;
}

void Gui::set_x(int32_t x){
    this->x = x;
}

int32_t Gui::get_y(){
    return this->y;
}

void Gui::set_y(int32_t y){
    this->y = y;
}

int32_t Gui::get_w(){
    return this->w;
}

void Gui::set_w(int32_t w){
    this->w = w;
}

int32_t Gui::get_h(){
    return this->h;
}

void Gui::set_h(int32_t h){
    this->h = h;
}

Color Gui::get_color(){
    return this->color;
}

void Gui::set_color(Color color){
    this->color = color;
}