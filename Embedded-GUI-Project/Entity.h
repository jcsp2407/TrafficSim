#ifndef ENTITY_H
#define ENTITY_H

class Entity
{
    public:
        Entity(wxPoint offsetPosition, int arena);
        virtual ~Entity();

        wxPoint GetoffsetPosition() { return offsetPosition; }
        void SetoffsetPosition(wxPoint val) { offsetPosition = val; }
        int Getlength() { return length; }
        void Setlength(int val) { length = val; }
        int Getwidth() { return width; }
        void Setwidth(int val) { width = val; }
        int getCurrentArena(){return currentArena;}

        virtual void show() = 0;

    protected:
        int currentArena;

    private:
        wxPoint offsetPosition;
        int length;
        int width;

};

#endif // ENTITY_H
