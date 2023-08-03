#pragma once
#include "car.hpp"
#include "position.hpp"

class follower : public position{
    private:
        car* connected_car;
        double lenght;
        double beta(double car_direction);
        point last_hitch_pos;
    public:
        double angle;
        follower(car* bbc, double len, double hbeta);
        virtual  ~follower();
        void set_to_car(double hbeta);
        double beta();
        void move();
};