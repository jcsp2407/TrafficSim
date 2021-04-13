/***************************************************************
 * Name:      Traffic_SimulationApp.h
 * Purpose:   Defines Application Class
 * Author:    Adrian A. Muino, Juan Saez, Alexander Perez ()
 * Created:   2021-03-28
 * Copyright: Adrian A. Muino, Juan Saez, Alexander Perez ()
 * License:
 **************************************************************/

#ifndef TRAFFIC_SIMULATIONAPP_H
#define TRAFFIC_SIMULATIONAPP_H

#include <wx/app.h>
#include "Traffic_SimulationMain.h"

class Traffic_SimulationApp : public wxApp
{
    public:
        virtual bool OnInit();
        Simulation* Frame;
};

DECLARE_APP(Traffic_SimulationApp)

#endif // TRAFFIC_SIMULATIONAPP_H
