#include <nodes/gui/container.h>

void GUI_Container::Init(int32_t x, int32_t y, int32_t w, int32_t h, Color color){
    this->set_x(x);
    this->set_y(y);
    this->set_w(w);
    this->set_h(h);
    this->set_color(color);
}

void GUI_Container::Delete(){
    delete this;
}

void GUI_Container::Run(){
    this->Display();
}

void GUI_Container::Display(){
    
}

int32_t GUI_Container::get_x(){
    return this->x;
}

void GUI_Container::set_x(int32_t x){
    this->x = x;
}

int32_t GUI_Container::get_y(){
    return this->y;
}

void GUI_Container::set_y(int32_t y){
    this->y = y;
}

int32_t GUI_Container::get_w(){
    return this->w;
}

void GUI_Container::set_w(int32_t w){
    this->w = w;
}

int32_t GUI_Container::get_h(){
    return this->h;
}

void GUI_Container::set_h(int32_t h){
    this->h = h;
}

Color GUI_Container::get_color(){
    return this->color;
}

void GUI_Container::set_color(Color color){
    this->color = color;
}