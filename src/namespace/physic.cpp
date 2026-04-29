#include <namespace/physic.h>

namespace Physic{
    std::pair<bool, std::string> is_colliding(Render *me, Render *target){
        int32_t min_x_me = me->get_x() - (me->get_w() / 2);
        int32_t max_x_me = me->get_x() + (me->get_w() / 2);
        int32_t min_y_me = me->get_y() - (me->get_h() / 2);
        int32_t max_y_me = me->get_y() + (me->get_h() / 2);

        int32_t min_x_target = target->get_x() - (target->get_w() / 2);
        int32_t max_x_target = target->get_x() + (target->get_w() / 2);
        int32_t min_y_target = target->get_y() - (target->get_h() / 2);
        int32_t max_y_target = target->get_y() + (target->get_h() / 2);

        if (max_x_me < min_x_target || min_x_me > max_x_target ||
            max_y_me < min_y_target || min_y_me > max_y_target){
            return {false, ""};
        }

        int dx = me->get_x() - target->get_x();
        int dy = me->get_y() - target->get_y();

        if (abs(dx) > abs(dy)){
            return {true, dx > 0 ? "LEFT" : "RIGHT"};
        }else{
            return {true, dy > 0 ? "TOP" : "BOTTOM"};
        }
    }
}