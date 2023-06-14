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
    move_straight(-lenght,0);
}


bool follower::check_connection(){
    return true;
}
void follower::set_angle(){

}

static inline float pow2(float x){
  return x*x;
}

    //float h = sin(_beta_straight)*_s_straight;

void follower::move(){
    float _x = connected_car->x - last_car_pos.x;
    float _y = connected_car->y - last_car_pos.y;
    float _s_straight = sqrt(pow2(_x) + pow2(_y));
    float _beta_straight = direction - tan(_y/_x);
    float _s_half = cos(_beta_straight) * lenght;
    float direction_tmp;
    if(_s_half < _s_straight/2){
        direction_tmp = 0;
    }
    else if(_s_half > _s_straight/2){
        direction_tmp = CPP_M_PI / 2 - _beta_straight + acos((sin(_beta_straight) - _s_straight) / lenght);
    }
    else{ //_s_half == _s_straight/2
        direction_tmp = CPP_M_PI - _beta_straight;
    }
    x = connected_car->x;
    y = connected_car->y;
    direction = connected_car->direction;
    move_straight(-connected_car->get_r2h(),0);
    direction = direction_tmp + connected_car->direction;;
    correct_direction();
    move_straight(-lenght,0);
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
