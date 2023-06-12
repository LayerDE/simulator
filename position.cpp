#include <cmath>
#include "position.hpp"


void position::move_straight(float lenght, float height){
        x += cos(direction)*lenght;
        y += sin(direction)*lenght;
        x += sin(direction)*height;
        y += cos(direction)*height;
}

void position::move(float move_lenght){
    move_straight(move_lenght,0);   
}

position::position(float hx,float hy,float hdirection){
    x = hx;
    y = hy;
    direction = hdirection;
}

position::position(){
    x = 0;
    y = 0;
    direction = 0;
}
const static double CPP_M_PI = atan(1)*4.0;
void position::correct_direction(){
    while(direction > CPP_M_PI)
        direction -= CPP_M_PI * 2;
    while(direction < -CPP_M_PI)
        direction += CPP_M_PI * 2;
}