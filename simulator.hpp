#pragma once
#include "car.hpp"
#include "follower.hpp"


typedef void (*point_out)(void* context, point x0, float direction);

class simulator{
    private:
        void* context;
        bool use_output;
        float step_lenght;
        point_out bb_out;
        point_out trail_out;
        car* bb;
        follower* trail;
        void step(float move_lenght);
        float distance;
    public:
        simulator(void* hcontext, float bbx, float bby, float bbwb, float bbr2h, float bbangle, float bbalpha, float followerlen, float followerbeta, float step_size);
        ~simulator();
        void set_alpha(float bbalpha);
        void simulate(float lenght);
        void set_output(point_out car,point_out trailer, bool sim_out);
        void reset_output();
        float output();
        void reset();
        float get_distance();
        void set_values(float bbx, float bby, float bbangle, float bbalpha, float followerbeta);
};