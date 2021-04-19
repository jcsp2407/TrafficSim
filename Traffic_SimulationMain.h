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
#include <wx/gauge.h>
#include <wx/timer.h>


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
#define R_WIDTH 430         // width of running panel
#define A_WIDTH 214       // width of arena
#define W_HEIGHT 253      // height of window
#define HEIGHT 216        // height of client area
#define R_HEIGHT 216        // height of running panel
#define A_HEIGHT 214      // height of arena

class myImageGridCellRenderer : public wxGridCellStringRenderer
{
public:
    wxImage inImage;

    myImageGridCellRenderer(wxImage test){
        inImage = test;
    }

    virtual void Draw(wxGrid& grid, wxGridCellAttr& attr, wxDC& dc, const wxRect& rect, int row, int col, bool isSelected)
    {
		dc.SetPen(*wxGREY_PEN);
        dc.SetBrush(*wxGREY_BRUSH);
        dc.DrawRectangle(rect);

        wxImage cellImage = inImage;
        wxBitmap cellBitmap(cellImage);
        dc.DrawBitmap(cellBitmap, rect.x, rect.y);
    }
};

class RoadGridCellRenderer : public wxGridCellStringRenderer
{
public:
    virtual void Draw(wxGrid& grid, wxGridCellAttr& attr, wxDC& dc, const wxRect& rect, int row, int col, bool isSelected)
    {
        dc.SetPen(*wxGREY_PEN);
        dc.SetBrush(*wxGREY_BRUSH);
        dc.DrawRectangle(rect);
    }
};

class Simulation: public wxFrame
{
    public:

        Simulation(wxWindow* parent,wxWindowID id = -1);
        virtual ~Simulation();

        enum DriveModeType { Safe, Average, Crazy, FromMiami};      // declaring Safe, Average, and Crazy drive modes
        int GetfullyStopped() { return fullyStopped; }
        void IncfullyStopped() { fullyStopped++; }
        int Getscore() { return score; }
        void Incscore() { score++; }
        bool start();
        void stop();
		void Crashed(Vehicle* V, Vehicle* temp);
		bool IsGonnaCrash(Vehicle* V);
		void compute(Vehicle*);

    private:

        int cars;
        int motorcycles;
        int trucks;
        int arenasCnt;
        int fullyStopped;
        int score;
        int speed;
        int screenState;
		int time_per_sec;
		int mytimeCount;

        DriveModeType mode;

        // containers
        Vehicle**** obstacles;
        Arena** arenas;
        TrafficLight** lights;
        Vehicle** vehicles;

        enum state {startScreen, settingsScreen, runningScreen, endScreen};

        wxScrolledWindow *mainPanel;
        wxPanel *startPanel;
        wxPanel *scorePanel;
        wxPanel *endPanel;

        wxImage car_img;
        wxImage truck_img;
        wxImage motorcycle_img;
        wxImage trafficRed_img;
        wxImage trafficGreen_img;
        wxImage trafficYellow_img;
        wxImage start_img;
        wxImage end_img;
        wxImage simend_img;
        wxImage crash_img;
        wxImage grass_img;
        wxImage grassmedianN_img;
        wxImage grassmedianE_img;
        wxImage grassmedianS_img;
        wxImage grassmedianW_img;
        wxImage grey_img;
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
        void OnCloseSimClick(wxCommandEvent& event);

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
		static const long ID_SCOREPANEL;
        static const long ID_ENDPANEL;
		static const long ID_CloseSimButton;

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

        //identifiers for end panel
        static const long ID_STATICTEXT7;
        static const long ID_STATICTEXT8;
        static const long ID_STATICTEXT9;
        static const long ID_STATICTEXT10;
        static const long ID_STATICTEXT11;
        static const long ID_ENDTEXT;
        static const long ID_GAUGE1;
        static const long ID_GAUGE2;
        //*)

        //(*Declarations(Simulation)
        wxStatusBar* StatusBar1;
        wxTimer SimTimer;
        wxButton* beginButton;

        ///settings declarations
        wxButton* BeginButton;
        wxChoice* DrivingModeCtrl;
        wxPanel* SettingPanel2;
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
		wxBoxSizer* BoxSizer2;
		wxStaticText* CarCountText;
        wxStaticText* TruckCountText;
        wxStaticText* MotorcycleCountText;
        wxStaticText* ScoreText;
        wxStaticText* TimeText;
        wxStaticText* EndText;
        wxGauge* scoreG;
        wxGauge* timeG;

		//end screen declarations
		wxButton* CloseSimButton;

        //*)

        DECLARE_EVENT_TABLE()
};

#endif // TRAFFIC_SIMULATIONMAIN_H
