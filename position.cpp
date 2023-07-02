#include <cmath>
#include "position.hpp"
const double CPP_M_PI = atan(1)*4.0;

void position::move_straight(float lenght, float height){
        pos.x += cos(direction)*lenght + sin(direction)*height;
        pos.y += sin(direction)*lenght + cos(direction)*height;
}

void position::move(float move_lenght){
    move_straight(move_lenght,0);   
}

position::position(float hx,float hy,float hdirection){
    pos.x = hx;
    pos.y = hy;
    direction = hdirection;
}

position::position(){
    pos.x = 0;
    pos.y = 0;
    direction = 0;
}

float correct_direction_recursive(float in){
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
