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
#ifndef LEVEL_H
#define LEVEL_H
#include "Square.h"
#include "Room.h"
#include "Monster.h"
#include "Utilities.h"
#include <vector>

const int LEVEL_SIZE_X = 100;
const int LEVEL_SIZE_Y = 40;
const int MIN_ROOMS = 5;
//Too many rooms may cause the level generation to never complete. They have to have space in between each room.
const int MAX_ROOMS = 15;
const int MIN_ROOM_SIZE = 5;
const int MAX_ROOM_SIZE = 8;


//TODO: Come up with up and down stairs and ways to move between levels
class Level
{
    public:
        Level();
        virtual ~Level();
        void addRoom();
        void makeHalls();
        void addMonster(Monster* monster);
        void addStairs();
        bool isMonster(Coord coordinate);
        void updateVisible(Coord playerLocation);

        Square squares[LEVEL_SIZE_X][LEVEL_SIZE_Y];
        int levelSizeX, levelSizeY;
        std::vector<Room> rooms;
        std::vector<Monster> monsters;
    protected:
    private:
        bool isAllWalls(Coord location);
};

#endif // LEVEL_H
