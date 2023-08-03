#pragma once
#include "position.h"

double correct_direction_recursive(double in);

extern const double CPP_M_PI;
class position{
    public:
        position();
        position(double hx,double hy,double hdirection);
        double direction;
        point pos;
        virtual void move(double move_lenght);
        void correct_direction();
        void move_straight(double lenght, double height);
};