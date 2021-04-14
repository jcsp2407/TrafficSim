#ifndef ARENA_H
#define ARENA_H
#include <wx/grid.h>

class Arena : public wxGrid
{
    public:
        Arena(wxWindow *parent,
            wxWindowID winid = wxID_ANY,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = wxTAB_TRAVERSAL | wxNO_BORDER,
            const wxString& name = wxPanelNameStr);

        virtual ~Arena();

        int Getintersections() { return intersections; }
        void Setintersections(int val) { intersections = val; }
        int Getlanes() { return lanes; }
        void Setlanes(int val) { lanes = val; }

    protected:

    private:
        int intersections;
        static int length;
        static int width;
        int lanes;
};

#endif // ARENA_H
