/***************************************************************
 * Name:      Traffic_SimulationMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Adrian A. Muino, Juan Saez, Alexander Perez ()
 * Created:   2021-03-28
 * Copyright: Adrian A. Muino, Juan Saez, Alexander Perez ()
 * License:
 **************************************************************/


#include "Traffic_SimulationMain.h"
#include <wx/msgdlg.h>
#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <iostream>

//(*InternalHeaders(Traffic_SimulationFrame)
#include <wx/bitmap.h>
#include <wx/image.h>
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

//(*IdInit(Traffic_SimulationFrame)
const long Traffic_SimulationFrame::ID_STATICBITMAP1 = wxNewId();
const long Traffic_SimulationFrame::idMenuQuit = wxNewId();
const long Traffic_SimulationFrame::idMenuAbout = wxNewId();
const long Traffic_SimulationFrame::ID_STATUSBAR1 = wxNewId();
const long Traffic_SimulationFrame::ID_MESSAGEDIALOG1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(Traffic_SimulationFrame,wxFrame)
    //(*EventTable(Traffic_SimulationFrame)
    //*)
END_EVENT_TABLE()

Traffic_SimulationFrame::Traffic_SimulationFrame(wxWindow* parent,wxWindowID id)
{

	bg_img.LoadFile( wxT( "bg_img.png" ), wxBITMAP_TYPE_PNG );
	start_img.LoadFile(wxT("start_img.jpg"),wxBITMAP_TYPE_PNG );
	end_img.LoadFile(wxT("endscreen_img.jpg"),wxBITMAP_TYPE_PNG );
	car_img.LoadFile(wxT("car1_img.png"),wxBITMAP_TYPE_PNG );
	truck_img.LoadFile(wxT("vehicles_img.jpg"),wxBITMAP_TYPE_PNG );
	MOTORCYCLE_img.LoadFile(wxT("motorcycle_img.jpg"),wxBITMAP_TYPE_PNG );
	trafficlight_img.LoadFile(wxT("trafficlight_img.png"),wxBITMAP_TYPE_PNG );
	streets_img.LoadFile(wxT("street_img.jpg"),wxBITMAP_TYPE_PNG );


    //(*Initialize(Traffic_SimulationFrame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, wxID_ANY, _("Traffic Simulation"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE|wxMAXIMIZE_BOX, _T("wxID_ANY"));
    SetClientSize(wxSize(570,545));
    StaticBitmap1 = new wxStaticBitmap(this, ID_STATICBITMAP1, wxBitmap(wxImage(_T("/home/juan/Desktop/Embedded-GUI-Project/start_img.jpg")).Rescale(wxSize(546,545).GetWidth(),wxSize(546,545).GetHeight())), wxPoint(24,0), wxSize(546,545), 0, _T("ID_STATICBITMAP1"));
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
    MessageDialog1 = new wxMessageDialog(this, wxEmptyString, _("Message"), wxOK|wxCANCEL, wxDefaultPosition);

    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Traffic_SimulationFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Traffic_SimulationFrame::OnAbout);
    Connect(wxEVT_PAINT,(wxObjectEventFunction)&Traffic_SimulationFrame::OnPaint);
    //*)

}

Traffic_SimulationFrame::~Traffic_SimulationFrame()
{
    //(*Destroy(Traffic_SimulationFrame)
    //*)
}

void Traffic_SimulationFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void Traffic_SimulationFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxString(_T("Traffic Simulation Program"));
    wxMessageBox(msg, _("Welcome to..."));
}

void Traffic_SimulationFrame::OnPaint(wxPaintEvent& event)
{
	wxBufferedPaintDC dc( this );

	wxBitmap start_img; //main screen when loading program
	wxBitmap end_img; //ending screen
	wxBitmap bg_img; //main simulation background image

    wxBitmap car_img; //generic car
    wxBitmap truck_img; //generic truck img
    wxBitmap MOTORCYCLE_img;//generic bike img
    wxBitmap trafficlight_img; //static traffic light
    wxBitmap streets_img; //might need to remove this, but static streets

//	dc.DrawBitmap( bg_img, 0, 0, true );
//    dc.DrawBitmap( paddle_img, int( paddle[0].x ), int( paddle[0].y ), true );
//    dc.DrawBitmap( paddle_img, int( paddle[1].x ), int( paddle[1].y ), true );
//    dc.DrawBitmap( ball_img, int( ball.x ), int( ball.y ), true );

}
