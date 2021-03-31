#ifndef ARENA_H
#define ARENA_H

#include "Entity.h"
#include <vector>
#include <map>

class Arena
{
    public:
        Arena();
        virtual ~Arena();

        int Getintersections() { return intersections; }
        void Setintersections(int val) { intersections = val; }
        wxPoint GetbasePosition() { return basePosition; }
        void SetbasePosition(wxPoint val) { basePosition = val; }
        static int Getlength() { return length; }
        static void Setlength(int val) { length = val; }
        static int Getwidth() { return width; }
        static void Setwidth(int val) { width = val; }
        int Getlanes() { return lanes; }
        void Setlanes(int val) { lanes = val; }

    protected:

    private:
        int intersections;
        wxPoint basePosition;
        static int length;
        static int width;
        int lanes;
        std::map<wxPoint, Entity*> obstaclePos;
        std::vector<Entity> stationary;
        std::vector<Entity> vehicles;
};

#endif // ARENA_H
