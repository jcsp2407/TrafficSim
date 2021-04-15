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

        void show() override;
        bool move() override;
        wxPoint getPosFront();

    protected:

    private:
        static int count;
        static int total_count;
};

#endif // MOTORCYCLE_H
