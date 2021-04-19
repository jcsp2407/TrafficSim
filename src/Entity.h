#ifndef ENTITY_H
#define ENTITY_H
#include <wx/gdicmn.h>
class Entity
{
    public:
        Entity(wxPoint pos, int arena);
        virtual ~Entity();

        wxPoint Getpos() { return pos; }
        void Setpos(wxPoint val) { pos = val; }
        int Getlength() { return length; }
        void Setlength(int val) { length = val; }
        int Getwidth() { return width; }
        void Setwidth(int val) { width = val; }
        int getCurrentArena(){return currentArena;}

        virtual void show() = 0;

    protected:
        int currentArena;
        wxPoint pos;

    private:
        int length;
        int width;

};

#endif // ENTITY_H
