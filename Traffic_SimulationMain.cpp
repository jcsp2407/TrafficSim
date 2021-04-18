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
#include <time.h>
//*)

#define ROWS 14
#define COLS 14
#define LIGHTS_PER_ARENA 4

unsigned int random_list[] = {0,3,4,5,8,9,10,13};

// Randomly spawn vehicle coordinates
int xRand, yRand;

void randXY(){
    int r = random_list[rand() % 8];

    if(rand() % 2){
        xRand = r;
        if(xRand == 0)
            yRand = rand() % 3 + 8;
        else if(xRand <= 6)
            yRand = 0;
        else if(xRand <= 10)
            yRand = 13;
        else
            yRand = rand() % 3 + 3;
    }else{
        yRand = r;
        if(yRand == 0)
            xRand = rand() % 3 + 3;
        else if(yRand <= 6)
            xRand = 13;
        else if(yRand <= 10)
            xRand = 0;
        else
            xRand = rand() % 3 + 8;
    }
}

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
const long Simulation::ID_SCOREPANEL = wxNewId();
const long Simulation::ID_ENDPANEL = wxNewId();

///settings panel buttons and interactives
const long Simulation::ID_ArenaCtrl = wxNewId();
const long Simulation::ID_CarSpinCtrl = wxNewId();
const long Simulation::ID_BikeSpinCtrl = wxNewId();
const long Simulation::ID_TruckSpinCtrl = wxNewId();
const long Simulation::ID_DrivingModeCtrl = wxNewId();
const long Simulation::ID_BeginButton = wxNewId();
const long Simulation::ID_CloseSimButton = wxNewId();
const long Simulation::ID_ENDTEXT = wxNewId();

//settings panel stuff
const long Simulation::ID_DrivingText = wxNewId();
const long Simulation::ID_ArenaText = wxNewId();
const long Simulation::ID_STATICTEXT3 = wxNewId();
const long Simulation::ID_STATICTEXT4 = wxNewId();
const long Simulation::ID_STATICTEXT5 = wxNewId();
const long Simulation::ID_STATICTEXT6 = wxNewId();
const long Simulation::ID_STATICTEXT7 = wxNewId();
const long Simulation::ID_STATICTEXT8 = wxNewId();
const long Simulation::ID_STATICTEXT9 = wxNewId();
const long Simulation::ID_STATICTEXT10 = wxNewId();
const long Simulation::ID_STATICTEXT11 = wxNewId();
const long Simulation::ID_PANEL3 = wxNewId();
const long Simulation::ID_PANEL1 = wxNewId();
const long Simulation::ID_GAUGE1 = wxNewId();
const long Simulation::ID_GAUGE2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(Simulation,wxFrame)
    //(*EventTable(Simulation)
    //*)
    //EVT_SIZE()
END_EVENT_TABLE()

Simulation::Simulation(wxWindow* parent,wxWindowID id)
{
    srand(time(NULL));

    //(*Initialize(Simulation)

    Create(parent, id, _T("Traffic Sim"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    Connect( ID_TIMER1,wxEVT_TIMER,( wxObjectEventFunction )&Simulation::OnTick );
    Connect( wxID_ANY,wxEVT_PAINT,( wxObjectEventFunction )&Simulation::OnPaint );
    Connect( wxID_ANY,wxEVT_ERASE_BACKGROUND,( wxObjectEventFunction )&Simulation::OnEraseBackground );
    //*)

    //Timer
    SimTimer.SetOwner( this, ID_TIMER1 );
    SimTimer.Start(500, false );

    //Loading images
    car_img.LoadFile( wxT( "car2_img.png" ), wxBITMAP_TYPE_PNG );
    truck_img.LoadFile( wxT( "truck.png" ), wxBITMAP_TYPE_PNG );
    motorcycle_img.LoadFile( wxT( "bike.png" ), wxBITMAP_TYPE_PNG );
    trafficRed_img.LoadFile( wxT( "red.png" ), wxBITMAP_TYPE_PNG );
    trafficYellow_img.LoadFile( wxT( "yellow.png" ), wxBITMAP_TYPE_PNG );
    trafficGreen_img.LoadFile( wxT( "green.png" ), wxBITMAP_TYPE_PNG );
    start_img.LoadFile( wxT("NEWSTART.jpg"), wxBITMAP_TYPE_ANY);
    end_img.LoadFile( wxT("endscreen_img.jpg"), wxBITMAP_TYPE_ANY );
    simend_img.LoadFile( wxT("simend.png"), wxBITMAP_TYPE_PNG);
    blank_img.LoadFile( wxT("blank.png"), wxBITMAP_TYPE_ANY);
    crash_img.LoadFile( wxT("crash.png"), wxBITMAP_TYPE_ANY);
    grass_img.LoadFile( wxT("grass_img.jpg"), wxBITMAP_TYPE_ANY);
    grassmedianN_img.LoadFile( wxT("grassmedian_img.jpg"), wxBITMAP_TYPE_ANY);
	grey_img.LoadFile( wxT("grey.png"), wxBITMAP_TYPE_PNG);


    //Re-scaling images
    car_img = car_img.Rescale(100, 50).ShrinkBy(7,5);
    truck_img = truck_img.Rescale(100, 50).ShrinkBy(5,5);
    motorcycle_img = motorcycle_img.ShrinkBy(7,6);
    trafficGreen_img = trafficGreen_img.Rescale(10,25).ShrinkBy(2,2);
    trafficRed_img = trafficRed_img.Rescale(10,25).ShrinkBy(2,2);
    trafficYellow_img = trafficYellow_img.Rescale(10,25).ShrinkBy(2,2);
    end_img = end_img.Scale(WIDTH, HEIGHT);
    grey_img = grey_img.Rescale(15,15);
    crash_img = crash_img.ShrinkBy(73,61);
	grass_img = grass_img.ShrinkBy(8,8);
    grassmedianN_img = grassmedianN_img.Rescale(28, 44);
    grassmedianE_img = grassmedianN_img.Rotate90(true);
    grassmedianS_img = grassmedianN_img.Rotate180();
    grassmedianW_img = grassmedianN_img.Rotate90(false);


    ramps = false;
    fullyStopped = 0;
    score = 0;
    speed = 1;

    //Panels
	endPanel = new wxPanel(this, ID_ENDPANEL, wxDefaultPosition, wxSize(WIDTH, HEIGHT), wxTAB_TRAVERSAL | wxNO_BORDER, _T("End Panel"));
	mainPanel = new wxScrolledWindow(this, ID_MAINPANEL, wxDefaultPosition, wxSize(R_WIDTH,R_HEIGHT), wxTAB_TRAVERSAL | wxVSCROLL, _T("Main Panel"));
	scorePanel = new wxPanel(this, ID_SCOREPANEL, wxPoint(R_WIDTH, 0), wxSize(WIDTH - R_WIDTH,HEIGHT), wxTAB_TRAVERSAL | wxNO_BORDER, _T("Score Panel"));
	//scorePanel->SetBackgroundColour(*wxLIGHT_GREY);
	scorePanel->Hide();
	startPanel = new wxPanel(this, ID_STARTPANEL, wxDefaultPosition, wxSize(WIDTH,HEIGHT), wxTAB_TRAVERSAL | wxNO_BORDER, _T("Start Panel"));
	startPanel->Hide();

    wxBoxSizer* BoxSizer1;
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	BoxSizer1->Add(startPanel, 1, wxALL|wxEXPAND, 0);
	SetSizer(BoxSizer1);

    screenState = state::startScreen;

    //Event Handlers
    startPanel->Connect(wxEVT_LEFT_DOWN,(wxObjectEventFunction)&Simulation::OnClickToStart,0,this);

    /* Settings Panel Config */
	wxBoxSizer* BoxSizer2;
    settingsPanel = new wxPanel(this, ID_PANEL1, wxPoint(0,0), wxSize(WIDTH,HEIGHT), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
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

	wxFont numbersFont(10, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);
	wxFont scoreFont(10, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, true);

	CarCountText = new wxStaticText(scorePanel, ID_STATICTEXT7, _("0/0"), wxPoint((WIDTH - R_WIDTH -25)/2, 25), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
	CarCountText->SetFont(numbersFont);
    TruckCountText = new wxStaticText(scorePanel, ID_STATICTEXT8, _("0/0"), wxPoint((WIDTH - R_WIDTH -25)/2, 65), wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    TruckCountText->SetFont(numbersFont);
    MotorcycleCountText = new wxStaticText(scorePanel, ID_STATICTEXT9, _("0/0"), wxPoint((WIDTH - R_WIDTH -25)/2, 105), wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    MotorcycleCountText->SetFont(numbersFont);
    ScoreText = new wxStaticText(scorePanel, ID_STATICTEXT10, _("Score"), wxPoint(7, 135), wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    ScoreText->SetFont(scoreFont);
    TimeText = new wxStaticText(scorePanel, ID_STATICTEXT11, _("Timer"), wxPoint(7, 175), wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    TimeText->SetFont(scoreFont);

    scoreG = new wxGauge(scorePanel, ID_GAUGE1, 0, wxPoint(5, 150), wxSize(37,10), wxHORIZONTAL, wxDefaultValidator, _T("SCORE"));
    timeG = new wxGauge(scorePanel, ID_GAUGE2, 0, wxPoint(5, 190), wxSize(37,10), wxHORIZONTAL, wxDefaultValidator, _T("TIMER"));

    //connect settings event handlers
    Connect(ID_BeginButton,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Simulation::OnBeginButtonClick);
    Connect(ID_CloseSimButton,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Simulation::OnCloseSimClick);
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
            scorePanel->Show();

            wxClientDC dc(scorePanel);
            dc.DrawBitmap( car_img, wxPoint((WIDTH - R_WIDTH -20)/2,15), true);
            dc.DrawBitmap( truck_img, wxPoint((WIDTH - R_WIDTH -20)/2, 55), true);
            dc.DrawBitmap( motorcycle_img, wxPoint((WIDTH - R_WIDTH -20)/2, 95), true);

            if(Car::GetTotalCrossed() < 10)
                CarCountText->SetLabel(wxString::Format(wxT("%i"), Car::GetTotalCrossed()) + "/" + wxString::Format(wxT("%i"), cars));
            else if (Car::GetTotalCrossed() < 100){
                CarCountText->SetPosition(wxPoint(5, 25));
                CarCountText->SetLabel(wxString::Format(wxT("%i"), Car::GetTotalCrossed()) + "/" + wxString::Format(wxT("%i"), cars));
            }
            else{
                CarCountText->SetPosition(wxPoint(1, 25));
                CarCountText->SetLabel(wxString::Format(wxT("%i"), Car::GetTotalCrossed()) + "/" + wxString::Format(wxT("%i"), cars));
            }

            if(Truck::GetTotalCrossed() < 10)
                TruckCountText->SetLabel(wxString::Format(wxT("%i"), Truck::GetTotalCrossed()) + "/" + wxString::Format(wxT("%i"), trucks));
            else if (Truck::GetTotalCrossed() < 100){
                TruckCountText->SetPosition(wxPoint(5, 65));
                TruckCountText->SetLabel(wxString::Format(wxT("%i"), Truck::GetTotalCrossed()) + "/" + wxString::Format(wxT("%i"), trucks));
            }
            else{
                TruckCountText->SetPosition(wxPoint(1, 65));
                TruckCountText->SetLabel(wxString::Format(wxT("%i"), Truck::GetTotalCrossed()) + "/" + wxString::Format(wxT("%i"), trucks));
            }

            if(Motorcycle::GetTotalCrossed() < 10)
                MotorcycleCountText->SetLabel(wxString::Format(wxT("%i"), Motorcycle::GetTotalCrossed()) + "/" + wxString::Format(wxT("%i"), motorcycles));
            else if (Motorcycle::GetTotalCrossed() < 100){
                MotorcycleCountText->SetPosition(wxPoint(5, 105));
                MotorcycleCountText->SetLabel(wxString::Format(wxT("%i"), Motorcycle::GetTotalCrossed()) + "/" + wxString::Format(wxT("%i"), motorcycles));
            }
            else{
                MotorcycleCountText->SetPosition(wxPoint(1, 105));
                MotorcycleCountText->SetLabel(wxString::Format(wxT("%i"), Motorcycle::GetTotalCrossed()) + "/" + wxString::Format(wxT("%i"), motorcycles));
            }

            int total = Vehicle::Gettotal();
            int a;
            Vehicle::DirectionType dir;
            wxImage img;
            myImageGridCellRenderer* render;

            for(int i = 0; i < total; i++){
                a = vehicles[i]->getCurrentArena();
                dir = vehicles[i]->Getdirection();

                if(dynamic_cast<Car*>(vehicles[i])){
                    if(!vehicles[i]->Getcrashed()){
                        switch(dir){
                            case Vehicle::North:
                                img = car_img.Rotate90(false);
                                break;
                            case Vehicle::South:
                                img = car_img.Rotate90(true);
                                break;
                            case Vehicle::West:
                                img = car_img.Rotate180();
                                break;
                            default:
                                img = car_img;
                        }
                    }else{
                        img = crash_img;
                    }
                    render = new myImageGridCellRenderer(img);
                }
                else if(dynamic_cast<Truck*>(vehicles[i])){
                    if(!vehicles[i]->Getcrashed()){
                        switch(dir){
                            case Vehicle::North:
                                img = truck_img.Rotate90(false);
                                break;
                            case Vehicle::South:
                                img = truck_img.Rotate90(true);
                                break;
                            case Vehicle::West:
                                img = truck_img.Rotate180();
                                break;
                            default:
                                img = truck_img;
                        }
                    }else{
                        img = crash_img;
                    }
                    render = new myImageGridCellRenderer(img);
                }else if(dynamic_cast<Motorcycle*>(vehicles[i])){
                    if(!vehicles[i]->Getcrashed()){
                        switch(dir){
                            case Vehicle::North:
                                img = motorcycle_img.Rotate90(false);
                                break;
                            case Vehicle::South:
                                img = motorcycle_img.Rotate90(true);
                                break;
                            case Vehicle::West:
                                img = motorcycle_img.Rotate180();
                                break;
                            default:
                                img = motorcycle_img;
                        }
                    }else{
                        img = crash_img;
                    }
                    render = new myImageGridCellRenderer(img);
                }

                    arenas[a]->SetCellRenderer(vehicles[i]->GetOldPos().y, vehicles[i]->GetOldPos().x, new myImageGridCellRenderer(grey_img));
                    arenas[a]->SetCellRenderer(vehicles[i]->Getpos().y, vehicles[i]->Getpos().x, render);
            }

            int lightCnt = arenasCnt * LIGHTS_PER_ARENA;

            for(int i = 0; i < lightCnt; i++){
                switch(lights[i]->Getcolor()){
                    case TrafficLight::Green:
                        img = trafficGreen_img;
                        break;
                    case TrafficLight::Yellow:
                        img = trafficYellow_img;
                        break;
                    case TrafficLight::Red:
                        img = trafficRed_img;
                        break;
                }
                render = new myImageGridCellRenderer(img);
                arenas[i/LIGHTS_PER_ARENA]->SetCellRenderer(lights[i]->Getpos().y, lights[i]->Getpos().x, render);
            }

            scoreG->SetValue(score);
            if(time_per_sec % (SimTimer.GetInterval())){
                if(timeG->GetValue() < timeG->GetRange()){
                    timeG->SetValue(timeG->GetValue() + 1);
                    time_per_sec = 0;
                }
            }
        }
            break;

        case state::endScreen:
        {
            wxClientDC dc(endPanel);
            mainPanel->Hide();
            scorePanel->Hide();
            endPanel->Show();
            dc.DrawBitmap(end_img, wxPoint(0,0), true);
            dc.DrawBitmap(simend_img, wxPoint(8,10), true);
        }
            break;

        default:
            break;
    }
}

void Simulation::OnTick( wxTimerEvent& event )
{
	switch (screenState){
        case state::runningScreen:
        {
            int total = Vehicle::Gettotal();

            Vehicle* temp;
            int r_index;

            int x, y, arena;

            for(int i= 0; i < total; i++){
                // Shuffle vehicle for randomness
                temp = vehicles[i];
                r_index = (rand() % (total - i)) + i;
                vehicles[i] = vehicles[r_index];
                vehicles[r_index] = temp;


                // CHECK GETPOSFRONT() AND USE PROBABILITIES FOR CRASHING

                if(!vehicles[i]->Getcrossed()){
                    // Move the shuffled vehicle if not crashed
                    if(!vehicles[i]->Getcrashed()){
                        obstacles[vehicles[i]->Getpos().x][vehicles[i]->Getpos().y][vehicles[i]->getCurrentArena()] = NULL;

                        x = vehicles[i]->getPosFront().x;
                        y = vehicles[i]->getPosFront().y;
                        arena = vehicles[i]->getCurrentArena();

                        if((x < 0 || x >= COLS) || (y < 0 || y >= ROWS)){
                            vehicles[i]->move();
                            vehicles[i]->Setcrossed(true);

                            if(dynamic_cast<Car*>(vehicles[i]))
                                Car::IncTotalCrossed();
                            else if(dynamic_cast<Truck*>(vehicles[i]))
                                Truck::IncTotalCrossed();
                            else if(dynamic_cast<Motorcycle*>(vehicles[i]))
                                Motorcycle::IncTotalCrossed();

                            score++;
                            continue;
                        }

                        temp = obstacles[x][y][arena];

                        if(temp == NULL){
                            vehicles[i]->move();
                            obstacles[x][y][arena] = vehicles[i];
        //                    MessageDialog1->SetMessage(wxT("Spot unoccupied"));
        //                    MessageDialog1->ShowModal();
                        }else{
        //                    MessageDialog1->SetMessage(wxT("Spot occupied"));
        //                    MessageDialog1->ShowModal();
                            int r;
                            switch(mode){
                                case Average: // Crazy = 10% crashing probability
                                    r = rand() % 10;
                                    if(!r){
                                        vehicles[i]->move();
                                        vehicles[i]->Setcrashed(true);
                                        temp->Setcrashed(true);
                                    }
                                    break;
                                case Crazy: // Crazy = 25% crashing probability
                                    r = rand() % 4;
                                    if(!r){
                                        vehicles[i]->move();
                                        vehicles[i]->Setcrashed(true);
                                        temp->Setcrashed(true);
                                    }
                                    break;
                                case FromMiami: // FromMiami = 50% crashing probability
                                    r = rand() % 2;
                                    if(!r){
                                        vehicles[i]->move();
                                        vehicles[i]->Setcrashed(true);
                                        temp->Setcrashed(true);
                                    }
                                    break;
                                default:    // Safe = 0% crashing probability
                                    break;
                            }
                        }
                    }
                }
            }

            int lightsCnt = arenasCnt * LIGHTS_PER_ARENA;
            for(int i= 0; i < lightsCnt; i++)
                lights[i]->alternate();

            time_per_sec++;
        }
            break;

        default:
            break;
	}

    this->Refresh();    // Refresh simulation GUI components

    if((screenState == state::runningScreen) && (timeG->GetValue() >= timeG->GetRange() || score >= (0.75 * Vehicle::Gettotal()))){
        screenState = state::endScreen;
        wxString scoreText;
        scoreText << score;
        wxString endScore = _T("Final Score: ") + scoreText;
        CloseSimButton = new wxButton(endPanel, ID_CloseSimButton, _("Close Simulation"), wxPoint(150,125), wxSize(150,40), 0, wxDefaultValidator, _T("ID_CloseSimButton"));
        wxFont EndTextFont(20,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
        EndText = new wxStaticText(endPanel, ID_ENDTEXT, endScore, wxPoint(150,60), wxSize(176,32), 0, _T("ID_ENDTEXT"));
        EndText->SetFont(EndTextFont);
    }
}

void Simulation::OnClickToStart(wxMouseEvent& event)
{
    screenState = state::settingsScreen;
}

void Simulation::OnBeginButtonClick(wxCommandEvent& event)
{
	arenasCnt = ArenaCtrl->GetValue();
	mode = static_cast<Simulation::DriveModeType>(DrivingModeCtrl->GetSelection());
	motorcycles = BikeSpinCtrl->GetValue();
	cars = CarSpinCtrl->GetValue();
	trucks = TruckSpinCtrl->GetValue();
	int t = cars + trucks + motorcycles;
	scoreG->SetRange(0.75 * t);

	if(t < 50)
        timeG->SetRange(50);
    else
        timeG->SetRange(t/arenasCnt);

	obstacles = new Vehicle***[COLS];
	for(int i=0; i<COLS;i++){
        obstacles[i] = new Vehicle**[ROWS];
        for(int j=0; j<ROWS; j++){
            obstacles[i][j] = new Vehicle*[arenasCnt];
            for(int k=0;k<arenasCnt;k++)
                obstacles[i][j][k] = NULL;
        }
	}


    mainPanel->SetScrollbars(0,10, 0, arenasCnt%2? A_HEIGHT*(arenasCnt+1)/20  : A_HEIGHT*arenasCnt/20);
    arenas = new Arena*[arenasCnt];
    int yPos = 0;
    for(int i = 0; i < arenasCnt; i++){
        arenas[i] = new Arena(mainPanel, wxID_ANY, wxPoint((i % 2)*(R_WIDTH/2), yPos), wxSize(A_WIDTH,A_HEIGHT), wxTAB_TRAVERSAL | wxBORDER);
        arenas[i]->CreateGrid(ROWS,COLS);
        arenas[i]->EnableEditing(true);
        arenas[i]->EnableGridLines(false);
        arenas[i]->SetColLabelSize(1);
        arenas[i]->SetRowLabelSize(1);
        arenas[i]->SetRowMinimalAcceptableHeight(10);
        arenas[i]->SetColMinimalAcceptableWidth(10);
        arenas[i]->SetDefaultRowSize(15, true);
        arenas[i]->SetDefaultColSize(15, true);
        arenas[i]->SetRowLabelValue(0, wxEmptyString);
        arenas[i]->SetDefaultCellFont( arenas[i]->GetFont() );
        arenas[i]->SetDefaultCellTextColour( arenas[i]->GetForegroundColour() );
        arenas[i]->Disable();

        if(i % 2)
            yPos+= HEIGHT;
    }

    int lightCnt = arenasCnt * LIGHTS_PER_ARENA;
    lights = new TrafficLight*[lightCnt];

    for(int i = 0; i < lightCnt; i++){
        int x;
        int y;
        switch(i % LIGHTS_PER_ARENA){
            case 0:
                x = 4; y =3;
            break;
            case 1:
                x = 10; y =4;
            break;
            case 2:
                x = 9; y =10;
            break;
            default:
                x = 3; y =9;
        }
        lights[i] = new TrafficLight(static_cast<TrafficLight::LightType>(i%2), wxPoint(x,y), i/LIGHTS_PER_ARENA);
    }

    vehicles = new Vehicle*[cars+trucks+motorcycles];

    int total;

    for(int i = 0; i < cars; i++){
        // Get random vehicle spawn coordinates
        randXY();
        Vehicle::DirectionType dir;

        switch(xRand){
            case 0: dir = Vehicle::DirectionType::East; break;
            case 13: dir = Vehicle::DirectionType::West; break;
        }
        switch(yRand){
            case 0: dir = Vehicle::DirectionType::South; break;
            case 13: dir = Vehicle::DirectionType::North; break;
        }

        total = Vehicle::Gettotal();

        vehicles[total] = new Car(dir, 1, wxPoint(xRand, yRand), rand() % arenasCnt);


    }

    for(int i = 0; i < trucks; i++){
        // Get random vehicle spawn coordinates
        randXY();
        Vehicle::DirectionType dir;

        switch(xRand){
            case 0: dir = Vehicle::DirectionType::East; break;
            case 13: dir = Vehicle::DirectionType::West; break;
        }
        switch(yRand){
            case 0: dir = Vehicle::DirectionType::South; break;
            case 13: dir = Vehicle::DirectionType::North; break;
        }

        total = Vehicle::Gettotal();

        vehicles[total] = new Truck(dir, 1, wxPoint(xRand, yRand), rand() % arenasCnt);
    }

    for(int i = 0; i < motorcycles; i++){
        // Get random vehicle spawn coordinates
        randXY();
        Vehicle::DirectionType dir;

        switch(xRand){
            case 0: dir = Vehicle::DirectionType::East; break;
            case 13: dir = Vehicle::DirectionType::West; break;
        }
        switch(yRand){
            case 0: dir = Vehicle::DirectionType::South; break;
            case 13: dir = Vehicle::DirectionType::North; break;
        }

        total = Vehicle::Gettotal();

        vehicles[total] = new Motorcycle(dir, 1, wxPoint(xRand, yRand), rand() % arenasCnt);
    }

    for(int k=0; k < arenasCnt ; k++)
    {
        for (int l=0; l < 4 ; l++){
            myImageGridCellRenderer *render = new myImageGridCellRenderer(grass_img);
            arenas[k]->SetCellRenderer(	(l%3 ? 0 : 11),		(l%2 ? 0 : 11), render);
        }
    }

    for(int i = 0; i<arenasCnt; i++){
        for(int j = 3; j<11; j++){
            for(int k = 0; k<14; k++){
                arenas[i]->SetCellRenderer(k, j, new RoadGridCellRenderer);
            }
        }

        for(int j = 3; j<11; j++){
            for(int k = 0; k<14; k++){
                arenas[i]->SetCellRenderer(j, k, new RoadGridCellRenderer);
            }
        }

        arenas[i]->SetCellRenderer(0, 6, new myImageGridCellRenderer(grassmedianN_img));
        arenas[i]->SetCellRenderer(6, 0, new myImageGridCellRenderer(grassmedianW_img));
        arenas[i]->SetCellRenderer(6, 11, new myImageGridCellRenderer(grassmedianE_img));
        arenas[i]->SetCellRenderer(11, 6, new myImageGridCellRenderer(grassmedianS_img));
    }

    screenState = state::runningScreen;
}

void Simulation::OnCloseSimClick(wxCommandEvent& event)
{
    Close();
}

void Simulation::OnResize(wxSizeEvent& event)
{

}

bool Simulation::start()
{
	return true;
}

void Simulation::stop()
{
}
