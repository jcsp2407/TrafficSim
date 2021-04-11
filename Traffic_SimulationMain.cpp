/***************************************************************
 * Name:      Traffic_SimulationMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Adrian A. Muino, Juan Saez, Alexander Perez ()
 * Created:   2021-03-28
 * Copyright: Adrian A. Muino, Juan Saez, Alexander Perez ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "Traffic_SimulationMain.h"
#include <wx/msgdlg.h>

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
const long Simulation::ID_TESTPANEL = wxNewId();
//*)

BEGIN_EVENT_TABLE(Simulation,wxFrame)
    //(*EventTable(Simulation)
    //*)

END_EVENT_TABLE()

Simulation::Simulation(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(Simulation)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Simulation::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Simulation::OnAbout);
    Connect( ID_TIMER1,wxEVT_TIMER,( wxObjectEventFunction )&Simulation::OnTick );
    Connect( wxID_ANY,wxEVT_PAINT,( wxObjectEventFunction )&Simulation::OnPaint );
    Connect( wxID_ANY,wxEVT_ERASE_BACKGROUND,( wxObjectEventFunction )&Simulation::OnEraseBackground );
    //*)

	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	startframe = new wxFrame(NULL, wxID_ANY, wxT("Traffic Sim"), wxPoint(50,50), wxSize(800,600));
	startpanel = new wxImagePanel( startframe, wxT("NEWSTART.jpg"), wxBITMAP_TYPE_JPEG);
	sizer->Add(startpanel, 1, wxEXPAND);
	startframe->SetSizer(sizer);
	startframe->Show();
	startpanel->Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&Simulation::OnClickToStart,0,this);


    car_img.LoadFile( wxT( "car2_img.png" ), wxBITMAP_TYPE_PNG );
    truck_img.LoadFile( wxT( "truck.png" ), wxBITMAP_TYPE_PNG );
    motorcycle_img.LoadFile( wxT( "bike.png" ), wxBITMAP_TYPE_PNG );
    trafficRed_img.LoadFile( wxT( "red.png" ), wxBITMAP_TYPE_PNG );
    trafficYellow_img.LoadFile( wxT( "yellow.png" ), wxBITMAP_TYPE_PNG );
    trafficGreen_img.LoadFile( wxT( "green.png" ), wxBITMAP_TYPE_PNG );
    start_img.LoadFile( wxT("start_img.jpg"), wxBITMAP_TYPE_ANY);
    traffic_img.LoadFile( wxT("Traffic.png"), wxBITMAP_TYPE_PNG);
    sim_img.LoadFile( wxT("Sim.png"), wxBITMAP_TYPE_PNG);
    clicktostart_img.LoadFile( wxT("Clicktostart.png"), wxBITMAP_TYPE_PNG);

    clicktostart_img.SetMaskColour(50,50,50);
    car_img = car_img.Rescale(100, 50);
    motorcycle_img = motorcycle_img.Rotate90().ShrinkBy(2,2);
    trafficGreen_img = trafficGreen_img.Rescale(10,25);
    trafficRed_img = trafficRed_img.Rescale(10,25);
    trafficYellow_img = trafficYellow_img.Rescale(10,25);
    start_img = start_img.Rescale(800, 600);

    SimTimer.SetOwner( this, ID_TIMER1 );
    SimTimer.Start( 10, false );


    arenaframe = new wxFrame(NULL, wxID_ANY, wxT("Arenas"), wxPoint(50,50), wxSize(800,600));
	arenapanel = new wxPanel(this, ID_TESTPANEL, wxPoint(0,0), wxSize(800,600), wxTAB_TRAVERSAL, _T("Start Panel"));
	arenas = new Arena*[10];
    arenas[0] = new Arena(this, wxID_ANY, wxDefaultPosition, wxSize(800, 600), wxTAB_TRAVERSAL, _T("Arena 0"));
	arenapanel->Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&Simulation::OnClickToStart,0,this);

//create event handler for new panel, make it show->false and then show->true new panel.

    //arenas[0]->SetBackgroundColour(wxColour(* wxLIGHT_GREY));


    //arenas[0]->Bind(wxEVT_PAINT, &Simulation::OnPaint, this );

    vehicles = new Vehicle*[10];

    vehicles[0] = new Car(Vehicle::East, 1, arenas[0]->GetPosition(), wxPoint(0,0), 1);
    vehicles[1] = new Motorcycle(Vehicle::East, 1, arenas[0]->GetPosition(), wxPoint(0, 50), 1);

    lights = new TrafficLight*[3];
    lights[0] = new TrafficLight(TrafficLight::Green, arenas[0]->GetPosition(), wxPoint(500, 20), 1);

    screenState = state::startScreen;
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

  //  wxClientDC dc(arenas[0]);

 //   dc.BeginDrawing(  );

    switch (screenState){
        case state::startScreen:
        {
//        wxClientDC dc(arenas[0]);
//
//		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
////		Traffic_SimulationApp::frame = new wxFrame(NULL, wxID_ANY, wxT("Hello wxDC"), wxPoint(50,50), wxSize(800,600));
////		Traffic_SimulationApp::drawPane = new wxImagePanel( frame, wxT("NEWSTART.jpg"), wxBITMAP_TYPE_JPEG);
//		sizer->Add(drawPane, 1, wxEXPAND);
//		Frame->SetSizer(sizer);
//		Frame->Show();
        }
            break;

		case state::settingsScreen:
		{

		}
			break;

        case state::runningScreen:
        {
            //delete test;
            wxClientDC dc(arenas[0]);

            dc.DrawBitmap( car_img, vehicles[0]->GetoffsetPosition(), true);
            dc.DrawBitmap( motorcycle_img, vehicles[1]->GetoffsetPosition(), true);

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
		}
			break;

        default:
            break;
    }





    /*
    dc.DrawBitmap( car_img, vehicles[0]->GetoffsetPosition(), true);
    dc.DrawBitmap( motorcycle_img, vehicles[1]->GetoffsetPosition(), true);

    switch(lights[0]->Getcolor()){
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
    */
    //dc.DrawBitmap( paddle_img, int( paddle[1].x ), int( paddle[1].y ), true );
    //dc.DrawBitmap( ball_img, int( ball.x ), int( ball.y ), true );

//    dc.EndDrawing(  );
}

void Simulation::OnTick( wxTimerEvent& event )
{
    /* Get keyboard input
    if( wxGetKeyState( WXK_SHIFT ) )
        paddle[0].y -= 8;
    else if( wxGetKeyState( WXK_CONTROL ) )
        paddle[0].y += 8;
    if( wxGetKeyState( WXK_UP ) )
        paddle[1].y -= 8;
    else if( wxGetKeyState( WXK_DOWN ) )
        paddle[1].y += 8;
    */

	// Computations

	switch (screenState){
        case state::startScreen:
            {
            }
            break;

		case state::settingsScreen:
			break;

        case state::runningScreen:
        {
            if((lights[0]->Getcolor() == TrafficLight::Green && vehicles[0]->GetoffsetPosition().x <= lights[0]->GetoffsetPosition().x) || (vehicles[0]->GetoffsetPosition().x > lights[0]->GetoffsetPosition().x && vehicles[0]->GetoffsetPosition().x < arenas[0]->GetSize().GetWidth() - 100)){
                vehicles[0]->move();
            }

            if(vehicles[1]->GetoffsetPosition().x == lights[0]->GetoffsetPosition().x){
                motorcycle_img = motorcycle_img.Rotate90();
                vehicles[1]->move();
                vehicles[1]->Setdirection(Vehicle::South);
            }

            if((lights[0]->Getcolor() == TrafficLight::Green && vehicles[1]->GetoffsetPosition().x <= lights[0]->GetoffsetPosition().x) || (vehicles[1]->GetoffsetPosition().x > lights[0]->GetoffsetPosition().x && vehicles[1]->GetoffsetPosition().y < arenas[0]->GetSize().GetHeight() - 100)){
                vehicles[1]->move();
            }
        }
        break;

        case state::endScreen:
			break;
	}

    /*lights[0]->alternate();

    if((lights[0]->Getcolor() == TrafficLight::Green && vehicles[0]->GetoffsetPosition().x <= lights[0]->GetoffsetPosition().x) || (vehicles[0]->GetoffsetPosition().x > lights[0]->GetoffsetPosition().x && vehicles[0]->GetoffsetPosition().x < arenas[0]->GetSize().GetWidth() - 100)){
        vehicles[0]->move();
    }

    if(vehicles[1]->GetoffsetPosition().x == lights[0]->GetoffsetPosition().x){
        motorcycle_img = motorcycle_img.Rotate90();
        vehicles[1]->move();
        vehicles[1]->Setdirection(Vehicle::South);
    }

    if((lights[0]->Getcolor() == TrafficLight::Green && vehicles[1]->GetoffsetPosition().x <= lights[0]->GetoffsetPosition().x) || (vehicles[1]->GetoffsetPosition().x > lights[0]->GetoffsetPosition().x && vehicles[1]->GetoffsetPosition().y < arenas[0]->GetSize().GetHeight() - 100)){
        vehicles[1]->move();
    }

    */
    this->Refresh();
}

void Simulation::OnClickToStart(wxMouseEvent& event)
{
	startframe->Show(false);
    screenState = state::runningScreen;
    arenaframe->Show(true);

}

bool Simulation::start()
{

}

void Simulation::stop()
{

}

