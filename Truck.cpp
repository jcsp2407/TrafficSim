#include "Truck.h"

int Truck::count = 0;

Truck::Truck(DirectionType direction, int lane, wxPoint offsetPosition, int arena):
    Vehicle(direction, lane, offsetPosition, arena)
{
    Setspeed(TRUCK);
    // setLength(bitmap.length(x));
    // setWidth(bitmap.length(y));
    count++;
}

Truck::~Truck()
{
    //dtor
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
        switch(Getdirection()){
        case Vehicle::North:
            SetoffsetPosition(wxPoint(GetoffsetPosition().x, GetoffsetPosition().y - 1));
            break;
        case Vehicle::South:
            SetoffsetPosition(wxPoint(GetoffsetPosition().x, GetoffsetPosition().y + 1));
            break;
        case Vehicle::East:
            SetoffsetPosition(wxPoint(GetoffsetPosition().x + 1, GetoffsetPosition().y));
            break;
        case Vehicle::West:
            SetoffsetPosition(wxPoint(GetoffsetPosition().x - 1, GetoffsetPosition().y));
            break;
    }
}
