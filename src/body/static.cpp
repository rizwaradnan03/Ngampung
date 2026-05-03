#include <body/static.h>
#include <raylib.h>
#include <initial.h>
#include <iostream>
#include <namespace/audio.h>
#include <namespace/system.h>
#include <singleton/mouse.h>
#include <body/dynamic.h>

void Static::Init(int32_t x, int32_t y, int32_t w, int32_t h, int32_t health, bool anchor, bool is_can_collide, int32_t layer, std::vector<int32_t>* collide_masks, std::string texture){
    this->set_x(x);
    this->set_y(y);
    this->set_w(w);
    this->set_h(h);
    this->anchor = anchor;
    this->set_is_can_collide(is_can_collide);
    this->set_collide_masks(collide_masks);
    this->set_layer(layer);
    this->set_health(health);

    auto tex = G_initial->find_block_by_name(texture);
    if(tex == nullptr) {
        std::cout << "Texture Tidak Ditemukan!" << std::endl;
        return;
    }
    
    this->texture = *tex;
}

bool Static::get_is_free(){
    return this->is_free;
}

void Static::set_is_free(bool is_free){
    this->is_free = is_free;
}
std::chrono::time_point<std::chrono::high_resolution_clock>* Static::get_max_time_before_break(){
    return this->max_time_before_break;
}

void Static::set_max_time_before_break(std::chrono::time_point<std::chrono::high_resolution_clock>* max_time_before_break){
    this->max_time_before_break = max_time_before_break;
}

int32_t Static::get_x(){
    return this->x;
}

void Static::set_x(int32_t x){
    this->x = x;
}

int32_t Static::get_y(){
    return this->y;
}

void Static::set_y(int32_t y){
    this->y = y;
}

int32_t Static::get_w(){
    return this->w;
}

void Static::set_w(int32_t w){
    this->w = w;
}

int32_t Static::get_h(){
    return this->h;
}

void Static::set_h(int32_t h){
    this->h = h;
}

int32_t Static::get_health(){
    return this->health;
}

void Static::set_health(int32_t health){
    this->health = health;
}

int32_t Static::get_layer(){
    return this->layer;
}

void Static::set_layer(int32_t layer){
    this->layer = layer;
}

bool Static::get_is_can_collide(){
    return this->is_can_collide;
}

void Static::set_is_can_collide(bool is_can_collide){
    this->is_can_collide = is_can_collide;
}


std::vector<int32_t>* Static::get_collide_masks(){
    return this->collide_masks;
}

void Static::set_collide_masks(std::vector<int32_t>* collide_masks){
    this->collide_masks = collide_masks;
}

void Static::Run(std::string* action, const std::vector<Static*>& static_objects, const std::vector<Dynamic*>& dynamic_objects){
    this->physics(static_objects);
    this->action_check(action);
    this->Display();

    // delete checker
    this->mouse_checker();
    this->reset_max_time_checker();
    this->Delete();
}

void Static::physics(const std::vector<Static*>& static_objects){

}

void Static::Delete(){
    if(this->health <= 0){
        this->set_is_free(true);
    }
}

void Static::Display(){
    Rectangle source = {0, 0, (float)this->texture.width, (float)this->texture.height};
    Rectangle dest = {(float)this->get_x(), (float)this->get_y(), (float)this->get_w(), (float)this->get_h()};
    Vector2 origin = {0, 0};

    DrawTexturePro(this->texture, source, dest, origin, 0.0f, WHITE);
}

void Static::affect_by_action(std::string action){
    if(action == "ACT_HIT"){
        this->health -= 1;
    }
}

void Static::action_check(std::string* action){
    if(action != nullptr){
        this->affect_by_action(*action);
    }
}

void Static::reset_max_time_checker(){
    std::chrono::time_point<std::chrono::high_resolution_clock> current_time = sys::current_time();
    if(this->get_max_time_before_break() == nullptr){
        return;
    }

    if(current_time >= *this->get_max_time_before_break()){
        this->set_health(3);
        this->set_max_time_before_break(nullptr);
    }
}

void Static::mouse_checker(){
    if(G_SINGLETON_mouse->get_mouse().second.first == this->get_x() && G_SINGLETON_mouse->get_mouse().second.second == this->get_y()){
        if(*G_SINGLETON_mouse->get_mouse().first == "CLICK_LEFT"){
            std::chrono::time_point<std::chrono::high_resolution_clock> t = sys::current_time() + std::chrono::seconds(2);
            
            this->set_health(this->get_health() - 1);
            this->set_max_time_before_break(new std::chrono::time_point<std::chrono::high_resolution_clock>(t));
            
            if(this->get_health() > 0){
                Audio::play("punch");
            }else{
                Audio::play("break");
            }
        }        
    }
}

Static::~Static(){
    
}