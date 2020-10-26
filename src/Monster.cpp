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
#include "Fight.h"
#include "Level.h"
#include "Monster.h"
#include "Character.h"
#include "Logger.h"

Monster::Monster()
{
	symbol = '@';
	location = Coord(0,0);
    hp = 10.0;
    maxHp = 10.0;
    visibility = 5.0;
    speed = 1.0;
    movement = 0.0;

    l = l->getInstance();
}

Monster::~Monster()
{
}

void Monster::update() {
    if (hp < maxHp) {
        hp += (maxHp / 100.0);
    }
}

void Monster::takeTurn(Level & level, Character & character) {
    double relative_speed = speed / character.speed;
    movement += relative_speed;
    while (movement >= 1.0) {
        if (level.isAdjacent(*this,character)) {
            Fight::attack(*this,character);
            l->log(Logger::GAME,"The " + this->classname + " hits you!",true);
        } else {
            if (level.isLOS(character.location,*this)) {
                //Move toward the player
                Coord moveTo = this->location;
                if (location.x < character.location.x) {
                    moveTo.x++;
                } else if (location.x > character.location.x) {
                    moveTo.x--;
                }
                if (location.y < character.location.y) {
                    moveTo.y++;
                } else if (location.y > character.location.y) {
                    moveTo.y--;
                }
                if (level.squares[moveTo.x][moveTo.y].isWalkable()) {
                    location = moveTo;
                }
            }
        }
        movement -= 1.0;
    }
    
}
