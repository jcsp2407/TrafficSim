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
	wxBitmap start_img; //main screen when loading program
	wxBitmap end_img; //ending screen
	wxBitmap bg_img; //main simulation background image

    wxBitmap car_img; //generic car
    wxBitmap truck_img; //generic truck img
    wxBitmap MOTORCYCLE_img;//generic bike img
    wxBitmap trafficlight_img; //static traffic light
    wxBitmap streets_img; //might need to remove this, but static streets


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
