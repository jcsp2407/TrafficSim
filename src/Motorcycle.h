#ifndef MOTORCYCLE_H
#define MOTORCYCLE_H

#include "Vehicle.h"

#define MOTORCYCLE 3

class Motorcycle : public Vehicle
{
    public:
        Motorcycle(DirectionType direction, int lane, wxPoint pos, int arena);
        virtual ~Motorcycle();

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

#endif // MOTORCYCLE_H
