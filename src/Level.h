/*
 * Twisty Passages - A simple rogue-like dungeon crawler
 * Copyright (C) 2018  Elliot Dronebarger
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
#ifndef LEVEL_H
#define LEVEL_H
#include "Square.h"
#include "Room.h"
#include "Monster.h"
#include "Utilities.h"
#include <vector>

const int MIN_ROOMS = 5;
//Too many rooms may cause the level generation to never complete. They have to have space in between each room.
const int MAX_ROOMS = 15;
const int MIN_ROOM_SIZE = 5;
const int MAX_ROOM_SIZE = 8;
const double VISIBILITY_ANGLE_INCREMENT = 5.0;
const double VISIBILITY_LINEAR_INCREMENT = 0.1;

#include "Config.h"



//TODO: Come up with up and down stairs and ways to move between levels
class Level
{
    public:
        Level();
        virtual ~Level();
        void addRoom();
        void makeHalls();
        void addMonster(Monster& monster);
        void addStairs();
        bool isMonster(const Coord& coordinate);
        void updateVisible(const Coord& playerLocation);

        std::vector<std::vector<Square>> squares;
        int levelSizeX, levelSizeY;
        std::vector<Room> rooms;
        std::vector<Monster> monsters;
    protected:
    private:
        bool isAllWalls(const Coord& location);
        bool isLOS(const Coord& target, Coord& playerLoc);
        Config * c;
};

#endif // LEVEL_H
