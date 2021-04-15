#include "Ramp.h"

Ramp::Ramp(bool ascending, wxPoint pos, int arena): Entity(pos, arena)
{
    this->ascending = ascending;
    // setLength(bitmap.length(x));
    // setWidth(bitmap.length(y));
}

Ramp::~Ramp()
{
    //dtor
}

void Ramp::show()
{
    std::cout << "Showing Ramp in arena " << getCurrentArena() << std::endl;
}
