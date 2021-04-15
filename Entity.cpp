#include "Entity.h"

Entity::Entity(wxPoint pos, int arena)
{
    this->pos = pos;
    currentArena = arena;
}

Entity::~Entity()
{
    //dtor
}
