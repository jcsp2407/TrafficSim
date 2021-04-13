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
#include <wx/msgdlg.h>
#include <wx/spinctrl.h>

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
const long Simulation::idMenuQuit = wxNewId();
const long Simulation::idMenuAbout = wxNewId();
const long Simulation::ID_STATUSBAR1 = wxNewId();
const long Simulation::ID_TIMER1 = wxNewId();
const long Simulation::ID_STARTPANEL = wxNewId();
const long Simulation::ID_SETTINGSPANEL = wxNewId();
const long Simulation::ID_MAINPANEL = wxNewId();
const long Simulation::ID_BEGINBUTTON = wxNewId();
const long Simulation::ID_NUMCARS = wxNewId();
//*)

BEGIN_EVENT_TABLE(Simulation,wxFrame)
    //(*EventTable(Simulation)
    //*)
    //EVT_SIZE()
END_EVENT_TABLE()

Simulation::Simulation(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(Simulation)

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));

    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Simulation::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Simulation::OnAbout);
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

    //Initialize Simulation members
    cars = 10;
    trucks = 10;
    motorcycles = 10;
    arenasCnt = 10;
    mode = DriveModeType::Average;
    ramps = false;
    fullyStopped = 0;
    score = 0;
    speed = 1;

    //Panels
    wxBoxSizer* BoxSizer1;

    mainPanel = new wxScrolledWindow(this, ID_MAINPANEL, wxDefaultPosition, wxSize(WIDTH,HEIGHT), wxTAB_TRAVERSAL | wxVSCROLL, _T("Main Panel"));

    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    settingsPanel = new wxPanel(mainPanel, ID_SETTINGSPANEL, wxDefaultPosition, wxSize(WIDTH,HEIGHT), wxTAB_TRAVERSAL | wxNO_BORDER, _T("Settings"));
    startPanel = new wxPanel(mainPanel, ID_STARTPANEL, wxDefaultPosition, wxSize(WIDTH,HEIGHT), wxTAB_TRAVERSAL | wxNO_BORDER, _T("Start Panel"));
    startPanel->Hide();
    settingsPanel->Hide();

    //Entities
    vehicles = new Vehicle*[10];
    vehicles[0] = new Car(Vehicle::East, 1, wxPoint(0,0), 1);
    vehicles[1] = new Motorcycle(Vehicle::East, 1, wxPoint(0, 50), 1);
    vehicles[2] = new Truck(Vehicle::North, 1, wxPoint(50, HEIGHT), 1);

    lights = new TrafficLight*[3];
    lights[0] = new TrafficLight(TrafficLight::Green, wxPoint(30, 30), 1);

    //Misc
    beginButton = new wxButton(settingsPanel, ID_BEGINBUTTON, _("Begin"), wxDefaultPosition, wxSize(184,34), 0, wxDefaultValidator, _T("ID_URLBUTTON"));
    BoxSizer1->Add(startPanel, 1, wxALL|wxEXPAND, 0);
    SetSizer(BoxSizer1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);


    screenState = state::startScreen;

    //Event Handlers
    startPanel->Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&Simulation::OnClickToStart,0,this);
    Connect(ID_BEGINBUTTON,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Simulation::OnBeginButton);
}

Simulation::~Simulation()
{
    //(*Destroy(Simulation)
    //*)
}

void Simulation::OnQuit(wxCommandEvent& event)
{
    Close();
}

void Simulation::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxString(_T("Traffic Simulation Program"));
    wxMessageBox(msg, _("Welcome to..."));
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
            wxClientDC dc(settingsPanel);
        }
            break;

        case state::runningScreen:
        {
            startPanel->Hide();
            settingsPanel->Hide();
            arenas[0]->Show();
            arenas[1]->Show();
            wxClientDC dc(arenas[1]);

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
            settingsPanel->Show();
            wxClientDC dc(settingsPanel);
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

void Simulation::OnBeginButton(wxCommandEvent& event)
{
    mainPanel->SetScrollbars(0,1, 0, HEIGHT*arenasCnt/2);

    arenas = new Arena*[arenasCnt];
    int yPos = 0;
    for(int i = 0; i < arenasCnt; i++){
        arenas[i] = new Arena(mainPanel, wxID_ANY, wxPoint((i % 2)*(WIDTH/2), yPos), wxSize(WIDTH/2,HEIGHT), wxTAB_TRAVERSAL | wxBORDER);
        if(i % 2)
            yPos+= HEIGHT;
    }

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

}

void Simulation::stop()
{

}
