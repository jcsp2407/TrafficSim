#include "Curb.h"

Curb::Curb(wxPoint offsetPosition, int arena): Entity(offsetPosition, arena)
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
