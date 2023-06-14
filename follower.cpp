#include "position.hpp"
#include "car.hpp"
#include "follower.hpp"
#include <cmath>

follower::follower(car* bbc, float len, float hbeta)
        : position(bbc->x,bbc->y,bbc->direction), last_hitch_pos(){

    lenght = len;
    connected_car = bbc;
    last_hitch_pos = connected_car->get_hitch();
    move_straight(-bbc->get_r2h(),0);
    direction += hbeta;
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
    position temp = connected_car->get_hitch();
    float _x = temp.x - last_hitch_pos.x;
    float _y = temp.y - last_hitch_pos.y;
    float _s_straight = sqrt(pow2(_x) + pow2(_y));
    float _beta_straight = direction - tan(_y/_x);
    float _s_half = cos(_beta_straight) * lenght;
    float direction_tmp;
    if(_s_half < _s_straight/2){ // schlechter ansatz
        if(_beta_straight < CPP_M_PI/2){
            float h = sin(_beta_straight)*lenght;
            float len = _s_straight -_s_half;
            direction_tmp = CPP_M_PI - atan(h/len);
        }
        else if(_beta_straight > CPP_M_PI/2){
            float _beta_straight_tmp = CPP_M_PI - _beta_straight;
            float len = cos(_beta_straight_tmp)*lenght + _s_straight;
            float h = sin(_beta_straight)*lenght;
            direction_tmp = atan(h/len);
        }
        else{
            direction_tmp = atan(lenght/_s_straight);
        }
    }
    else if(_s_half > _s_straight/2){
        float h = sin(_beta_straight) * _s_straight;
        direction_tmp = CPP_M_PI / 2 - _beta_straight + acos(h / lenght);
    }
    else{ //_s_half == _s_straight/2
        direction_tmp = CPP_M_PI - _beta_straight;
    }
    x = temp.x;
    y = temp.y;
    direction = temp.direction;
    direction = direction_tmp;
    correct_direction();
    move_straight(-lenght, 0);
    last_hitch_pos = temp;
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
