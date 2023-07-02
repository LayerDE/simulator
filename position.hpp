#pragma once
#include "position.h"

float correct_direction_recursive(float in);

extern const double CPP_M_PI;
class position{
    public:
        position();
        position(float hx,float hy,float hdirection);
        float direction;
        point pos;
        virtual void move(float move_lenght);
        void correct_direction();
        void move_straight(float lenght, float height);
};