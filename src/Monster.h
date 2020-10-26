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
#ifndef MONSTER_H
#define MONSTER_H

#include <string>

#include "Utilities.h"

class Level;
class Character;

class Monster
{
    public:
        Monster();
        virtual ~Monster();

        void update();

        Coord location;
        char symbol;
        double hp,maxHp;
        double attack,defense;
        double visibility;
        double speed;
        int minLevel,maxLevel;
        std::string description;
        std::string classname;
        std::string keyname;
        void takeTurn(Level & level, Character & character);
        double movement;

    protected:
    private:
};

#endif // MONSTER_H
