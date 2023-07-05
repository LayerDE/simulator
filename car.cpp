#include <cmath>
#include "car.hpp"

car::car(float wb, float rh, float hx, float hy, float hdirection, float halpha) : position(hx, hy,hdirection){
    wheelbase = wb;
    rear2hitch = rh;
    alpha = halpha;
}

float car::get_r2h(){
    return rear2hitch;
}

float car::get_wb(){
    return wheelbase;
}

car::~car(){}

point car::get_hitch(){ // needs testing
    position out;
    out.pos.x = pos.x;
    out.pos.y = pos.y;
    out.direction = direction;
    out.move_straight(-get_r2h(),0);
    return {.x = out.pos.x, .y = out.pos.y};
}

void car::calc_curve(float lenght, float alpha_steer, float &x, float &y, float &angle) // works for me
{
    if(alpha_steer == 0.0f){
        x=lenght;
        y=0;
        angle = 0;
    }
    else{
        float r_bw = wheelbase / tan(alpha_steer);
        angle = lenght/r_bw;
        x = sin(angle) * r_bw;
        y = (1 - cos(angle)) * r_bw;// * SIGN(alpha_steer);
    }
}

void car::move(float move_lenght){ // Works
    float x,y,a;
    calc_curve(move_lenght,alpha,x,y,a); //Works
    move_straight(x,y);
    direction+=a;
    correct_direction();
}
