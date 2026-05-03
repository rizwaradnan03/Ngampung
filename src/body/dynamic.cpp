#include <body/dynamic.h>
#include <initial.h>
#include <namespace/system.h>
#include <iostream>
#include <namespace/audio.h>
#include <namespace/physic.h>
#include <namespace/system.h>
#include <body/static.h>
#include <singleton/mouse.h>

void Dynamic::Init(int32_t x, int32_t y, int32_t w, int32_t h, int32_t health, bool anchor, bool is_can_collide, int32_t layer, std::vector<int32_t>* collide_masks, std::string texture){
    this->set_x(x);
    this->set_y(y);
    this->set_w(w);
    this->set_h(h);
    this->set_anchor(anchor);
    this->set_is_can_collide(is_can_collide);
    this->set_health(health);
    this->set_layer(layer);
    this->set_jump_amount(2);
    this->set_is_free(false);

    auto tex = G_initial->find_block_by_name(texture);
    if(tex == nullptr){
        sys::Log(false, "Gagal Load Texture!");
        return;
    }

    this->m_body = *tex;
}

void Dynamic::Delete(){
    // Audio::play()
    this->set_is_free(true);
}

int32_t Dynamic::get_layer(){
    return this->layer;
}

void Dynamic::set_layer(int32_t layer){
    this->layer = layer;
}

int32_t Dynamic::get_x(){
    return this->x;
}

void Dynamic::set_x(int32_t x){
    this->x = x;
}

int32_t Dynamic::get_y(){
    return this->y;
}

void Dynamic::set_y(int32_t y){
    this->y = y;
}

int32_t Dynamic::get_w(){
    return this->w;
}

void Dynamic::set_w(int32_t w){
    this->w = w;
}

int32_t Dynamic::get_h(){
    return this->h;
}

void Dynamic::set_h(int32_t h){
    this->h = h;
}

bool Dynamic::get_is_can_collide(){
    return this->is_can_collide;
}

void Dynamic::set_is_can_collide(bool is_can_collide){
    this->is_can_collide = is_can_collide;
}

bool Dynamic::get_anchor(){
    return this->anchor;
}

void Dynamic::set_anchor(bool anchor){
    this->anchor = anchor;
}

bool Dynamic::get_is_free(){
    return this->is_free;
}

void Dynamic::set_is_free(bool is_free){
    this->is_free = is_free;
}

std::pair<bool, bool> Dynamic::get_available_direction(){
    return this->available_direction;
}

void Dynamic::set_available_direction(std::pair<bool, bool> available_direction){
    this->available_direction = available_direction;
}

std::vector<Render*> Dynamic::get_inventory(){
    return this->inventory;
}

void Dynamic::set_inventory(std::vector<Render*> inventory){
    this->inventory = inventory;
}

std::string Dynamic::get_movement_action(){
    return this->movement_action;
}

void Dynamic::set_movement_action(std::string movement_action){
    this->movement_action = movement_action;
}

std::string Dynamic::get_movement_direction(){
    return this->movement_direction;
}

void Dynamic::set_movement_direction(std::string movement_direction){
    this->movement_direction = movement_direction;
}

std::string* Dynamic::get_mouse_action(){
    return this->mouse_action;
}

void Dynamic::set_mouse_action(std::string* mouse_action){
    this->mouse_action = mouse_action;
}

int32_t Dynamic::get_health(){
    return this->health;
}

void Dynamic::set_health(int32_t health){
    this->health = health;
}

int32_t Dynamic::get_jump_amount(){
    return this->jump_amount;
}

void Dynamic::set_jump_amount(int32_t jump_amount){
    this->jump_amount = jump_amount;
}

std::chrono::time_point<std::chrono::high_resolution_clock> Dynamic::get_start_jump(){
    return this->start_jump;
}

void Dynamic::set_start_jump(std::chrono::time_point<std::chrono::high_resolution_clock> start_jump){
    this->start_jump = start_jump;
}

void Dynamic::Run(std::string* action, const std::vector<Static*>& static_objects, const std::vector<Dynamic*>& dynamic_objects){
    this->mouse_movement(static_objects, dynamic_objects);
    this->physics(static_objects, dynamic_objects);
    this->Display();
}

void Dynamic::Movement(){
    std::pair<bool, bool> avail_x = this->get_available_direction();

    if(IsKeyDown(KEY_D) && avail_x.second == true){
        this->set_movement_direction("RIGHT");
        this->set_x(this->get_x() + 2.0f);
    }else if(IsKeyDown(KEY_A) && avail_x.first == true){
        this->set_movement_direction("LEFT");
        this->set_x(this->get_x() - 2.0f);
    }

    if(IsKeyPressed(KEY_SPACE) && this->get_movement_action() != "JUMP" && this->get_jump_amount() > 0){
        this->set_start_jump(sys::current_time());
        Audio::play("jump");
        this->set_movement_action("JUMP");

        this->set_jump_amount(this->get_jump_amount() - 1);
    }

    if(this->get_movement_action() == "JUMP"){
        auto current_time = sys::current_time();
        std::chrono::duration<float> differ = current_time - this->get_start_jump();

        if(differ.count() >= 0.3f){
            this->set_movement_action("STAY");
        }else if(differ.count() < 0.3f){
            this->set_y(this->get_y() - 7.0f);
        }
    }
}

void Dynamic::mouse_movement(const std::vector<Static*>& static_objects, const std::vector<Dynamic*>& dynamic_objects){
    int32_t max_x = 500;
    int32_t max_y = 410;
    Vector2 mouse_pos = GetMousePosition();

    std::string* action = nullptr;
    std::pair<int32_t, int32_t> pos = std::make_pair((int32_t)mouse_pos.x, (int32_t)mouse_pos.y);

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        action = new std::string("CLICK_LEFT");

        pos.first -= 420;
        pos.second -= 300;

        if(mouse_pos.x >= max_x - 200 && mouse_pos.x <= max_x && mouse_pos.y >= max_y - 200 && mouse_pos.y <= max_y){
            int32_t calc_x = (int32_t)pos.first % 30;
            int32_t calc_y = (int32_t)pos.second % 30;

            while(pos.first % 30 != 0){
                calc_x <= 15 ? pos.first-- : pos.first++;
            }

            while(pos.second % 30 != 0){
                calc_y <= 15 ? pos.second-- : pos.second++;
            }

            int32_t p_dpx = this->get_x();
            int32_t p_dpy = this->get_y();

            while(p_dpx % 30 != 0){
                p_dpx % 30 <= 15 ? p_dpx-- : p_dpx++;
            }

            while(p_dpy % 30 != 0){
                p_dpy % 30 <= 15 ? p_dpy-- : p_dpy++;
            }

            pos.first += p_dpx;
            pos.second += p_dpy;
            
        }
    }

    G_SINGLETON_mouse->set_mouse(std::make_pair(action, pos));
}

void Dynamic::physics(const std::vector<Static*>& static_objects, const std::vector<Dynamic*>& dynamic_objects){
    // this->box_collide_checker(static_objects, dynamic_objects);
}

void Dynamic::box_collide_checker(const std::vector<Static*>& static_objects, const std::vector<Dynamic*>& dynamic_objects){
    if(this->get_is_can_collide() == true && this->get_anchor() == false){
        S_Dynamic::Gravity d = {false, false, false, false};

        int32_t s_obj_z = static_objects.size();
        int32_t d_obj_z = dynamic_objects.size();
        for(int i = 0;i < s_obj_z + d_obj_z;i++){
            Render* obj;
            if(i < s_obj_z){
                obj = static_objects[i];
            }else{
                obj = dynamic_objects[i - s_obj_z];
            }

            if(obj->get_layer() == this->get_layer() && obj->get_is_can_collide() == true){
                std::pair<bool, std::string> cc = Physic::is_colliding(this, obj);
                if(cc.first == true){
                    if(cc.second == "BOTTOM"){
                        d.is_found_bottom = true;
                    }

                    if(cc.second == "TOP"){
                        d.is_found_top = true;
                    }

                    if(cc.second == "RIGHT"){
                        d.is_found_right = true;
                    }

                    if(cc.second == "LEFT"){
                        d.is_found_left = true;
                    }
                }
            }
        }

        if(d.is_found_bottom == false){
            this->set_y(this->get_y() + 3.0f);
        }else if(d.is_found_bottom == true){
            if(this->get_y() % 30 != 0){
                int32_t calc_bound = 30 * 0.25;
                int32_t ctb = this->get_y();
                while(ctb % 30 != 0){
                    ctb--;
                }

                if(this->get_y() >= calc_bound + ctb){
                    delete this;
                }

                int32_t calc = this->get_y();
                while(calc % 30 != 0){
                    calc--;
                }

                this->set_y(calc);
            }

            this->set_jump_amount(1);
        }

        if(d.is_found_left == true){
            if(this->get_x() % 30 != 0){
                int32_t calc = this->get_x();
                while(calc % 30 != 0){
                    calc++;
                }

                this->set_x(calc);
            }
        }

        if(d.is_found_right == true){
            int32_t calc = this->get_x();
            if(calc <= 0){
                calc *= -1;
            }

            if(calc % 30 != 0){
                if(this->get_x() <= 0){
                    calc = this->get_x();
                }

                while(true){
                    bool is_val = false;
                    
                    if(calc <= 0){
                        if((calc * -1) % 30 == 0){
                            is_val = true;
                        }
                    }else{
                        if(calc % 30 == 0){
                            is_val = true;
                        }
                    }

                    if(is_val == true){
                        break;
                    }

                    calc--;
                }

                this->set_x(calc);
            }
        }

        if(this->get_movement_action() == "JUMP"){
            if(d.is_found_top == true){
                if(this->get_y() % 30 != 0){
                    int32_t calc = this->get_y();
                    while(calc % 30 != 0){
                        calc++;
                    }
    
                    this->set_y(calc);
                }
            }
        }

        this->set_available_direction(std::make_pair(d.is_found_left == true ? false : true, d.is_found_right == true ? false : true));
    }
}

void Dynamic::gravity(const std::vector<Static*>& static_objects, const std::vector<Dynamic*>& dynamic_objects){
    if(this->get_anchor() == false){
        this->y += 1.0f;
    }
}

void Dynamic::Display(){
    Rectangle source = {0.0f, 0.0f, (float)this->m_body.width, (float)this->m_body.height};
    Rectangle dest = {(float)this->get_x(), (float)this->get_y(), (float)this->get_w(), (float)this->get_h()};
    Vector2 origin = {0, 0};

    DrawTexturePro(this->u_head, source, dest, origin, 0.0f, WHITE);
    DrawTexturePro(this->u_face, source, dest, origin, 0.0f, WHITE);
    DrawTexturePro(this->u_neck, source, dest, origin, 0.0f, WHITE);
    
    DrawTexturePro(this->m_body, source, dest, origin, 0.0f, WHITE);
    DrawTexturePro(this->m_l_hand, source, dest, origin, 0.0f, WHITE);
    DrawTexturePro(this->m_r_hand, source, dest, origin, 0.0f, WHITE);

    DrawTexturePro(this->l_foot, source, dest, origin, 0.0f, WHITE);
    DrawTexturePro(this->l_leg, source, dest, origin, 0.0f, WHITE);
}