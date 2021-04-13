#ifndef MYBGPANELS_H
#define MYBGPANELS_H


#include <wx/wx.h>
#include <wx/sizer.h>


class wxImagePanel : public wxPanel
{
    wxImage image;
    wxBitmap resized;
    int w, h;

public:
    wxImagePanel(wxFrame* parent, wxString file, wxBitmapType format);

    void paintEvent(wxPaintEvent & evt);
    void paintNow();
    void OnSize(wxSizeEvent& event);
    void render(wxDC& dc);

//     void mouseMoved(wxMouseEvent& event);
//     void mouseDown(wxMouseEvent& event);
//     void mouseWheelMoved(wxMouseEvent& event);
//     void mouseReleased(wxMouseEvent& event);
//     void rightClick(wxMouseEvent& event);
//     void mouseLeftWindow(wxMouseEvent& event);
//     void keyPressed(wxKeyEvent& event);
//     void keyReleased(wxKeyEvent& event);


    DECLARE_EVENT_TABLE()
};

#endif // MYBGPANELS_H
