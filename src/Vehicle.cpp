#include "Vehicle.h"

int Vehicle::total = 0;

Vehicle::Vehicle(DirectionType direction, int lane, wxPoint pos, int arena):
     Entity(pos, arena)
{
    this->direction = direction;
    this->lane = lane;

    //set crosses, crashed, ...
    crossed = crashed = false;
    total++;
}

Vehicle::~Vehicle()
{
    //dtor
}

wxPoint Vehicle::getPosFront()
{
    switch(Getdirection()){
        case Vehicle::North:
            return wxPoint(Getpos().x, Getpos().y - 1);
        case Vehicle::South:
            return wxPoint(Getpos().x, Getpos().y + 1);
        case Vehicle::East:
            return wxPoint(Getpos().x + 1, Getpos().y);
        case Vehicle::West:
            return wxPoint(Getpos().x - 1, Getpos().y);
    }
}
