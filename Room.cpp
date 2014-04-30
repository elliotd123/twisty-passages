#include "Room.h"

Room::Room(Coord inCenter, Dimension inSize, Coord inLocation)
{
    //ctor
    size = inSize;

    center = inCenter;

    location = inLocation;
}

Room::~Room()
{
    //dtor
}
