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

//(*Headers(Traffic_SimulationFrame)
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include "Simulation.h"
//*)

class Traffic_SimulationFrame: public wxFrame
{
    public:

        Traffic_SimulationFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~Traffic_SimulationFrame();

    private:

        int speed;

        //(*Handlers(Traffic_SimulationFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        //*)

        //(*Identifiers(Traffic_SimulationFrame)
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(Traffic_SimulationFrame)
        wxStatusBar* StatusBar1;
        wxTimer SimTimer;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // TRAFFIC_SIMULATIONMAIN_H
