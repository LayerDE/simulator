#include <cmath>
#include "car.hpp"

car::car(double wb, double rh, double hx, double hy, double hdirection, double halpha) : position(hx, hy,hdirection){
    wheelbase = wb;
    rear2hitch = rh;
    alpha = halpha;
}

double car::get_r2h(){
    return rear2hitch;
}

double car::get_wb(){
    return wheelbase;
}

car::~car(){}

point car::get_hitch(){ // needs testing
    position out;
    out.pos.x = pos.x;
    out.pos.y = pos.y;
    out.direction = direction;
    out.move_straight(-get_r2h(),0);
    point ret_val;
    ret_val.x = out.pos.x;
    ret_val.y = out.pos.y;
    return ret_val;
}

void car::calc_curve(double lenght, double alpha_steer, double &x, double &y, double &angle) // works for me
{
    if(alpha_steer == 0.0f){
        x=lenght;
        y=0;
        angle = 0;
    }
    else{
        double r_bw = wheelbase / tan(alpha_steer);
        angle = lenght/r_bw;
        x = sin(angle) * r_bw;
        y = (1 - cos(angle)) * r_bw;// * SIGN(alpha_steer);
    }
}

void car::move(double move_lenght){ // Works
    double x,y,a;
    calc_curve(move_lenght,alpha,x,y,a); //Works
    move_straight(x,y);
    direction+=a;
    correct_direction();
}
