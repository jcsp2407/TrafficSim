#ifndef ARENA_H
#define ARENA_H

class Arena : public wxPanel
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
        wxPoint GetbasePosition() { return basePosition; }
        void SetbasePosition(wxPoint val) { basePosition = val; }
        static int Getlength() { return length; }
        static void Setlength(int val) { length = val; }
        static int Getwidth() { return width; }
        static void Setwidth(int val) { width = val; }
        int Getlanes() { return lanes; }
        void Setlanes(int val) { lanes = val; }

    protected:

    private:
        int intersections;
        wxPoint basePosition;
        static int length;
        static int width;
        int lanes;
};

#endif // ARENA_H
