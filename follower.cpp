#include "position.hpp"
#include "car.hpp"
#include "follower.hpp"
#include <cmath>
#include "sim_config.h"
#ifdef DEBUG
    #include <iostream>
    #define DEBUG_TAG "follower.cpp: "
    #define debug_out(x) std::cout << DEBUG_TAG << x << std::endl
    float rad2deg(float in);
#endif
follower::follower(car* bbc, float len, float hbeta) // hbeta is relative
        : position(), last_hitch_pos(){
    lenght = len;
    connected_car = bbc;
    last_hitch_pos = connected_car->get_hitch();
    x = last_hitch_pos.x;
    y = last_hitch_pos.y;
    direction += hbeta; // add angle
    move_straight(-lenght,0); // set trailer to position
}

static inline float pow2(float x){
  return x*x;
}

    //float h = sin(_beta_straight)*_s_straight;

static inline float get_direction(float x, float y){ // outputs trash
    if(x < 0.0)
        if(y == 0.0)
            return CPP_M_PI; //180° x negative, y = 0
        else
            return atan(y/x) + CPP_M_PI * SIGN(y);
    else if(x > 0.0)
        if(y == 0.0)
            return 0; // 0° x positive y = 0
        else
            return atan(y/x); // ]-90:90[° x positive, y != 0
    else // x == 0
        return CPP_M_PI/2 * SIGN(y);
}
#ifdef OLD_MOVE
void follower::move(){
    position temp = connected_car->get_hitch();
    float _x = temp.x - last_hitch_pos.x;
    float _y = temp.y - last_hitch_pos.y;
    float _s_straight = sqrt(pow2(_x) + pow2(_y));
    if(_s_straight == 0.0)
        return; // not moved
    float _straght_direction = get_direction(_x,_y);
    float _beta_straight = _straght_direction - direction;
    float _s_half = cos(_beta_straight) * lenght;
    float direction_tmp;
    if(_s_half < _s_straight/2){ // schlechter ansatz
        float h = sin(_beta_straight)*lenght;
        if(_beta_straight < CPP_M_PI/2){
            float len = _s_straight -_s_half;
            direction_tmp = CPP_M_PI - atan(h/len);
        }
        else if(_beta_straight > CPP_M_PI/2){
            float _beta_straight_tmp = CPP_M_PI - _beta_straight;
            float len = cos(_beta_straight_tmp)*lenght + _s_straight;
            direction_tmp = atan(h/len);
        }
        else{ // _beta_straight == CPP_M_PI/2
            direction_tmp = atan(lenght/_s_straight);
        }
    }
    else if(_s_half > _s_straight/2){
        float h = sin(_beta_straight) * _s_straight;
        direction_tmp = CPP_M_PI / 2 - _beta_straight + acos(h / lenght); // lenght always positive
    }
    else{ //_s_half == _s_straight/2
        direction_tmp = CPP_M_PI - _beta_straight; // sollte passen
    }
    x = temp.x; // set x to hitch pos
    y = temp.y; // set y to hitch pos
    direction = direction_tmp + _straght_direction; //set direction to new calculated trailer direction
    correct_direction(); // set direction to ]-pi : pi[
    move_straight(-lenght, 0); //  move to axle position
    last_hitch_pos = temp; //set current hitch position to last position for preparing the next move
}

#else
void follower::move(){
    position temp = connected_car->get_hitch();
    float _x = temp.x - last_hitch_pos.x;
    float _y = temp.y - last_hitch_pos.y;
    float _s_straight = sqrt(pow2(_x) + pow2(_y));
    float _straght_direction = get_direction(_x,_y);
    float _beta_straight = correct_direction_recursive(direction - _straght_direction);
    float direction_tmp;
#ifdef DEBUG
    debug_out(rad2deg(_straght_direction));
#endif
    if(_s_straight == 0.0)
        return; // not moved
    else if(_beta_straight == 0.0 || _beta_straight == CPP_M_PI || _beta_straight == -CPP_M_PI){
        direction_tmp = _beta_straight;
    }
    else if(fabs(_beta_straight) < CPP_M_PI/2){
        float _check_hypo = cos(_beta_straight) * lenght;
        if(_s_straight/2 < _check_hypo){
            float h = sin(_beta_straight) * _s_straight;
            direction_tmp = CPP_M_PI / 2 - _beta_straight + acos(h / lenght); // lenght always positive
        }
        else if(_s_straight/2 > _check_hypo){
            float h = sin(_beta_straight)*lenght;
            float len = _s_straight - _check_hypo;
            direction_tmp = CPP_M_PI - atan(h/len);
        }
        else/*_s_straight/2 == _check_hypo*/{
            direction_tmp = CPP_M_PI * SIGN(_beta_straight) - _beta_straight;
        }
    }
    else if(fabs(_beta_straight) > CPP_M_PI/2){
        float _beta_straight_tmp = CPP_M_PI - _beta_straight;
        float len = cos(_beta_straight_tmp)*lenght + _s_straight;
        float h = sin(_beta_straight_tmp)*lenght;
        direction_tmp = atan(h/len);
    }
    else/*_beta_straight == CPP_M_PI/2*/{
        direction_tmp = atan(lenght/_s_straight) * SIGN(_beta_straight);
    }
    x = temp.x; // set x to hitch pos
    y = temp.y; // set y to hitch pos
    direction = direction_tmp + _straght_direction; //set direction to new calculated trailer direction
    correct_direction(); // set direction to ]-pi : pi[
    move_straight(-lenght, 0); //  move to axle position
    last_hitch_pos = temp; //set current hitch position to last position for preparing the next move
}
#endif
float follower::beta(){
    return beta(connected_car->direction);
}

float follower::beta(float car_direction){
    return correct_direction_recursive(direction - car_direction);
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
