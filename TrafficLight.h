#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "Entity.h"

#define GREEN 4
#define YELLOW 3
#define RED 9

class TrafficLight : public Entity
{
    public:
    	enum DirectionType {North, East, South, West};
        enum LightType {Green, Red, Yellow};      // declaring Green, Yellow, and Red lights
		DirectionType Getdirection() { return direction; }
        void Setdirection(DirectionType val) { direction = val; }
        TrafficLight(LightType color, wxPoint pos, int arena);
        virtual ~TrafficLight();

        LightType Getcolor() { return color; }
        void Setcolor(LightType val) { color = val; }

        void alternate();
        void show() override;

    protected:

    private:
        LightType color;
        int count;
        DirectionType direction;
};

#endif // TRAFFICLIGHT_H
