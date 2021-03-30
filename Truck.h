#ifndef TRUCK_H
#define TRUCK_H

#include "Vehicle.h"

#define TRUCK 1

class Truck : public Vehicle
{
    public:
        Truck(DirectionType direction, int lane, wxPoint basePosition, wxPoint offsetPosition, int arena);
        virtual ~Truck();

        static int Getcount() { return count; }
        static void Setcount(int val) { count = val; }

        void show() override;
        bool move() override;

    protected:

    private:
        static int count;
};

#endif // TRUCK_H
