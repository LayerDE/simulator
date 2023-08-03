#pragma once
#include "position.hpp"

class car : public position{
    private:
        double wheelbase;
        double rear2hitch;
    public:
        point get_hitch();
        double get_wb();
        double get_r2h();
        car(double wb, double rh, double hx, double hy, double hdirection, double halpha);
        virtual ~car();
        double alpha;
        void calc_curve(double lenght, double alpha_steer, double &x, double &y, double &angle);
        void move(double move_lenght);
};