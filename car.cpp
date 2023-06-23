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

position car::get_hitch(){
    position out;
    out.x = x;
    out.y = y;
    out.direction = direction;
    out.move_straight(-get_r2h(),0);
    return out;
}

void car::calc_curve(float lenght, float alpha_steer, float &x, float &y, float &angle)
{
    if(alpha_steer == 0.0f){
        x=lenght;
        y=0;
        angle = 0;
    }
    else{
        float r_bw = wheelbase / tan(fabs(alpha_steer));
        angle = lenght/r_bw; //todo looks toooo wrong
        x = sin(angle) * r_bw;
        y = (1 - cos(angle)) * r_bw * SIGN(alpha_steer);
    }
}
void car::move(float move_lenght){
    float x,y,a;
    calc_curve(move_lenght,alpha,x,y,a);
    move_straight(x,y);
    direction+=a;
    correct_direction();
}
