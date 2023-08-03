#include <cmath>
#include "position.hpp"
const double CPP_M_PI = atan(1)*4.0;

void position::move_straight(double lenght, double height){
        pos.x += cos(direction)*lenght + sin(direction)*height;
        pos.y += sin(direction)*lenght + cos(direction)*height;
}

void position::move(double move_lenght){
    move_straight(move_lenght,0);   
}

position::position(double hx,double hy,double hdirection){
    pos.x = hx;
    pos.y = hy;
    direction = hdirection;
}

position::position(){
    pos.x = 0;
    pos.y = 0;
    direction = 0;
}

double correct_direction_recursive(double in){
    if(in > CPP_M_PI)
        return correct_direction_recursive(in - CPP_M_PI * 2);
    else if(in < -CPP_M_PI)
        return correct_direction_recursive(in + CPP_M_PI * 2);
    else
        return in;
}

void position::correct_direction(){
    direction = correct_direction_recursive(direction);
}
