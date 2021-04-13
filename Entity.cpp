#include "Entity.h"

Entity::Entity(wxPoint offsetPosition, int arena)
{
    this->offsetPosition = offsetPosition;
    currentArena = arena;
}

Entity::~Entity()
{
    //dtor
}
