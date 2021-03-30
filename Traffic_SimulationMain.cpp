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

//(*InternalHeaders(Traffic_SimulationFrame)
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
const long Traffic_SimulationFrame::idMenuQuit = wxNewId();
const long Traffic_SimulationFrame::idMenuAbout = wxNewId();
const long Traffic_SimulationFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(Traffic_SimulationFrame,wxFrame)
    //(*EventTable(Traffic_SimulationFrame)
    //*)
END_EVENT_TABLE()

Traffic_SimulationFrame::Traffic_SimulationFrame(wxWindow* parent,wxWindowID id)
{

	bg_img.LoadFile( wxT( "bg.png" ), wxBITMAP_TYPE_PNG );
	start_img.LoadFile(wxT("start_img.png"),wxBITMAP_TYPE_PNG );
	end_img.LoadFile(wxT("end_img.png"),wxBITMAP_TYPE_PNG );
	car_img.LoadFile(wxT("car_img.png"),wxBITMAP_TYPE_PNG );
	truck_img.LoadFile(wxT("truck_img.png"),wxBITMAP_TYPE_PNG );
	MOTORCYCLE_img.LoadFile(wxT("MOTORCYCLE_img.png"),wxBITMAP_TYPE_PNG );
	trafficlight_img.LoadFile(wxT("trafficlight_img.png"),wxBITMAP_TYPE_PNG );
	streets_img.LoadFile(wxT("streets_img.png"),wxBITMAP_TYPE_PNG );


    //(*Initialize(Traffic_SimulationFrame)
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

    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Traffic_SimulationFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Traffic_SimulationFrame::OnAbout);
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
