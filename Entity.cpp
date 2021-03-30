#include "Entity.h"

Entity::Entity(wxPoint basePosition, wxPoint offsetPosition, int arena)
{
    this->basePosition = basePosition;
    this->offsetPosition = offsetPosition;
    currentArena = arena;
}

Entity::~Entity()
{
    //dtor
}
