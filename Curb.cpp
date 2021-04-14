#include "Curb.h"

Curb::Curb(wxPoint pos, int arena): Entity(pos, arena)
{
    // setLength(bitmap.length(x));
    // setWidth(bitmap.length(y));
}

Curb::~Curb()
{
    //dtor
}

void Curb::show()
{
    std::cout << "Showing Curb!" << std::endl;
}
