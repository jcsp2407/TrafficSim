#ifndef SIMULATION_H
#define SIMULATION_H

#include "Arena.h"
#include <vector>

class Simulation
{
    public:
        Simulation();
        virtual ~Simulation();

        int Getcars() { return cars; }
        void Setcars(int val) { cars = val; }
        int Getmotorcycles() { return motorcycles; }
        void Setmotorcycles(int val) { motorcycles = val; }
        int Gettrucks() { return trucks; }
        void Settrucks(int val) { trucks = val; }
        int GetarenasCnt() { return arenasCnt; }
        void SetarenasCnt(int val) { arenasCnt = val; }
        enum DriveModeType { Safe, Average, Crazy};      // declaring Safe, Average, and Crazy drive modes
        DriveModeType Getmode() { return mode; }
        void Setmode(DriveModeType val) { mode = val; }
        bool Getramps() { return ramps; }
        void Setramps(bool val) { ramps = val; }
        int GetfullyStopped() { return fullyStopped; }
        void IncfullyStopped() { fullyStopped++; }
        int Getscore() { return score; }
        void Incscore() { score++; }
        bool start();
        void stop();

    protected:

    private:
        int cars;
        int motorcycles;
        int trucks;
        int arenasCnt;
        DriveModeType mode;
        bool ramps;
        int fullyStopped;
        int score;
        std::vector<Arena> arenas;
};

#endif // SIMULATION_H
