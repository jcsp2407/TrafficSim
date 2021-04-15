#include "Truck.h"

int Truck::count = 0;

Truck::Truck(DirectionType direction, int lane, wxPoint pos, int arena):
    Vehicle(direction, lane, pos, arena)
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

wxPoint Truck::getPosFront()
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
