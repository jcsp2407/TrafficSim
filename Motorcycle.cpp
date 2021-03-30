#include "Motorcycle.h"

int Motorcycle::count = 0;

Motorcycle::Motorcycle(DirectionType direction, int lane, wxPoint basePosition, wxPoint offsetPosition, int arena):
    Vehicle(direction, lane, basePosition, offsetPosition, arena)
{
    Setspeed(MOTORCYCLE);
    // setLength(bitmap.length(x));
    // setWidth(bitmap.length(y));
    count++;
}

Motorcycle::~Motorcycle()
{
    count--;
}

void Motorcycle::show(){
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
    std::cout << "Showing Motorcycle heading (" << dirStr << ") in arena " << getCurrentArena() << std::endl;
}

bool Motorcycle::move(){
    std::cout << "Moving Motorcycle with speed of" << Getspeed() << std::endl;
}
