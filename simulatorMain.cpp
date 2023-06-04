#include <iostream>
#define _USE_MATH_DEFINES
#include "position.hpp"
#include "car.hpp"
#include "simulator.hpp"
#include <math.h>

using namespace std;

int sim_cnt;

void dumpout(simulator* in){
    int len = 0;
    for(int x = 0; x < len; x++)
        cout << "point" << endl;
}

float rad2deg(float in){
  return in * 45.0 / M_PI_4;
}
float deg2rad(float in){
  return in * M_PI_4 / 45.0;
}


void _point_out(char* name, float x, float y, float direction){
    cout << name <<": " << x <<", " << y << ": " << rad2deg(direction) << endl;
}


void trail_point_out(float x, float y, float direction){
    _point_out("Trailer", x, y, direction);
}

void car_point_out(float x, float y, float direction){
    _point_out("Car", x, y, direction);
}

// simulator(float bbx, float bby, float bbwb, float bbr2h, float bbangle, float bbalpha, float followerlen, float followerbeta, float step_size)

int main(int argc, char *argv[]){
    const float bbwb = 35, bbr2h = 5,followerlen = 60;
    const float bbx = 0,bby = 0,bbangle = 0,bbalpha = 0;
    const float followerbeta = 0;
    const float stepsize = 0.001;
    cout << "Simulator init..." << endl;
    simulator* sim[sim_cnt = 2] = {new simulator(bbx, bby, bbwb, bbr2h, bbangle, bbalpha, followerlen, followerbeta, 0.001)
    ,new simulator(bbx, bby, bbwb, bbr2h, bbangle, bbalpha, followerlen, followerbeta, 0.0001)};
    cout << "Simulate..." << endl;
    for(int i =0; i < sim_cnt; i++){
        sim[i]->set_output(car_point_out,trail_point_out);
        sim[i]->simulate(10);
    }        
    cout << "Simulation finished" << endl;
    delete[] sim;
    return 0;
}