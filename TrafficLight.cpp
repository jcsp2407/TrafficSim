#include "TrafficLight.h"
#include <wx/msgdlg.h>
#include <iostream>

TrafficLight::TrafficLight(LightType color, wxPoint basePosition, wxPoint offsetPosition, int arena):
     Entity(basePosition, offsetPosition, arena)
{
    this->color = color;
    count = 0;
    // setLength(bitmap.length(x));
    // setWidth(bitmap.length(y));
}

TrafficLight::~TrafficLight()
{
    //dtor
}

void TrafficLight::alternate()
{
    switch(color){
        case Green:
            if(count >= GREEN){
                color = Yellow;
                count = 0;
            }else{
                count++;
            }
            break;
        case Yellow:
            if(count >= YELLOW){
                color = Red;
                count = 0;
            }else{
                count++;
            }
            break;
        case Red:
            if(count >= RED){
                color = Green;
                count = 0;
            }else{
                count++;
            }
            break;
    }
}
void TrafficLight::show()
{
    wxString colorStr;
    switch(color){
        case Green:
            colorStr = "green";
            break;
        case Yellow:
            colorStr = "yellow";
            break;
        case Red:
            colorStr = "red";
            break;
    }

    std::cout << "Showing TrafficLight (" << colorStr << ") in arena " << getCurrentArena()  << std::endl;
}
