#include <iostream>
#define _USE_MATH_DEFINES
#include "position.hpp"
#include "car.hpp"
#include "simulator.hpp"

#include <math.h>

using namespace std;

const int sim_cnt = 2;

float rad2deg(float in){
  return in * 45.0 / M_PI_4;
}
float deg2rad(float in){
  return in * M_PI_4 / 45.0;
}


void _point_out(const char* name, float x, float y, float direction){
    cout << name <<": " << x <<", " << y << ": " << rad2deg(direction) << endl;
}


void trail_point_out(point x0, float direction){
    _point_out("Trailer", x0.x, x0.y, direction);
}

void car_point_out(point x0, float direction){
    _point_out("Car", x0.x, x0.y, direction);
}

// simulator(float bbx, float bby, float bbwb, float bbr2h, float bbangle, float bbalpha, float followerlen, float followerbeta, float step_size)

int main(int argc, char *argv[]){
    const float bbwb = 0.35, bbr2h = 0.05, followerlen = 0.60;
    const float bbx = 0.0, bby = 0.0, bbangle = 0.0, bbalpha = deg2rad(20);
    const float followerbeta = deg2rad(0);
//    const float stepsize = 0.001;
    cout << "Simulator init..." << endl;
    simulator* sim[sim_cnt] = {new simulator(bbx, bby, bbwb, bbr2h, bbangle, -bbalpha, followerlen, followerbeta, 0.0001)
    ,new simulator(bbx, bby, bbwb, bbr2h, bbangle, bbalpha, followerlen, followerbeta, 0.001)};
    cout << "Simulate..." << endl;
    while(1){
        cout << "wait" << endl;
        cin.ignore();
        for(int i =0; i < sim_cnt; i++){
            sim[i]->set_output(car_point_out, trail_point_out,false);
            cout << "sim[" << i << "]" << endl;
            sim[i]->simulate(-0.01);
            float temp = rad2deg(sim[i]->output());
            cout << "sim[" << i << "] beta:" << temp << endl;
        }
    }      
    cout << "Simulation finished" << endl;
    //delete[] sim;
    return 0;
}