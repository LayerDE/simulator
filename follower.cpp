#include "position.hpp"
#include "car.hpp"
#include "follower.hpp"
#include <cmath>

follower::follower(car* bbc, float len, float hbeta)
        : position(bbc->x,bbc->y,bbc->direction), last_car_pos(bbc->x,bbc->y,bbc->direction){

    lenght = len;
    connected_car = bbc;
    move_straight(-bbc->get_r2h(),0);
    direction+=hbeta;
    move_straight(-(lenght + connected_car->get_r2h()),0);
}


bool follower::check_connection(){
    return true;
}
void follower::set_angle(){

}

static inline float pow2(float x){
  return x*x;
}

void follower::move(){
    float _x = connected_car->x-last_car_pos.x;
    float _y = connected_car->y-last_car_pos.y;
    float _beta = beta(last_car_pos->direction)-(tan(_y/_x)-last_car_pos->direction)
    float _s = sqrt(pow2(connected_car->x-last_car_pos.x) + pow2(connected_car->y-last_car_pos.y));
    float h = sin(_beta)*_s;
    direction = atan(1)*2-_beta+acos((sin(_beta)-_s)/lenght)-connected_car->direction;
    x = connected_car->x;
    y = connected_car->y;
    move_straight(lenght,0);
    last_car_pos.x = connected_car->x;
    last_car_pos.y = connected_car->y;
    last_car_pos.direction = connected_car->direction;
}

float follower::beta(){
    return direction - connected_car->direction;
}

float follower::beta(float car_direction){
    return direction - connected_car->direction;
}


float follower::calc_alpha_const(float beta){
    float V_bw = connected_car->get_r2h()/tan(beta);
    return atan(connected_car->get_wb()/V_bw);
}

float follower::calc_beta_const(float alpha_steer){
    if(alpha_steer == 0.0)
        return 0.0;
    float V_bw = connected_car->get_wb()/tan(fabs(alpha_steer));
    return tan(connected_car->get_r2h()/V_bw);
    //float delta_2 = sin(hitch2axle/sqrt(pow2(V_bw)+pow2(car2hitch)));
    //return delta_1;
}
