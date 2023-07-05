#include "simulator.hpp"
#include "sim_config.h"
#include <cmath>
void null_out(void* context, point x0, float direction){}

void simulator::step(float step_lenght){
    bb->move(step_lenght);
    trail->move();
    distance += abs(step_lenght);
}

simulator::simulator(void* hcontext, float bbx, float bby, float bbwb, float bbr2h, float bbangle, float bbalpha, float followerlen, float followerbeta, float step_size){
    bb = new car(bbwb, bbr2h, bbx, bby, bbangle, bbalpha);
    trail = new follower(bb, followerlen, followerbeta);
    use_output = false;
    trail_out = bb_out = null_out;
    step_lenght = fabs(step_size);
    distance = 0;
    context = hcontext;
}

simulator::~simulator(){
    //delete bb;
    //delete trail;
}

void simulator::reset(){
    reset_output();
}

float simulator::output(){
        bb_out(context, bb->pos, bb->direction);
        trail_out(context, trail->pos, trail->direction);
        return trail->beta();
}

void simulator::simulate(float lenght){
    while(lenght != 0.0){
        if(fabs(lenght) > step_lenght){
            step(SIGN(lenght) * step_lenght);
            lenght -= SIGN(lenght) * step_lenght;
        }
        else{
            step(lenght);
            lenght = 0.0;
        }
        if(use_output)
            output();
    }
}

void simulator::set_values(float bbx, float bby, float bbangle, float bbalpha, float followerbeta){
    bb->pos.x = bbx;
    bb->pos.y = bby;
    bb->direction = bbangle;
    set_alpha(bbalpha);
    trail->set_to_car(followerbeta);
}
void simulator::set_alpha(float bbalpha){
    bb->alpha = bbalpha;
}

void simulator::set_output(point_out car,point_out trailer, bool sim_out){
    use_output = sim_out;
    bb_out = car;
    trail_out = trailer;
}

void simulator::reset_output(){
    use_output = false;
    trail_out = bb_out = null_out;
}

float simulator::get_distance(){
    return distance;
}
