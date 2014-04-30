/*
 * Twisty Passages - A simple rogue-like dungeon crawler
 * Copyright (C) 2014  Elliot Dronebarger
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef ROOM_H
#define ROOM_H

#include "Utilities.h"

/*
 * Rooms are simple definitions that just include a Coord location (Top-left corner),
 * Coord room center(Which could be anywhere inside the room),
 * and a Dimension size.
 */

class Room
{
    public:
        Room(Coord inCenter, Dimension inSize, Coord inLocation);
        virtual ~Room();

        Coord center;

        Dimension size;

        Coord location;

    protected:
    private:
};

#endif // ROOM_H
