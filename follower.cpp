#include "position.hpp"
#include "car.hpp"
#include "follower.hpp"
#include <cmath>
#include "sim_config.h"
#ifdef DEBUG
    #include <iostream>
    #define DEBUG_TAG "follower.cpp: "
    #define debug_out(x) std::cout << DEBUG_TAG << x << std::endl
static double rad2deg_tmp(double in){return in * 45.0 / atan(1);}
    #define ang(x) rad2deg_tmp(correct_direction_recursive(x))
#else
    #define debug_out(x)
#endif
follower::follower(car* bbc, double len, double hbeta) // hbeta is relative
        : position(), last_hitch_pos(){
    lenght = len;
    connected_car = bbc;
    set_to_car(hbeta);
}

follower::~follower(){}

void follower::set_to_car(double hbeta){
    pos = last_hitch_pos = connected_car->get_hitch();
    direction = connected_car->direction + hbeta; // add angle
    move_straight(-lenght,0); // set trailer to position
}

static inline double pow2(double x){
  return x*x;
}

    //double h = sin(_beta_straight)*_s_straight;

static inline double get_direction(double x, double y){ // outputs trash
    if(x < 0.0)
        if(y == 0.0)
            return CPP_M_PI; //180° x negative, y = 0
        else
            return atan(y/x) - CPP_M_PI * SIGN(y);
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
    point temp = connected_car->get_hitch();
    double _x = temp.x - last_hitch_pos.x;
    double _y = temp.y - last_hitch_pos.y;
    double _s_straight = sqrt(pow2(_x) + pow2(_y));
    if(_s_straight == 0.0)
        return; // not moved
    double _straght_direction = get_direction(_x,_y);
    double _beta_straight = _straght_direction - direction;
    double _s_half = cos(_beta_straight) * lenght;
    double direction_tmp;
    if(_s_half < _s_straight/2){ // schlechter ansatz
        double h = sin(_beta_straight)*lenght;
        if(_beta_straight < CPP_M_PI/2){
            double len = _s_straight -_s_half;
            direction_tmp = CPP_M_PI - atan(h/len);
        }
        else if(_beta_straight > CPP_M_PI/2){
            double _beta_straight_tmp = CPP_M_PI - _beta_straight;
            double len = cos(_beta_straight_tmp)*lenght + _s_straight;
            direction_tmp = atan(h/len);
        }
        else{ // _beta_straight == CPP_M_PI/2
            direction_tmp = atan(lenght/_s_straight);
        }
    }
    else if(_s_half > _s_straight/2){
        double h = sin(_beta_straight) * _s_straight;
        direction_tmp = CPP_M_PI / 2 - _beta_straight + acos(h / lenght); // lenght always positive
    }
    else{ //_s_half == _s_straight/2
        direction_tmp = CPP_M_PI - _beta_straight; // sollte passen
    }
    pos.x = temp.x; // set x to hitch pos
    pos.y = temp.y; // set y to hitch pos
    direction = direction_tmp + _straght_direction; //set direction to new calculated trailer direction
    correct_direction(); // set direction to ]-pi : pi[
    move_straight(-lenght, 0); //  move to axle position
    last_hitch_pos = temp; //set current hitch position to last position for preparing the next move
}

#else
void follower::move(){
    point temp = connected_car->get_hitch();
    double _x = temp.x - last_hitch_pos.x;
    double _y = temp.y - last_hitch_pos.y;
    double _s_straight = sqrt(pow2(_x) + pow2(_y));
    double _straght_direction = get_direction(_x,_y);
    double _beta_straight = correct_direction_recursive(direction - _straght_direction);
    double direction_tmp;
    if(_s_straight == 0.0)
        return; // not moved
    else if(_beta_straight == 0.0 || _beta_straight == CPP_M_PI || _beta_straight == -CPP_M_PI){
        debug_out("0 ||+-360");
        direction_tmp = _beta_straight;
    }
    else if(fabs(_beta_straight) < CPP_M_PI/2){
        
        double _check_hypo = cos(_beta_straight) * lenght;
        if(_s_straight/2 < _check_hypo){ //
            debug_out("x<+-90 c1");
            double h = sin(_beta_straight) * _s_straight;
            double d1 = CPP_M_PI / 2 - _beta_straight;
            double d2 = acos(h / lenght);
            direction_tmp = CPP_M_PI/2 - d1 - d2; // lenght always positive
        }
        else if(_s_straight/2 > _check_hypo){
            debug_out("x<+-90 c2");
            double h = sin(_beta_straight) * lenght;
            double len = _s_straight - _check_hypo;
            direction_tmp = CPP_M_PI * SIGN(_beta_straight) - atan(h/len);
        }
        else/*_s_straight/2 == _check_hypo*/{
            debug_out("x<+-90 c0=0");
            direction_tmp = CPP_M_PI * SIGN(_beta_straight) - _beta_straight;
        }
    }
    else if(fabs(_beta_straight) > CPP_M_PI/2){ //quite simlar to c2
        debug_out("x>+-90");
        double beta_straight_90 = CPP_M_PI - _beta_straight;
        double len = cos(beta_straight_90)*lenght + _s_straight;
        double h = sin(beta_straight_90)*lenght;
        //double h = sin(_beta_straight) * lenght;
        //double len = cos(_beta_straight) * lenght + _s_straight;
        direction_tmp = CPP_M_PI * SIGN(_beta_straight) - atan(h / len);
        debug_out("len: " << len << ", h: " << h << ", b_s: " << ang(beta_straight_90));
        direction_tmp = CPP_M_PI * SIGN(_beta_straight) - atan(h / len);
    }
    else/*_beta_straight == CPP_M_PI/2*/{
        debug_out("x==+-90");
        direction_tmp = atan(lenght/_s_straight) * SIGN(_beta_straight);
    }
    pos = temp; // set pos to hitch pos
    direction = direction_tmp + _straght_direction; //set direction to new calculated trailer direction
    correct_direction(); // set direction to ]-pi : pi[
    move_straight(-lenght, 0); //  move to axle position
    last_hitch_pos = temp; //set current hitch position to last position for preparing the next move
    #ifdef DEBUG
        debug_out("direction: " << ang(_straght_direction) << ", beta: " << ang(_beta_straight) << ", s: " << _s_straight << ", tmp: " << ang(direction_tmp));
    #endif
}
#endif
double follower::beta(){
    return beta(connected_car->direction);
}

double follower::beta(double car_direction){
    return correct_direction_recursive(direction - car_direction);
}
