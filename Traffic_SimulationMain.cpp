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

    car_img.LoadFile( wxT( "car.png" ), wxBITMAP_TYPE_PNG );
    truck_img.LoadFile( wxT( "truck.png" ), wxBITMAP_TYPE_PNG );
    motorcycle_img.LoadFile( wxT( "motorcycle.png" ), wxBITMAP_TYPE_PNG );

    SimTimer.SetOwner( this, ID_TIMER1 );
    SimTimer.Start( 10, false );

    arenas = new Arena*[10];

    arenas[0] = new Arena(this, wxID_ANY, wxDefaultPosition, wxSize(500, 500), wxTAB_TRAVERSAL, _T("Arena 0"));
    //arenas[0]->SetBackgroundColour(wxColour(* wxLIGHT_GREY));


    //arenas[0]->Bind(wxEVT_PAINT, &Simulation::OnPaint, this );

    vehicles = new Vehicle*[10];

    vehicles[0] = new Car(Vehicle::North, 1, arenas[0]->GetPosition(), wxPoint(0,0), 1);

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
    wxClientDC dc(arenas[0]);

//    dc.BeginDrawing(  );

    dc.DrawBitmap( car_img, vehicles[0]->GetbasePosition(), true);
    dc.DrawBitmap( motorcycle_img, vehicles[0]->GetbasePosition(), true);
   // dc.DrawBitmap( paddle_img, int( paddle[0].x ), int( paddle[0].y ), true );
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


    this->Refresh();
}

bool Simulation::start()
{

}

void Simulation::stop()
{

}
