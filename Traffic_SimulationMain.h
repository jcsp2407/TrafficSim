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

//(*Headers(Simulation)
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/dcbuffer.h>
#include <wx/msgdlg.h>
#include <wx/spinctrl.h>
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>

#include "Arena.h"
#include "Car.h"
//#include "Curb.h"
#include "Entity.h"
#include "Motorcycle.h"
///#include "Ramp.h"
///#include "Traffic_SimulationApp.h"
#include "TrafficLight.h"
#include "Truck.h"
#include "Vehicle.h"
//*)

#define W_WIDTH 480       // width of window
#define WIDTH 480         // width of client area
#define W_HEIGHT 253      // height of window
#define HEIGHT 216        // height of client area

class Simulation: public wxFrame
{
    public:

        Simulation(wxWindow* parent,wxWindowID id = -1);
        virtual ~Simulation();

        enum DriveModeType { Safe, Average, Crazy, FromMiami};      // declaring Safe, Average, and Crazy drive modes
     //   void Setmode(DriveModeType val) { mode = val; }
        bool Getramps() { return ramps; }
        void Setramps(bool val) { ramps = val; }
        int GetfullyStopped() { return fullyStopped; }
        void IncfullyStopped() { fullyStopped++; }
        int Getscore() { return score; }
        void Incscore() { score++; }
        bool start();
        void stop();

    private:

        int cars;
        int motorcycles;
        int trucks;
        int arenasCnt;
        int fullyStopped;
        int score;
        int speed;
        int screenState;

        DriveModeType mode;
        bool ramps;

        // containers
        Entity** obstacles;
        Arena** arenas;
        TrafficLight** lights;
        Vehicle** vehicles;

        enum state {startScreen, settingsScreen, runningScreen, endScreen};

        wxPanel *startPanel;
        wxPanel *settingsPanel;
        wxScrolledWindow *mainPanel;

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
        void OnResize(wxSizeEvent& event);

		///settings panel

        void OnBeginButtonClick(wxCommandEvent& event);

        //*)

        //(*Identifiers(Simulation)
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        static const long ID_TIMER1;
        static const long ID_STARTPANEL;
        static const long ID_MAINPANEL;


        ///identifiers for settings panel
		static const long ID_ArenaCtrl;
        static const long ID_ArenaText;
        static const long ID_DrivingText;
        static const long ID_CarSpinCtrl;
        static const long ID_BikeSpinCtrl;
        static const long ID_TruckSpinCtrl;
        static const long ID_DrivingModeCtrl;
        static const long ID_STATICTEXT3;
        static const long ID_STATICTEXT4;
        static const long ID_STATICTEXT5;
        static const long ID_STATICTEXT6;
        static const long ID_BeginButton;
        static const long ID_PANEL3;
        static const long ID_PANEL1;
        //*)

        //(*Declarations(Simulation)
        wxStatusBar* StatusBar1;
        wxTimer SimTimer;
        wxButton* beginButton;

        ///settings declarations
        wxButton* BeginButton;
        wxChoice* DrivingModeCtrl;
        wxPanel* SettingPanel2;
        wxPanel* SettingPanel;
        wxSpinCtrl* ArenaCtrl;
        wxSpinCtrl* BikeSpinCtrl;
        wxSpinCtrl* CarSpinCtrl;
        wxSpinCtrl* TruckSpinCtrl;
        wxStaticText* ArenaText;
        wxStaticText* BikeText;
        wxStaticText* CarText;
        wxStaticText* DrivingText;
        wxStaticText* SettingsText;
        wxStaticText* TruckText;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // TRAFFIC_SIMULATIONMAIN_H
