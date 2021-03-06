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

#include "Character.h"
#include "Config.h"
#include "Monster.h"
#include "MonsterData.h"
#include "Room.h"
#include "Square.h"
#include "Utilities.h"

#include <vector>



//TODO: Come up with up and down stairs and ways to move between levels
class Level
{
    public:
        Level();
        virtual ~Level();
        void addRoom();
        void makeHalls();
        void addMonster(Monster& monster);
        void addMonsters(int level);
        void addStairs();
        Monster * monsterAt(const Coord& coordinate);
        bool isLOS(const Coord& target, const Monster& source);
        bool isAdjacent(const Monster & mons1, const Monster &mons2);
        void updateVisible(const Character& player);

        std::vector<std::vector<Square>> squares;
        int levelSizeX, levelSizeY;
        std::vector<Room> rooms;
        std::vector<Monster> monsters;
        
    protected:
    private:
        bool isAllWalls(const Coord& location);
        MonsterData * mons_data;
        Config * c;
};

#endif // LEVEL_H
