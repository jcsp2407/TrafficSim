#include "Truck.h"
#include <iostream>

int Truck::count = 0;

Truck::Truck(DirectionType direction, int lane, wxPoint basePosition, wxPoint offsetPosition, int arena):
    Vehicle(direction, lane, basePosition, offsetPosition, arena)
{
    Setspeed(TRUCK);
    // setLength(bitmap.length(x));
    // setWidth(bitmap.length(y));
    count++;
}

Truck::~Truck()
{
    count--;
}

void Truck::show()
{
    std::string dirStr;
    switch(this->Getdirection()){
        case North:
            dirStr = "North";
            break;
        case South:
            dirStr = "South";
            break;
        case East:
            dirStr = "East";
            break;
        case West:
            dirStr = "West";
            break;
    }
    std::cout << "Showing Truck heading (" << dirStr << ") in arena " << getCurrentArena()  << std::endl;
}

bool Truck::move()
{
    std::cout << "Moving Truck with speed of" << Getspeed() << std::endl;
}
