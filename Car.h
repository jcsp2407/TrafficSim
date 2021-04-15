#ifndef CAR_H
#define CAR_H

#include "Vehicle.h"

#define CAR 2

class Car : public Vehicle
{
    public:
        Car(DirectionType direction, int lane, wxPoint pos, int arena);
        virtual ~Car();

        static int Getcount() { return count; }
        static void Setcount(int val) { count = val; }

        void show() override;
        bool move() override;
        wxPoint getPosFront();

    protected:

    private:
        static int count;
        static int total_count;
};

#endif // CAR_H
