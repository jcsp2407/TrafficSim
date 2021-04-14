#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "Entity.h"

#define GREEN 300
#define YELLOW 50
#define RED 300

class TrafficLight : public Entity
{
    public:
        enum LightType {Green, Yellow, Red};      // declaring Green, Yellow, and Red lights

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
};

#endif // TRAFFICLIGHT_H
