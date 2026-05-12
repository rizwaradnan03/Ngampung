#include <sources/gui/item_inventory_click.h>
#include <singleton/mouse.h>
#include <iostream>

void GUI_Item_Inventory_Click::Init(int32_t x, int32_t y, int32_t w, int32_t h, Color color){
    this->set_x(x);
    this->set_y(y);
    this->set_w(w);
    this->set_h(h);
    this->set_color(color);
}

void GUI_Item_Inventory_Click::Delete(){
    delete this;
}

void GUI_Item_Inventory_Click::Run(){
    this->Display();
    this->click();
}

void GUI_Item_Inventory_Click::Display(){
    DrawRectangle(this->get_x(), this->get_y(), this->get_w(), this->get_h(), this->get_color());
}

int32_t GUI_Item_Inventory_Click::get_x(){
    return this->x;
}

void GUI_Item_Inventory_Click::set_x(int32_t x){
    this->x = x;
}

int32_t GUI_Item_Inventory_Click::get_y(){
    return this->y;
}

void GUI_Item_Inventory_Click::set_y(int32_t y){
    this->y = y;
}

int32_t GUI_Item_Inventory_Click::get_w(){
    return this->w;
}

void GUI_Item_Inventory_Click::set_w(int32_t w){
    this->w = w;
}

int32_t GUI_Item_Inventory_Click::get_h(){
    return this->h;
}

void GUI_Item_Inventory_Click::set_h(int32_t h){
    this->h = h;
}

Color GUI_Item_Inventory_Click::get_color(){
    return this->color;
}

void GUI_Item_Inventory_Click::set_color(Color color){
    this->color = color;
}

// action & i got so much bug on here
void GUI_Item_Inventory_Click::click(){
    std::pair<std::string*, std::pair<int32_t, int32_t>> mouse = G_SINGLETON_mouse->get_mouse();

    int32_t left = this->get_x();
    int32_t right = this->get_x() + this->get_w();
    int32_t top = this->get_y();
    int32_t bottom = this->get_y() + this->get_h();
    
    if(mouse.second.first >= left && mouse.second.first <= right && mouse.second.second >= top && mouse.second.second <= bottom){

    }

}