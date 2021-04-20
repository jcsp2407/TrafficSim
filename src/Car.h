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
        static int GetTotalCrossed() { return totalCrossed; }
        static void IncTotalCrossed() { totalCrossed++; }

        void show() override;
        bool move() override;

    protected:

    private:
        static int count;
        static int totalCrossed;
};

#endif // CAR_H
