/***************************************************************
 * Name:      Traffic_SimulationMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Adrian A. Muino, Juan Saez, Alexander Perez ()
 * Created:   2021-03-28
 * Copyright: Adrian A. Muino, Juan Saez, Alexander Perez ()
 * License:
 **************************************************************/

#include "Traffic_SimulationMain.h"
#include "Arena.h"
#include "Traffic_SimulationApp.h"
#include "wx_pch.h"


//(*InternalHeaders(Simulation)
#include <wx/intl.h>
#include <wx/string.h>
//*)


//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(Simulation)
const long Simulation::ID_TIMER1 = wxNewId();
const long Simulation::ID_STARTPANEL = wxNewId();
const long Simulation::ID_MAINPANEL = wxNewId();

///settings panel buttons and interactives
const long Simulation::ID_ArenaCtrl = wxNewId();
const long Simulation::ID_CarSpinCtrl = wxNewId();
const long Simulation::ID_BikeSpinCtrl = wxNewId();
const long Simulation::ID_TruckSpinCtrl = wxNewId();
const long Simulation::ID_DrivingModeCtrl = wxNewId();
const long Simulation::ID_BeginButton = wxNewId();

//settings panel stuff
const long Simulation::ID_DrivingText = wxNewId();
const long Simulation::ID_ArenaText = wxNewId();
const long Simulation::ID_STATICTEXT3 = wxNewId();
const long Simulation::ID_STATICTEXT4 = wxNewId();
const long Simulation::ID_STATICTEXT5 = wxNewId();
const long Simulation::ID_STATICTEXT6 = wxNewId();
const long Simulation::ID_PANEL3 = wxNewId();
const long Simulation::ID_PANEL1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(Simulation,wxFrame)
    //(*EventTable(Simulation)
    //*)
    //EVT_SIZE()
END_EVENT_TABLE()

Simulation::Simulation(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(Simulation)

    Create(parent, id, _T("Traffic Sim"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    Connect( ID_TIMER1,wxEVT_TIMER,( wxObjectEventFunction )&Simulation::OnTick );
    Connect( wxID_ANY,wxEVT_PAINT,( wxObjectEventFunction )&Simulation::OnPaint );
    Connect( wxID_ANY,wxEVT_ERASE_BACKGROUND,( wxObjectEventFunction )&Simulation::OnEraseBackground );
    //*)

    //Timer
    SimTimer.SetOwner( this, ID_TIMER1 );
    SimTimer.Start( 10, false );

    //Loading images
    car_img.LoadFile( wxT( "car2_img.png" ), wxBITMAP_TYPE_PNG );
    truck_img.LoadFile( wxT( "truck.png" ), wxBITMAP_TYPE_PNG );
    motorcycle_img.LoadFile( wxT( "bike.png" ), wxBITMAP_TYPE_PNG );
    trafficRed_img.LoadFile( wxT( "red.png" ), wxBITMAP_TYPE_PNG );
    trafficYellow_img.LoadFile( wxT( "yellow.png" ), wxBITMAP_TYPE_PNG );
    trafficGreen_img.LoadFile( wxT( "green.png" ), wxBITMAP_TYPE_PNG );
    start_img.LoadFile( wxT("NEWSTART.jpg"), wxBITMAP_TYPE_ANY);

    //Re-scaling images
    car_img = car_img.Rescale(100, 50).ShrinkBy(5,5);
    truck_img = truck_img.Rescale(100, 50).ShrinkBy(5,5);
    motorcycle_img = motorcycle_img.Rotate90().ShrinkBy(5,5);
    trafficGreen_img = trafficGreen_img.Rescale(10,25).ShrinkBy(2,2);
    trafficRed_img = trafficRed_img.Rescale(10,25).ShrinkBy(2,2);
    trafficYellow_img = trafficYellow_img.Rescale(10,25).ShrinkBy(2,2);

    ramps = false;
    fullyStopped = 0;
    score = 0;
    speed = 1;

    //Panels
	mainPanel = new wxScrolledWindow(this, ID_MAINPANEL, wxDefaultPosition, wxSize(WIDTH,HEIGHT), wxTAB_TRAVERSAL | wxVSCROLL, _T("Main Panel"));
	startPanel = new wxPanel(mainPanel, ID_STARTPANEL, wxDefaultPosition, wxSize(WIDTH,HEIGHT), wxTAB_TRAVERSAL | wxNO_BORDER, _T("Start Panel"));
	startPanel->Hide();

    wxBoxSizer* BoxSizer1;
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer1->Add(startPanel, 1, wxALL|wxEXPAND, 0);
	SetSizer(BoxSizer1);
	BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    screenState = state::startScreen;

    //Event Handlers
    startPanel->Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&Simulation::OnClickToStart,0,this);

    /* Settings Panel Config */
	wxBoxSizer* BoxSizer2;
    settingsPanel = new wxPanel(this, ID_PANEL1, wxPoint(0,0), wxSize(504,280), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    SettingPanel2 = new wxPanel(settingsPanel, ID_PANEL3, wxDefaultPosition, wxSize(491,261), wxTAB_TRAVERSAL, _T("ID_PANEL3"));
    SettingPanel2->SetBackgroundColour(wxColour(184,243,243));
    ArenaCtrl = new wxSpinCtrl(SettingPanel2, ID_ArenaCtrl, _T("1"), wxPoint(16,64), wxSize(120,30), wxALIGN_RIGHT, 1, 10, 1, _T("ID_ArenaCtrl"));
    ArenaCtrl->SetValue(_T("1"));
    ArenaText = new wxStaticText(SettingPanel2, ID_ArenaText, _("Number of Arenas"), wxPoint(16,48), wxDefaultSize, 0, _T("ID_ArenaText"));
    DrivingText = new wxStaticText(SettingPanel2, ID_DrivingText, _("Driving Mode"), wxPoint(16,96), wxDefaultSize, 0, _T("ID_DrivingText"));
    CarSpinCtrl = new wxSpinCtrl(SettingPanel2, ID_CarSpinCtrl, _T("50"), wxPoint(336,40), wxSize(120,30), 0, 0, 100, 10, _T("ID_CarSpinCtrl"));
    CarSpinCtrl->SetValue(_T("10"));
    BikeSpinCtrl = new wxSpinCtrl(SettingPanel2, ID_BikeSpinCtrl, _T("50"), wxPoint(336,120), wxSize(120,30), 0, 0, 100, 0, _T("ID_BikeSpinCtrl"));
    BikeSpinCtrl->SetValue(_T("0"));
    TruckSpinCtrl = new wxSpinCtrl(SettingPanel2, ID_TruckSpinCtrl, _T("50"), wxPoint(336,80), wxSize(120,30), 0, 0, 100, 0, _T("ID_TruckSpinCtrl"));
    TruckSpinCtrl->SetValue(_T("0"));
    DrivingModeCtrl = new wxChoice(SettingPanel2, ID_DrivingModeCtrl, wxPoint(16,112), wxSize(-1,30), 0, 0, 0, wxDefaultValidator, _T("ID_DrivingModeCtrl"));
    DrivingModeCtrl->SetSelection( DrivingModeCtrl->Append(_("Safe")) );
    DrivingModeCtrl->Append(_("Average"));
    DrivingModeCtrl->Append(_("Crazy"));
    DrivingModeCtrl->Append(_("From Miami"));
    CarText = new wxStaticText(SettingPanel2, ID_STATICTEXT3, _("Number of Cars"), wxPoint(224,48), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    TruckText = new wxStaticText(SettingPanel2, ID_STATICTEXT4, _("Number of Trucks"), wxPoint(208,88), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    SettingsText = new wxStaticText(SettingPanel2, ID_STATICTEXT5, _("Simulation Settings"), wxPoint(96,0), wxSize(176,32), 0, _T("ID_STATICTEXT5"));
    wxFont SettingsTextFont(20,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    SettingsText->SetFont(SettingsTextFont);
    BikeText = new wxStaticText(SettingPanel2, ID_STATICTEXT6, _("Number of Motorcycles"), wxPoint(176,128), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    BeginButton = new wxButton(SettingPanel2, ID_BeginButton, _("Begin!"), wxPoint(168,152), wxSize(136,40), 0, wxDefaultValidator, _T("ID_BeginButton"));
    BoxSizer2->Add(SettingPanel2, 1, wxALL|wxEXPAND, 0);
    settingsPanel->SetSizer(BoxSizer2);
	settingsPanel->Hide();
    BoxSizer2->Fit(this);
    BoxSizer2->SetSizeHints(this);

    //connect settings event handlers

    Connect(ID_BeginButton,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Simulation::OnBeginButtonClick);
}

Simulation::~Simulation()
{
    //(*Destroy(Simulation)
    //*)
}

void Simulation::OnEraseBackground( wxEraseEvent& event )
{
}

void Simulation::OnPaint( wxPaintEvent& event )
{
    switch (screenState){
        case state::startScreen:
        {
            wxBitmap resized;
            settingsPanel->Hide();
            startPanel->Show();

            wxClientDC dc(startPanel);
            resized = wxBitmap( start_img.Scale( this->GetSize().GetWidth(), this->GetSize().GetHeight() ), wxIMAGE_QUALITY_HIGH );
            dc.DrawBitmap(resized,wxPoint(0,0), true);
        }
            break;

        case state::settingsScreen:
        {
            startPanel->Hide();
            settingsPanel->Show();
        }
            break;

        case state::runningScreen:
        {
            startPanel->Hide();
            settingsPanel->Hide();
            mainPanel->Show();

            wxClientDC dc(arenas[0]);
            dc.DrawBitmap( car_img, vehicles[0]->GetoffsetPosition(), true);
            dc.DrawBitmap( motorcycle_img, vehicles[1]->GetoffsetPosition(), true);
            dc.DrawBitmap( truck_img, vehicles[2]->GetoffsetPosition(), true);

            switch(lights[0]->Getcolor())
            {
                case TrafficLight::Green:
                    dc.DrawBitmap( trafficGreen_img, lights[0]->GetoffsetPosition(), true);
                    break;
                case TrafficLight::Yellow:
                    dc.DrawBitmap( trafficYellow_img, lights[0]->GetoffsetPosition(), true);
                    break;
                case TrafficLight::Red:
                    dc.DrawBitmap( trafficRed_img, lights[0]->GetoffsetPosition(), true);
                    break;
            }
        }
            break;

        case state::endScreen:
        {
            startPanel->Hide();
            arenas[0]->Hide();
            settingsPanel->Hide();
        }
            break;

        default:
            break;
    }
}

void Simulation::OnTick( wxTimerEvent& event )
{
	switch (screenState){
        case state::startScreen:
        {
        }
            break;

        case state::runningScreen:
        {
            lights[0]->alternate();

            if((lights[0]->Getcolor() == TrafficLight::Green && vehicles[0]->GetoffsetPosition().x <= lights[0]->GetoffsetPosition().x) || (vehicles[0]->GetoffsetPosition().x > lights[0]->GetoffsetPosition().x)){
                vehicles[0]->move();
            }

            if(vehicles[1]->GetoffsetPosition().x == lights[0]->GetoffsetPosition().x){
                motorcycle_img = motorcycle_img.Rotate90();
                vehicles[1]->move();
                vehicles[1]->Setdirection(Vehicle::South);
            }

            if((lights[0]->Getcolor() == TrafficLight::Green && vehicles[1]->GetoffsetPosition().x <= lights[0]->GetoffsetPosition().x) || (vehicles[1]->GetoffsetPosition().x > lights[0]->GetoffsetPosition().x)){
                vehicles[1]->move();
            }
            vehicles[2]->move();
        }
            break;

        default:
            break;
	}

    this->Refresh();
}

void Simulation::OnClickToStart(wxMouseEvent& event)
{
    screenState = state::settingsScreen;
}

void Simulation::OnBeginButtonClick(wxCommandEvent& event)
{
	arenasCnt = ArenaCtrl->GetValue();
	mode = (Simulation::DriveModeType)DrivingModeCtrl->GetSelection();
	motorcycles = BikeSpinCtrl->GetValue();
	cars = CarSpinCtrl->GetValue();
	trucks = TruckSpinCtrl->GetValue();

    mainPanel->SetScrollbars(0,10, 0, arenasCnt%2? HEIGHT*(arenasCnt+1)/20  : HEIGHT*arenasCnt/20);
    arenas = new Arena*[arenasCnt];
    int yPos = 0;
    for(int i = 0; i < arenasCnt; i++){
        arenas[i] = new Arena(mainPanel, wxID_ANY, wxPoint((i % 2)*(WIDTH/2), yPos), wxSize(WIDTH/2,HEIGHT), wxTAB_TRAVERSAL | wxBORDER);
        if(i % 2)
            yPos+= HEIGHT;
    }

    vehicles = new Vehicle*[cars];
    vehicles[0] = new Car(Vehicle::East, 1, wxPoint(0,0), 1);
    vehicles[1] = new Motorcycle(Vehicle::East, 1, wxPoint(0, 50), 1);
    vehicles[2] = new Truck(Vehicle::North, 1, wxPoint(50, HEIGHT), 1);

	lights = new TrafficLight*[3];
    lights[0] = new TrafficLight(TrafficLight::Green, wxPoint(30, 30), 1);

    screenState = state::runningScreen;
}

void Simulation::OnResize(wxSizeEvent& event)
{
    /*wxSize windowSize = event.GetSize();
    int x = windowSize.GetWidth();
    int y = windowSize.GetHeight();*/

}

bool Simulation::start()
{
	return true;
}

void Simulation::stop()
{
}

/* __________________Settings Event handlers ______________________				*/



/* __________________End of Settings Event handlers ______________________				*/
