#include <sources/gui/inventory.h>
#include <sources/gui/item_inventory_click.h>
#include <iostream>

void GUI_Inventory::Init(int32_t x, int32_t y, int32_t w, int32_t h, Color color){
    this->set_x(x);
    this->set_y(y);
    this->set_w(w);
    this->set_h(h);
    this->set_color(color);

    std::vector<Gui*> chd;

    Gui* clicked_stuff = new GUI_Item_Inventory_Click();
    clicked_stuff->Init(this->get_x() + 30, this->get_y(), 60, 60, RED);
    chd.push_back(clicked_stuff);

    this->set_children(chd);
}

void GUI_Inventory::Delete(){
    delete this;
}

void GUI_Inventory::Run(){
    this->Display();

    std::vector<Gui*> chd = this->get_children();
    for(int i = 0;i < chd.size();i++){
        chd[i]->Run();
    }
}

void GUI_Inventory::Display(){
    DrawRectangle(this->get_x(), this->get_y(), this->get_w(), this->get_h(), Fade(this->get_color(), 0.5F));
}

int32_t GUI_Inventory::get_x(){
    return this->x;
}

void GUI_Inventory::set_x(int32_t x){
    this->x = x;
}

int32_t GUI_Inventory::get_y(){
    return this->y;
}

void GUI_Inventory::set_y(int32_t y){
    this->y = y;
}

int32_t GUI_Inventory::get_w(){
    return this->w;
}

void GUI_Inventory::set_w(int32_t w){
    this->w = w;
}

int32_t GUI_Inventory::get_h(){
    return this->h;
}

void GUI_Inventory::set_h(int32_t h){
    this->h = h;
}

std::vector<Gui*> GUI_Inventory::get_children(){
    return this->children;
}

void GUI_Inventory::set_children(std::vector<Gui*> children){
    this->children = children;
}

Color GUI_Inventory::get_color(){
    return this->color;
}

void GUI_Inventory::set_color(Color color){
    this->color = color;
}