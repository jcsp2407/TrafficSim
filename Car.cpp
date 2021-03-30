#include "Car.h"

int Car::count = 0;

Car::Car(DirectionType direction, int lane, wxPoint basePosition, wxPoint offsetPosition, int arena):
    Vehicle(direction, lane, basePosition, offsetPosition, arena)
{
    Setspeed(CAR);
    // setLength(bitmap.length(x));
    // setWidth(bitmap.length(y));
    count++;
}

Car::~Car()
{
    //dtor
}

void Car::show()
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
    std::cout << "Showing Car heading (" << dirStr << ") in arena " << getCurrentArena()  << std::endl;
}

bool Car::move()
{
    std::cout << "Moving Car with speed of" << Getspeed() << std::endl;
}
