#include "Vehicle.h"

int Vehicle::total = 0;

Vehicle::Vehicle(DirectionType direction, int lane, wxPoint basePosition, wxPoint offsetPosition, int arena):
     Entity(basePosition, offsetPosition, arena)
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
