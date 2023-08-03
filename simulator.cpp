#include "simulator.hpp"
#include "sim_config.h"
#include <cmath>
void null_out(void* context, point x0, double direction){}

void simulator::step(double step_lenght){
    bb->move(step_lenght);
    trail->move();
    distance += fabs(step_lenght);
}

simulator::simulator(void* hcontext, double bbx, double bby, double bbwb, double bbr2h, double bbangle, double bbalpha, double followerlen, double followerbeta, double step_size){
    bb = new car(bbwb, bbr2h, bbx, bby, bbangle, bbalpha);
    trail = new follower(bb, followerlen, followerbeta);
    use_output = false;
    trail_out = bb_out = null_out;
    step_lenght = fabs(step_size);
    distance = 0;
    context = hcontext;
}

simulator::~simulator(){
    delete bb;
    delete trail;
}

void simulator::reset(){
    reset_output();
}

double simulator::output(){
        bb_out(context, bb->pos, bb->direction);
        trail_out(context, trail->pos, trail->direction);
        return trail->beta();
}

void simulator::simulate(double lenght){
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

void simulator::set_values(double bbx, double bby, double bbangle, double bbalpha, double followerbeta){
    bb->pos.x = bbx;
    bb->pos.y = bby;
    bb->direction = bbangle;
    set_alpha(bbalpha);
    trail->set_to_car(followerbeta);
}
void simulator::set_alpha(double bbalpha){
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

double simulator::get_distance(){
    return distance;
}
