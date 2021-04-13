#include "Ramp.h"

Ramp::Ramp(bool ascending, wxPoint offsetPosition, int arena): Entity(offsetPosition, arena)
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
