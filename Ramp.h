#ifndef RAMP_H
#define RAMP_H

#include "Entity.h"


class Ramp : public Entity
{
    public:
        Ramp(bool ascending,wxPoint pos, int arena);
        virtual ~Ramp();

        bool Getascending() { return ascending; }
        void Setascending(bool val) { ascending = val; }

        void show() override;

    protected:

    private:
        bool ascending;
};

#endif // RAMP_H
