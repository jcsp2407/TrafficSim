#include "Curb.h"
#include <iostream>     // std::cout, std::end

Curb::Curb(wxPoint basePosition, wxPoint offsetPosition, int arena): Entity(basePosition, offsetPosition, arena)
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
