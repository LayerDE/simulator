#include "simulator.hpp"
#include <cmath>
void null_out(float x, float y, float direction){}

void simulator::step(float step_lenght){
    bb->move(step_lenght);
    trail->move();

}

simulator::simulator(float bbx, float bby, float bbwb, float bbr2h, float bbangle, float bbalpha, float followerlen, float followerbeta, float step_size){
    bb = new car(bbwb, bbr2h, bbx, bby, bbangle, bbalpha);
    trail = new follower(bb, followerlen, followerbeta);
    use_output = false;
    trail_out = bb_out = null_out;
    step_lenght = fabs(step_size);
}

void simulator::reset(){
    reset_output();
}

float simulator::output(){
        bb_out(bb->x,bb->y,bb->direction);
        trail_out(trail->x, trail->y, trail->direction);
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

void simulator::set_output(point_out car,point_out trailer, bool sim_out){
    use_output = sim_out;
    bb_out = car;
    trail_out = trailer;
}

void simulator::reset_output(){
    use_output = false;
    trail_out = bb_out = null_out;
}
