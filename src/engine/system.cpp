#include <engine/system.h>
#include <engine/render_type/world.h>

System* G_System = nullptr;

void System::set_render_type(std::pair<std::string, std::string> render){
    this->render = render;

    if(render.first == "GUI"){

    }else if(render.first == "WORLD"){
        G_RENDER_TYPE_world->Set(render.second);
    }

}

std::pair<std::string, std::string> System::get_render_type(){
    return this->render;
}