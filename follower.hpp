#pragma once
#include "car.hpp"
#include "position.hpp"

class follower : public position{
    private:
        car* connected_car;
        float lenght;
        float beta();
        float beta(float car_direction);
        position last_hitch_pos;
        float calc_alpha_const(float beta);
        float calc_beta_const(float alpha_steer);
    public:
        float angle;
//        follower(float len, float hx, float hy, car* bbc);
        follower(car* bbc, float len, float hbeta);
        bool check_connection();
        void set_angle();
        void move();
};