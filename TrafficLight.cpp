#include "TrafficLight.h"

TrafficLight::TrafficLight(LightType color, wxPoint pos, int arena):
     Entity(pos, arena)
{
    this->color = color;
    if(color == LightType::Red)
        count = 1;
    else
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
                count = 1;
            }else{
                count++;
            }
            break;
        case Yellow:
            if(count >= YELLOW){
                color = Red;
                count = 1;
            }else{
                count++;
            }
            break;
        case Red:
            if(count >= RED){
                color = Green;
                count = 1;
            }else{
                count++;
            }
            break;
    }
}
void TrafficLight::show()
{
    std::string colorStr;
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
 //   std::cout << "Showing TrafficLight (" << colorStr << ") in arena " << getCurrentArena()  << std::endl;
}
