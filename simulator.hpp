#pragma once
#include "car.hpp"
#include "follower.hpp"


typedef void (*point_out)(void* context, point x0, double direction);

class simulator{
    private:
        void* context;
        bool use_output;
        double step_lenght;
        point_out bb_out;
        point_out trail_out;
        car* bb;
        follower* trail;
        void step(double move_lenght);
        double distance;
    public:
        simulator(void* hcontext, double bbx, double bby, double bbwb, double bbr2h, double bbangle, double bbalpha, double followerlen, double followerbeta, double step_size);
        ~simulator();
        void set_alpha(double bbalpha);
        void simulate(double lenght);
        void set_output(point_out car,point_out trailer, bool sim_out);
        void reset_output();
        double output();
        void reset();
        double get_distance();
        void set_values(double bbx, double bby, double bbangle, double bbalpha, double followerbeta);
};