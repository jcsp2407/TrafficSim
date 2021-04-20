#include "Car.h"

int Car::count = 0;
int Car::totalCrossed = 0;

Car::Car(DirectionType direction, int lane, wxPoint pos, int arena):
    Vehicle(direction, lane, pos, arena)
{
    Setspeed(CAR);
    // setLength(bitmap.length(x));
    // setWidth(bitmap.length(y));
    count++;
}

Car::~Car()
{

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
 //   std::cout << "Showing Car heading (" << dirStr << ") in arena " << getCurrentArena()  << std::endl;
}

bool Car::move()
{
    oldPos = pos;

    switch(Getdirection()){
        case Vehicle::North:
            Setpos(wxPoint(Getpos().x, Getpos().y - 1));
            break;
        case Vehicle::South:
            Setpos(wxPoint(Getpos().x, Getpos().y + 1));
            break;
        case Vehicle::East:
            Setpos(wxPoint(Getpos().x + 1, Getpos().y));
            break;
        case Vehicle::West:
            Setpos(wxPoint(Getpos().x - 1, Getpos().y));
            break;
    }
}
