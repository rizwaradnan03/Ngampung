#include <nodes/gui/click.h>

void GUI_Click::Init(int32_t x, int32_t y, int32_t w, int32_t h, Color color){
    this->set_x(x);
    this->set_y(y);
    this->set_w(w);
    this->set_h(h);
    this->set_color(color);
}

void GUI_Click::Run(int32_t x, int32_t y, int32_t w, int32_t h){
    this->Display();
}

void GUI_Click::Display(){
    
}

void GUI_Click::Delete(){}

int32_t GUI_Click::get_x(){
    return this->x;
}

void GUI_Click::set_x(int32_t x){
    this->x = x;
}

int32_t GUI_Click::get_y(){
    return this->y;
}

void GUI_Click::set_y(int32_t y){
    this->y = y;
}

int32_t GUI_Click::get_w(){
    return this->w;
}

void GUI_Click::set_w(int32_t w){
    this->w = w;
}

int32_t GUI_Click::get_h(){
    return this->h;
}

void GUI_Click::set_h(int32_t h){
    this->h = h;
}

Color GUI_Click::get_color(){
    return this->color;
}

void GUI_Click::set_color(Color color){
    this->color = color;
}

void GUI_Click::click(){}