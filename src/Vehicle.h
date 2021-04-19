#ifndef VEHICLE_H
#define VEHICLE_H

#include "Entity.h"


class Vehicle : public Entity
{
    public:
        enum DirectionType {North, South, East, West};      // declaring North, South, East, and West directions

        Vehicle(DirectionType direction, int lane, wxPoint pos, int currentArena);
        virtual ~Vehicle();

        DirectionType Getdirection() { return direction; }
        void Setdirection(DirectionType val) { direction = val; }
        int Getspeed() { return speed; }
        void Setspeed(int val) { speed = val; }
        int Getlane() { return lane; }
        void Setlane(int val) { lane = val; }
        bool Getcrossed() { return crossed; }
        void Setcrossed(bool val) { crossed = val; }
        bool Getcrashed() { return crashed; }
        void Setcrashed(bool val) { crashed = val; }
        static int Gettotal() { return total; }
        static void Settotal(int val) { total = val; }
        void goUp(){currentArena++;}
        void goDown(){currentArena--;}
        wxPoint GetOldPos() { return oldPos; }
        wxPoint getPosFront();

        virtual bool move() = 0;

    protected:
        wxPoint oldPos;

    private:
        DirectionType direction;
        int speed;
        int lane;
        bool crossed;
        bool crashed;
        static int total;
};

#endif // VEHICLE_H
