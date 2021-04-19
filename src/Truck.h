#ifndef TRUCK_H
#define TRUCK_H

#include "Vehicle.h"

#define TRUCK 1

class Truck : public Vehicle
{
    public:
        Truck(DirectionType direction, int lane, wxPoint pos, int arena);
        virtual ~Truck();

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

#endif // TRUCK_H
