#include <sources/objects/player.h>
#include <initial.h>
#include <namespace/system.h>
#include <namespace/audio.h>
#include <namespace/physic.h>
#include <namespace/system.h>
#include <nodes/body/static.h>
#include <singleton/mouse.h>

void Player::Init(int32_t x, int32_t y, int32_t w, int32_t h, int32_t health, bool anchor, bool is_can_collide, int32_t layer, std::vector<int32_t>* collide_masks, std::string texture){
    this->set_x(x);
    this->set_y(y);
    this->set_w(w);
    this->set_h(h);
    this->set_anchor(anchor);
    this->set_is_can_collide(is_can_collide);
    this->set_health(health);
    this->set_layer(layer);
    this->set_collide_masks(collide_masks);
    this->set_jump_amount(2);
    this->set_is_free(false);

    auto tex = G_initial->find_block_by_name(texture);
    if(tex == nullptr){
        sys::Log(false, "Gagal Load Texture!");
        return;
    }

    this->m_body = *tex;

    // initialize some gui
    GUI_Inventory* invent = new GUI_Inventory();
    invent->Init(300, 540, 240, 60, GREEN);

    this->set_inventory(invent);
}

void Player::Delete(){
    // Audio::play()
    this->set_is_free(true);
}

int32_t Player::get_layer(){
    return this->layer;
}

void Player::set_layer(int32_t layer){
    this->layer = layer;
}

std::vector<int32_t>* Player::get_collide_masks(){
    return this->collide_masks;
}

void Player::set_collide_masks(std::vector<int32_t>* collide_masks){
    this->collide_masks = collide_masks;
}

int32_t Player::get_x(){
    return this->x;
}

void Player::set_x(int32_t x){
    this->x = x;
}

int32_t Player::get_y(){
    return this->y;
}

void Player::set_y(int32_t y){
    this->y = y;
}

int32_t Player::get_w(){
    return this->w;
}

void Player::set_w(int32_t w){
    this->w = w;
}

int32_t Player::get_h(){
    return this->h;
}

void Player::set_h(int32_t h){
    this->h = h;
}

bool Player::get_is_can_collide(){
    return this->is_can_collide;
}

void Player::set_is_can_collide(bool is_can_collide){
    this->is_can_collide = is_can_collide;
}

bool Player::get_anchor(){
    return this->anchor;
}

void Player::set_anchor(bool anchor){
    this->anchor = anchor;
}

bool Player::get_is_free(){
    return this->is_free;
}

void Player::set_is_free(bool is_free){
    this->is_free = is_free;
}

std::pair<bool, bool> Player::get_available_direction(){
    return this->available_direction;
}

void Player::set_available_direction(std::pair<bool, bool> available_direction){
    this->available_direction = available_direction;
}

GUI_Inventory* Player::get_inventory(){
    return this->inventory;
}

void Player::set_inventory(GUI_Inventory* inventory){
    this->inventory = inventory;
}

Render* Player::get_selected_item(){
    return this->selected_item;
}

void Player::set_selected_item(Render* selected_item){
    this->selected_item = selected_item;
}

std::string Player::get_movement_action(){
    return this->movement_action;
}

void Player::set_movement_action(std::string movement_action){
    this->movement_action = movement_action;
}

std::string Player::get_movement_direction(){
    return this->movement_direction;
}

void Player::set_movement_direction(std::string movement_direction){
    this->movement_direction = movement_direction;
}

std::string* Player::get_mouse_action(){
    return this->mouse_action;
}

void Player::set_mouse_action(std::string* mouse_action){
    this->mouse_action = mouse_action;
}

int32_t Player::get_health(){
    return this->health;
}

void Player::set_health(int32_t health){
    this->health = health;
}

int32_t Player::get_oxygen_level(){
    return this->oxygen_level;
}

void Player::set_oxygen_level(int32_t oxygen_level){
    this->oxygen_level = oxygen_level;
}

std::string Player::get_state(){
    return this->state;
}

void Player::set_state(std::string state){
    this->state = state;
}

std::chrono::time_point<std::chrono::high_resolution_clock>* Player::get_dive_time(){
    return this->dive_time;
}

void Player::set_dive_time(std::chrono::time_point<std::chrono::high_resolution_clock>* dive_time){
    this->dive_time = dive_time;
}

int32_t Player::get_jump_amount(){
    return this->jump_amount;
}

void Player::set_jump_amount(int32_t jump_amount){
    this->jump_amount = jump_amount;
}

std::chrono::time_point<std::chrono::high_resolution_clock> Player::get_start_jump(){
    return this->start_jump;
}

void Player::set_start_jump(std::chrono::time_point<std::chrono::high_resolution_clock> start_jump){
    this->start_jump = start_jump;
}

void Player::Run(std::string* action, const std::vector<Static*>& static_objects, const std::vector<Dynamic*>& dynamic_objects){
    this->reset_oxygen_level_checker();
    this->mouse_movement(static_objects, dynamic_objects);
    this->physics(static_objects, dynamic_objects);
    
    this->Display();
}

void Player::fixed_on_screen_run(){
    this->get_inventory()->Run([this](Render* r) {
        this->set_selected_item(r);
    });
}

void Player::Movement(){
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

void Player::mouse_movement(const std::vector<Static*>& static_objects, const std::vector<Dynamic*>& dynamic_objects){
    int32_t max_x = 500;
    int32_t max_y = 410;
    Vector2 mouse_pos = GetMousePosition();

    std::string* action = nullptr;
    std::pair<int32_t, int32_t> pos = std::make_pair((int32_t)mouse_pos.x, (int32_t)mouse_pos.y);

    pos.first -= 420;
    pos.second -= 300;

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        action = new std::string("CLICK_LEFT");

        if(mouse_pos.x >= max_x - 200 && mouse_pos.x <= max_x && mouse_pos.y >= max_y - 200 && mouse_pos.y <= max_y){
            int32_t calc_dir_x = (int32_t)pos.first % 30;
            int32_t calc_dir_y = (int32_t)pos.second % 30;
            
            while(pos.first % 30 != 0){
                calc_dir_x < 15 ? pos.first-- : pos.first++;
            }

            while(pos.second % 30 != 0){
                calc_dir_y < 15 ? pos.second-- : pos.second++;
            }
        }

    }
    
    int32_t p_x = this->get_x();
    int32_t p_y = this->get_y();

    int32_t p_dir_x = p_x % 30;
    int32_t p_dir_y = p_y % 30;

    while(p_x % 30 != 0){
        p_dir_x < 15 ? p_x-- : p_x++;
    }

    while(p_y % 30 != 0){
        p_dir_y < 15 ? p_y-- : p_y++;
    }

    pos.first += p_x;
    pos.second += p_y;

    G_SINGLETON_mouse->set_mouse(std::make_pair(action, pos));
}

void Player::physics(const std::vector<Static*>& static_objects, const std::vector<Dynamic*>& dynamic_objects){
    // this->box_collide_checker(static_objects, dynamic_objects);
}

void Player::box_collide_checker(const std::vector<Static*>& static_objects, const std::vector<Dynamic*>& dynamic_objects){
    if(this->get_is_can_collide() == true && this->get_anchor() == false){
        std::vector<int32_t>* masks = this->get_collide_masks();
        S_Dynamic::Gravity d = {false, false, false, false};

        int32_t s_obj_z = static_objects.size();
        int32_t d_obj_z = dynamic_objects.size();
        for(int i = 0;i < s_obj_z + d_obj_z;i++){
            Body* obj;
            if(i < s_obj_z){
                obj = static_objects[i];
            }else{
                obj = dynamic_objects[i - s_obj_z];
            }

            std::pair<bool, std::string> cc = Physic::is_colliding(this, obj);
            if(cc.first == true){
                bool is_sam_col = false;

                if(masks == nullptr){
                    return;
                }
        
                for(int j = 0;j < masks->size();j++){
                    if(obj->get_layer() == (*masks)[j]){
                        is_sam_col = true;
                        break;
                    }
                }

                // if collide is true so we're checking if it has the same value for layer on collide masks
                if(is_sam_col == true){
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

                    // to check if that is a water
                    if(obj->get_type() == "WATER" && this->get_dive_time() == nullptr){
                        auto current_time = new std::chrono::high_resolution_clock::time_point(
                            std::chrono::high_resolution_clock::now()
                        );
    
                        this->set_dive_time(current_time);
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

void Player::gravity(const std::vector<Static*>& static_objects, const std::vector<Dynamic*>& dynamic_objects){
    if(this->get_anchor() == false){
        this->y += 1.0f;
    }
}

void Player::reset_oxygen_level_checker(){
    if(this->get_state() == "WATER"){
        auto current_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> differ = current_time - *this->get_dive_time();

        if((int)differ.count() % 2 == 0){
            this->set_oxygen_level(this->get_oxygen_level() - 1);
            this->set_dive_time(new std::chrono::high_resolution_clock::time_point(current_time));

            if(this->get_oxygen_level() <= 0){
                this->Delete();
            }
        }
    }else{
        this->set_dive_time(nullptr);
    }
}

void Player::Display(){
    Rectangle source = {0.0f, 0.0f, (float)this->m_body.width, (float)this->m_body.height};
    Rectangle dest = {(float)this->get_x(), (float)this->get_y(), (float)this->get_w(), (float)this->get_h()};
    Vector2 origin = {0, 0};

    if(this->get_movement_direction() == "LEFT"){
        source.width = -this->m_body.width;
    }else if(this->get_movement_direction() == "RIGHT"){
        source.width = this->m_body.width;
    }

    DrawTexturePro(this->u_head, source, dest, origin, 0.0f, WHITE);
    DrawTexturePro(this->u_face, source, dest, origin, 0.0f, WHITE);
    DrawTexturePro(this->u_neck, source, dest, origin, 0.0f, WHITE);
    
    DrawTexturePro(this->m_body, source, dest, origin, 0.0f, WHITE);
    DrawTexturePro(this->m_l_hand, source, dest, origin, 0.0f, WHITE);
    DrawTexturePro(this->m_r_hand, source, dest, origin, 0.0f, WHITE);

    DrawTexturePro(this->l_foot, source, dest, origin, 0.0f, WHITE);
    DrawTexturePro(this->l_leg, source, dest, origin, 0.0f, WHITE);
}