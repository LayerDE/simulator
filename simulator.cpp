#include "simulator.hpp"

void simulator::step(float step_lenght){
    bb->move(step_lenght);
    trail->move();

}

simulator::simulator(float bbx, float bby, float bbwb, float bbr2h, float bbangle, float bbalpha, float followerlen, float followerbeta, float step_size){
    bb = new car(bbwb,bbr2h,bbx,bby,bbangle,bbalpha);
    trail = new follower(bb,followerlen,followerbeta);
    use_output = false;
    step_lengt = step_size;
};

void simulator::simulate(float lenght){
    while(lenght-=step_lengt > 0){
        step(step_lengt);
        if(use_output){
            bb_out(bb->x,bb->y,bb->direction);
            trail_out(trail->x, trail->y, trail->direction);
        }
    }
}

void simulator::set_output(point_out car,point_out trailer){
    use_output = true;
    bb_out = car;
    trail_out = trailer;
}
