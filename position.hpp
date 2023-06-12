#pragma once

#define SIGN(x) ((x > 0) ? 1 : ((x < 0) ? -1 : 0))

class position{
    public:
        position();
        position(float hx,float hy,float hdirection);
        float x,y,direction;
        virtual void move(float move_lenght);
        void correct_direction();
        void move_straight(float lenght, float height);
};