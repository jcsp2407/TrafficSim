/***************************************************************
 * Name:      Traffic_SimulationMain.h
 * Purpose:   Defines Application Frame
 * Author:    Adrian A. Muino, Juan Saez, Alexander Perez ()
 * Created:   2021-03-28
 * Copyright: Adrian A. Muino, Juan Saez, Alexander Perez ()
 * License:
 **************************************************************/

#ifndef TRAFFIC_SIMULATIONMAIN_H
#define TRAFFIC_SIMULATIONMAIN_H
#include "Traffic_SimulationApp.h"
//(*Headers(Simulation)
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/dcbuffer.h>
#include "Arena.h"
#include "Entity.h"
#include "Vehicle.h"
#include "Car.h"
#include "Motorcycle.h"
#include "TrafficLight.h"

//*)

class Simulation: public wxFrame
{
    public:

        Simulation(wxWindow* parent,wxWindowID id = -1);
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
        //friend void wxImagePanel::SetState(int a);
		enum state {startScreen, settingsScreen, runningScreen, endScreen};

    private:

        int cars;
        int motorcycles;
        int trucks;
        int arenasCnt;
        DriveModeType mode;
        bool ramps;
        int fullyStopped;
        int score;
        Entity** obstacles;
        Arena** arenas;
        TrafficLight** lights;
        Vehicle** vehicles;
        wxPanel *startframe;

        wxPanel *test;
		wxPanel *starpanel;
		wxPanel *configpanel;
		wxPanel *endpanel;

        int speed;
        int screenState;

        wxImage car_img;
        wxImage truck_img;
        wxImage motorcycle_img;
        wxImage trafficRed_img;
        wxImage trafficGreen_img;
        wxImage trafficYellow_img;
        wxImage start_img;
        wxImage traffic_img;
        wxImage sim_img;
        wxImage clicktostart_img;

        wxFont startScreenFont;

        //(*Handlers(Simulation)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnTick(wxTimerEvent& event);
        void OnPaint(wxPaintEvent& event);
        void OnEraseBackground(wxEraseEvent& event);
        void OnClickToStart(wxMouseEvent& event);
        //*)

        //(*Identifiers(Simulation)
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        static const long ID_TIMER1;
        static const long ID_TESTPANEL;
        //*)

        //(*Declarations(Simulation)
        wxStatusBar* StatusBar1;
        wxTimer SimTimer;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // TRAFFIC_SIMULATIONMAIN_H
